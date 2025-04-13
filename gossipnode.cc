#include <omnetpp.h>
#include <unordered_set>
#include "GossipNode.h"
#include "ModelUpdate_m.h"  // Include generated header
#include <Python.h>

// Adding csv file reading func
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace omnetpp;

Define_Module(GossipNode);

// Define a struct for the node information
struct NodeInfo {
    int nodeId;
    std::string location;
    std::vector<std::string> cluster;
};

//read the node_locations.csv file and assign locations and clusters to nodes
void GossipNode::assignLocationAndCluster(const std::string& csvFilePath) {
    std::ifstream file(csvFilePath);
    if (!file.is_open()) {
        EV << "Error: Could not open file " << csvFilePath << "\n";
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    int nodeIndex = getIndex(); // Get the index of the current node

    for (int i = 0; i <= nodeIndex; ++i) {
        if (!std::getline(file, line)) {
            EV << "Error: Not enough lines in CSV for node " << nodeIndex << "\n";
            return;
        }
    }

    std::stringstream ss(line);
    std::string nodeStr, loc, clusterStr;

    // Extract Node, Location, and Cluster columns
    std::getline(ss, nodeStr, ',');
    std::getline(ss, loc, ',');
    std::getline(ss, clusterStr, ',');

    // Assign location name
    locationName = loc;

    // Clear any old cluster data
    clusterMembers.clear();

    // Parse the clusterStr to extract individual cluster members
    if (clusterStr.front() == '[' && clusterStr.back() == ']') {
        clusterStr = clusterStr.substr(1, clusterStr.size() - 2);
    }

    std::stringstream clusterSS(clusterStr);
    std::string member;

    while (std::getline(clusterSS, member, ',')) {
        // Trim leading/trailing whitespace
        member.erase(0, member.find_first_not_of(" \t\n\r\f\v"));
        member.erase(member.find_last_not_of(" \t\n\r\f\v") + 1);

        // Remove quotes if present
        if (!member.empty() && member.front() == '\'' && member.back() == '\'') {
            member = member.substr(1, member.size() - 2);
        }

        clusterMembers.push_back(member);
    }

    // Log the assigned location and cluster members
    EV << "Assigned location \"" << locationName << "\" to node " << nodeIndex << "\n";
    EV << "Assigned cluster members to node " << nodeIndex << ": ";
    for (const auto& m : clusterMembers) {
        EV << m << " ";
    }
    EV << "\n";
}


void GossipNode::initialize() {
    if (getIndex() == 0) {
        cMessage *msg = new cMessage("GossipMessage");
        scheduleAt(0.0, msg);
        // Initialize Python interpreter once
       wchar_t programName[] = L"/Users/tyler/Desktop/omnetpp-6.1/.venv/bin/python3";
       Py_SetProgramName(programName);
       Py_Initialize();

       // Add FLARE-sim directory to Python path
       PyRun_SimpleString("import sys");
       PyRun_SimpleString("sys.path.append('/Users/tyler/Desktop/Winter2025/P2PNetworking/FLARE/test-env/FLARE-sim/')");
    }

    trainEvent = new cMessage("TrainEvent");
    scheduleAt(simTime() + uniform(1, 3), trainEvent);

    for (int i = 0; i < 5; i++) {
        modelWeights.push_back(uniform(0.5, 1.5));
    }

    EV << "Node[" << getIndex() << "] initialized with modelWeights = ";
    for (const auto& weight : modelWeights) {
        EV << weight << " ";
    }
    EV << "\n";

    // Assign location and cluster members from CSV
    std::string csvFilePath = "./node_locations.csv";
    assignLocationAndCluster(csvFilePath);

    // Build a display string label showing location + cluster members
    std::string label = locationName + "\\nCluster:";
    for (const auto& member : clusterMembers) {
        label += "\\n" + member;
    }

    // Set the display string (tooltip text)
    getDisplayString().setTagArg("t", 0, label.c_str());

    EV << "Display string updated to:\n" << label << "\n";
}



void GossipNode::handleMessage(cMessage *msg)
{
    if (msg == trainEvent) {
        performLocalTraining();
        scheduleAt(simTime() + uniform(1, 3), trainEvent);
        return;
    }

    ModelUpdate *update = dynamic_cast<ModelUpdate *>(msg);
    if (update != nullptr) {
        EV << "Node[" << getIndex() << "] received model from node "
           << update->getSenderId() << "\n";

        // Simple fusion: average with current weights
        std::vector<double> received;
        for (int i = 0; i < update->getWeightsArraySize(); ++i) {
            received.push_back(update->getWeights(i));
        }
        // received contains the full list of weights
        // can fuse it like this:
        for (size_t i = 0; i < modelWeights.size(); i++) {
            modelWeights[i] = (modelWeights[i] + received[i]) / 2.0;
        }

        delete msg;
        return;
    }

    delete msg; // fallback, in case of stray messages
}



void GossipNode::forwardModelUpdate(ModelUpdate *msg)
{
    int n = gateSize("out");
    for (int i = 0; i < n; i++) {
        ModelUpdate *copy = msg->dup();
        send(copy, "out", i);
    }
    delete msg;
}

void GossipNode::performLocalTraining() {
    EV << "Node[" << getIndex() << "] performing local training\n";

    // Simulate model update by tweaking weights
    std::vector<double> previousWeights = modelWeights;  // Store the previous weights for convergence tracking
    for (auto& weight : modelWeights) {
        weight += uniform(-0.1, 0.1);
    }

    // Track the maximum weight change for convergence
    double maxWeightChange = 0.0;
    for (size_t i = 0; i < modelWeights.size(); ++i) {
        double weightChange = fabs(modelWeights[i] - previousWeights[i]);
        maxWeightChange = std::max(maxWeightChange, weightChange);
    }

    // Log convergence information
    double convergenceThreshold = 0.01;  // Set a threshold for convergence (adjust as needed)
    if (maxWeightChange < convergenceThreshold) {
        EV << "Node[" << getIndex() << "] model has converged! Max weight change: " << maxWeightChange << "\n";
    }

    // Evaluate accuracy (for now, use a dummy function)
    double accuracy = evaluateModel(modelWeights);
    EV << "Node[" << getIndex() << "] accuracy: " << accuracy << "\n";

    // Create a message to send weights
    ModelUpdate *update = new ModelUpdate("ModelUpdate");
    update->setSenderId(getIndex());

    // Allocate and copy local model weights into the outgoing ModelUpdate message
    update->setWeightsArraySize(modelWeights.size());
    for (size_t i = 0; i < modelWeights.size(); ++i) {
        update->setWeights(i, modelWeights[i]);
    }

    // Track message send time for latency (record the time before sending)
    double sendTime = simTime().dbl();
    EV << "Node[" << getIndex() << "] sending message at time: " << sendTime << "\n";

    // Forward the message
    forwardModelUpdate(update);

    // After message is sent, we can track the round-trip latency (for now just log send time)
    //double receiveTime = simTime().dbl();  // Replace with actual receive time logic
  //  double latency = receiveTime - sendTime;
   // EV << "Node[" << getIndex() << "] message latency: " << latency << " seconds\n";
}

double GossipNode::evaluateModel(const std::vector<double>& modelWeights) {

    // Add FLARE-sim directory to Python path
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/Users/tyler/Desktop/Winter2025/P2PNetworking/FLARE/test-env/FLARE-sim')");  // <-- Update this if path differs

    // Prepare arguments for the Python script
    PyObject *pName = PyUnicode_DecodeFSDefault("linear_regression");  // Name of the Python script (without the .py)
    PyObject *pModule = PyImport_Import(pName);  // Import the module
    if (pModule == NULL) {
        PyErr_Print();  // This will print the error from Python
    }
    Py_XDECREF(pName);

    if (pModule != NULL) {
        // Create a Python tuple to pass the model weights and location as arguments
        PyObject *pArgs = PyTuple_New(modelWeights.size() + 1);  // +1 for the location argument
        for (size_t i = 0; i < modelWeights.size(); ++i) {
            PyTuple_SetItem(pArgs, i, PyFloat_FromDouble(modelWeights[i]));  // Convert model weight to Python float
        }


        // Pass the location as a string (convert it to a Python object)
        PyTuple_SetItem(pArgs, modelWeights.size(), PyUnicode_FromString(this->locationName.c_str()));

        // Call the function from the Python module (e.g., 'run_regression')
        PyObject *pFunc = PyObject_GetAttrString(pModule, "run_regression");  // Name of the function in the Python script
        if (pFunc == NULL || !PyCallable_Check(pFunc)) {
            PyErr_Print();  // Prints an error if the function isn't found or isn't callable
        }
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);  // Call the function
            Py_XDECREF(pArgs);
            if (pValue != NULL) {
                // Process the return value (e.g., regression result)
                double result = PyFloat_AsDouble(pValue);  // Assume the function returns a float value
                Py_XDECREF(pValue);
                Py_XDECREF(pFunc);
                Py_XDECREF(pModule);
                return result;  // Return the result
            }
        }
        else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_XDECREF(pModule);
    }
    else {
        PyErr_Print();
    }
    return -1;  // Return an error value if Python script fails
}

GossipNode::~GossipNode() {
    if (trainEvent) {
        cancelAndDelete(trainEvent);
    }
}

void GossipNode::finish() {
    if (pythonInitialized) {
        // Finalize Python interpreter once, when simulation finishes
        Py_FinalizeEx();
        pythonInitialized = false;
    }

    // Call the base class's finish (if needed)
    cSimpleModule::finish();
}

