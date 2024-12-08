# DS_Final-Project

# City Traffic Network Simulation

## Introduction

This project simulates a **City Traffic Network** to manage urban traffic flow, vehicle routing, road networks, and traffic signal management. The system is designed to handle real-world scenarios such as road closures, vehicle congestion, emergency vehicle routing, and traffic signal operations. It provides insights into traffic conditions and optimizes routes for both regular and emergency vehicles.

The simulation incorporates key components of modern traffic systems, making it a comprehensive tool for traffic management and urban planning.

---

## Overview

The project uses C++ to implement a modular design comprising the following components:

### 1. **Road Networks**
- Implements a graph-based representation of intersections and roads using adjacency matrices.
- Supports dynamic addition and removal of roads and intersections.
- Provides pathfinding algorithms such as Dijkstra's algorithm for shortest paths.

### 2. **Blocked Roads**
- Manages road statuses such as *Blocked*, *Under Repair*, or *Clear*.
- Allows dynamic updates to road conditions and displays a categorized list of road statuses.

### 3. **Traffic Signals**
- Simulates traffic signals for each intersection with configurable green time durations.
- Displays signal timings for all intersections.

### 4. **Vehicle Management**
- Tracks the number of vehicles on each road using a hash table.
- Identifies the most congested roads based on vehicle counts.
- Enables vehicle movement between intersections, updating traffic data dynamically.

### 5. **Emergency Vehicle Routing**
- Prioritizes emergency vehicles based on urgency (High, Medium, Low).
- Provides the shortest and safest route for emergency vehicles using BFS (Breadth-First Search).

### 6. **City Traffic Simulation**
- Offers a user-friendly menu for operations such as adding/removing intersections, updating roads, simulating traffic flow, and displaying traffic data.
- Handles real-world scenarios, including road closures, traffic signal management, and emergency routing.

---

## Simulation Board

The simulation board allows users to interact with the city traffic network through 13 different operations. Below is a description of each operation:

1. **Add New Car**:
   - Adds a new intersection (node) to the city traffic network.
   - Intersections are represented as alphabetic characters (e.g., `A`, `B`, `C`).

    ### Output of Choice 1
     ![alt text](<Images/Screenshot 2024-12-08 192948.png>)
     
     ![alt text](<Images/Screenshot 2024-12-08 193010.png>)
    

2. **Add Road**:
   - Connects two intersections with a road (edge).
   - Users specify the weight of the road (e.g., travel time or distance).
  
    ### Output of Choice 2
     
     ![alt text](<Images/Screenshot 2024-12-08 193049.png>)
     
     ![alt text](<Images/Screenshot 2024-12-08 193121.png>)
     

3. **Remove New Car**:
   - Deletes an intersection from the network.
   - Removes all roads connected to the specified intersection.
  
    ### Output of Choice 3

     
     ![alt text](<Images/Screenshot 2024-12-08 193419.png>)
   

4. **Remove Road**:
   - Deletes a specific road between two intersections.
   - Updates the adjacency matrix to reflect the removal.
  
    ### Output of Choice 4
     
     ![alt text](<Images/Screenshot 2024-12-08 193502.png>)
     

5. **Block Road Due to Accident**:
   - Marks a road as blocked and removes it from the active network.
   - Adds the road to the list of blocked roads for further monitoring
  
    ### Output of Choice 5
     
     
     ![alt text](<Images/Screenshot 2024-12-08 193601.png>)
     

6. **Display City Traffic Network**:
   - Shows all intersections and roads in the network.
   - Roads are displayed with their weights, providing a clear view of connectivity.

    ### Output of Choice 6
   
     ![alt text](<Images/Screenshot 2024-12-08 193630.png>)
     

7. **Display Blocked Roads**:
   - Lists all roads categorized as `Blocked`, `Under Repair`, or `Clear`.
   - Helps monitor road statuses for better decision-making.
  
    ### Output of Choice 7
     
     ![alt text](<Images/Screenshot 2024-12-08 193650.png>)
     

8. **Display Traffic Signals Status**:
   - Displays the green time duration for each intersection.
   - Helps analyze traffic flow and signal timings.
  
    ### Output of Choice 8
     
     ![alt text](<Images/Screenshot 2024-12-08 193708.png>)
     

9. **Move Vehicles**:
   - Simulates the movement of vehicles between two intersections.
   - Updates the vehicle count on the specified road.
  
  ### Output of Choice 9
  -
     ![alt text](<Images/Screenshot 2024-12-08 193754.png>)

     ![alt text](<Images/Screenshot 2024-12-08 192948.png>)
  

10. **Display Congestion Status**:
   - Identifies and displays the most congested roads based on vehicle counts.
   - Lists vehicle counts for all roads in the network.

  
  ### Output of Choice 10
  -
     ![alt text](<Images/Screenshot 2024-12-08 193849.png>)
     

11. **Handle Emergency Vehicle Routing**:
   - Simulates the routing of emergency vehicles based on priority (High, Medium, Low).
   - Finds and displays the shortest path for emergency vehicles using BFS.
    ### Output of Choice 11
     
     ![alt text](<Images/Screenshot 2024-12-08 193920.png>)

     ![alt text](<Images/Screenshot 2024-12-08 193941.png>)
     

12. **Simulate Vehicle Routing**:
   - Displays all possible paths between two intersections.
   - Highlights the shortest path using Dijkstra's algorithm.
     .
    ![alt text](<Images/Screenshot 2024-12-08 194049.png>)
     

13. **Exit Simulation**:
   - Terminates the simulation program.
    ### Output of Choice 12
   - 
     
     ![alt text](<Images/Screenshot 2024-12-08 194106.png>)
     

These operations allow users to dynamically manage and monitor the city traffic network, addressing real-world challenges such as traffic congestion, road closures, and emergency routing.


---

## How to Run

1. **Setup the Project**:
   - Clone the repository and navigate to the project directory.
   - Ensure `road_network.csv`, `road_closures.csv`, `vehicles.csv` , `emergency_vehicles.csv`  and `traffic_signals.csv` files are placed in the directory.

2. **Compile the Code**:
   ```bash
   g++ -o CityTrafficNetworkSimulation 1232615_1232631_1221935.cpp
