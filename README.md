# FLARE: Federated Learning for Adaptive Road Efficiency

## Overview
FLARE (Federated Learning for Adaptive Road Efficiency) is a framework designed to optimize traffic flow predictions using a decentralized mesh of traffic sensor nodes. This project leverages federated learning combined with gossip-based protocols to allow nodes to collaboratively improve local models without relying on a central server. This approach reduces communication overhead and enhances scalability.

## Project Description
As cities grow and urban transportation systems become increasingly complex, managing traffic efficiently has become a significant challenge—particularly in environments with constrained computing and communication capabilities, such as Wireless Sensor Networks (WSNs). FLARE is built to address these challenges by optimizing traffic flow predictions and enabling adaptive, decentralized control through a mesh of traffic sensors.

Each node in the system is trained on localized traffic data gathered from real intersections in downtown Victoria, BC. These nodes share model updates with their neighbors using a fully connected cluster-based topology called QuadMesh. By leveraging federated learning with gossip protocols, FLARE allows for scalable and efficient traffic management.

The simulation integrates **OMNeT++** for network modeling and **SUMO** for realistic traffic generation, with Python scripts handling data preprocessing and linear regression model training. Early simulation results show promising performance, with model convergence occurring through iterative neighborhood updates. This system holds potential for scalable, distributed traffic control and lays the groundwork for future enhancements such as anomaly detection and real-time adaptation.

## Running the Project in OMNeT++
To run this project in **OMNeT++**, follow these steps:

1. **Open the Project in OMNeT++**:
   - Download and install [OMNeT++](https://omnetpp.org/download/) if you haven't already.
   - Open the project in OMNeT++ by importing the project files.
  
2. **Install the `inet4.5` Framework**:
   - Ensure you have the **`inet4.5`** framework installed and configured within OMNeT++.
   - If `inet4.5` is not installed, download it from [INET Framework](https://inet.omnetpp.org/) and follow the installation instructions to integrate it into your OMNeT++ project.

3. **Run the Simulation**:
   - Once the project is set up and `inet4.5` is installed, run the simulation within OMNeT++ to simulate the mesh network and traffic data.

## Project Results
- **Simulation Environment**: The system integrates with **SUMO** for traffic simulation and **OMNeT++** for network modeling.
- **Federated Learning**: Each node in the mesh learns from local traffic data, improves its traffic prediction model, and shares updates with neighboring nodes.
- **Topology**: The simulation uses a **QuadMesh** topology, which consists of four fully connected clusters with nodes representing intersections in downtown Victoria.
- **Performance**: Early simulation results show promising performance with model convergence achieved through iterative neighborhood updates.

## Future Work
This project lays the groundwork for future enhancements, including:
- **Anomaly Detection**: Adding functionality to detect traffic anomalies in real-time.
- **Real-Time Adaptation**: Enhancing the system to adapt dynamically to changing traffic conditions.

## Website
For more details and updates on the project, visit the [official project website](https://tylertrott.github.io/CSC466Project/CSC466project.html).
