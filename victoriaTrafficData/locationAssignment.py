import os
import random
import pandas as pd
import csv

def extract_location_from_filename(filename):
    """
    Extract intersection location from the filename.
    Assumes the filename format is 'ID - Intersection Name.xlsx'
    """
    # Split the filename to get the intersection name
    intersection_name = filename.split(" - ")[1].replace(".xlsx", "")
    return intersection_name

# Directory where .xlsx files are stored
base_dir = os.path.dirname(__file__)  # path to directory where script lives
directory = os.path.join(base_dir, '2025 TMC Collection Program')

# Initialise an empty list for locations
locations = []

# Loop through all .xlsx files in the directory and extract the location
for filename in os.listdir(directory):
    if filename.endswith(".xlsx"):  # Ensure we're only working with .xlsx files
        location = extract_location_from_filename(filename)
        locations.append(location)

# Check the extracted locations
print("Extracted Locations:")
print(locations)

# Number of nodes in the GossipGrid
num_nodes = 16  # Change this as per your setup (4 clusters of 4 nodes)

# Randomly assign locations to nodes
random.shuffle(locations)

# Ensure there are enough locations for the number of nodes
if len(locations) < num_nodes:
    raise ValueError("Not enough locations for the number of nodes.")

# Create a list of node IDs (Node 1, Node 2, ..., Node n)
node_ids = [f"Node {i + 1}" for i in range(num_nodes)]

# Assign each node a random location
node_locations = locations[:num_nodes]  # Take the first 'num_nodes' locations

# Group nodes into clusters of 4
clusters = [node_locations[i:i + 4] for i in range(0, len(node_locations), 4)]

# Print the nodes and clusters to check
print("\nNode Locations:")
for i, location in enumerate(node_locations):
    print(f"Node {i + 1}: {location}")

print("\nClusters:")
for i, cluster in enumerate(clusters):
    print(f"Cluster {i + 1}: {cluster}")
    
with open('node_locations.csv', 'w', newline='') as csvfile:
    fieldnames = ['Node', 'Location', 'Cluster']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    writer.writeheader()
    for node, location, cluster in zip(node_ids, node_locations, clusters):
        writer.writerow({'Node': node, 'Location': location, 'Cluster': cluster})
        
clusters_array = []
for cluster in clusters:
    # Clean up each cluster member by stripping spaces and removing surrounding quotes
    clean_cluster = [member.strip().strip('\'') for member in cluster if member]
    clusters_array.append(clean_cluster)
print("\nClusters Array:")
print(clusters_array)

# Flatten and create node-level entries for CSV
rows = []
node_index = 0
for cluster in clusters_array:
    for node in cluster:
        # Each row will be: NodeIndex, LocationName
        rows.append([node_index, node])
        node_index += 1

# Write to CSV
with open("node_locations.csv", "w", newline="") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Node', 'Location'])  # Header
    writer.writerows(rows)

print("\nCSV written to node_locations.csv")
