#ifndef GOSSIPNODE_H
#define GOSSIPNODE_H

#include <omnetpp.h>
#include <unordered_set>
#include <vector>

using namespace omnetpp;

class ModelUpdate;

class GossipNode : public cSimpleModule
{
  private:
    std::unordered_set<std::string> receivedMsgs;
    double modelWeight;  // Declare model weight
    cMessage *trainEvent;  // Declare event for local training
    std::vector<double> modelWeights;  // Add modelWeights as a vector
    std::string locationName;
    std::vector<std::string> clusterMembers;
    bool pythonInitialized = false; // Flag to track if Python was initialized

  protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    void forwardMessage(cMessage *msg);
    void performLocalTraining();  // Declare training function
    void forwardModelUpdate(ModelUpdate *update);
    double evaluateModel(const std::vector<double>& modelWeights);
    void assignLocationAndCluster(const std::string& csvFilePath);
    void logAccuracy(double accuracy);

  public:
    virtual ~GossipNode();  // Declare the destructor
};

#endif
