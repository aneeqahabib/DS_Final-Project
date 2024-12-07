#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits> // For INT_MAX

using namespace std;

class EmergencyVehicles
{
private:
    int vertices;
    int **adjMatrix;              
    string intersectionNames[100];
    int currentId;

    struct EmergencyVehicle
    {
        string id;
        int source;
        int destination;
        string priority;
    } vehicles[100]; // Maximum of 100 emergency vehicles

    int vehicleCount = 0;

public:
    EmergencyVehicles(int v)
    {
        vertices = v;
        currentId = 0;

        // Dynamically allocate memory for adjacency matrix
        adjMatrix = new int *[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adjMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
            {
                adjMatrix[i][j] = INT_MAX; // Initialization
            }
        }
    }

    void addEdge(int source, int destination, int weight)
    {
        adjMatrix[source][destination] = weight;
    }

    int getIntersectionId(const string &name)
    {
        for (int i = 0; i < currentId; i++)
        {
            if (intersectionNames[i] == name)
                return i;
        }

        intersectionNames[currentId] = name;
        return currentId++;
    }

    void loadFromCSV(const string &filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;

        // Skip the header line
        getline(file, line);

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string sourceStr, destinationStr, weightStr;

            getline(ss, sourceStr, ',');
            getline(ss, destinationStr, ',');
            getline(ss, weightStr, ',');

            // Assign numeric IDs for source and destination
            int sourceId = getIntersectionId(sourceStr);
            int destinationId = getIntersectionId(destinationStr);

            // Convert weight and add edge to EmergencyVehicles
            int weight = stoi(weightStr);
            addEdge(sourceId, destinationId, weight);
        }

        file.close();
    }

    void loadEmergencyVehicles(const string &filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;

        // Skip the header line
        getline(file, line);

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string vehicleId, sourceStr, destinationStr, priorityStr;

            getline(ss, vehicleId, ',');
            getline(ss, sourceStr, ',');
            getline(ss, destinationStr, ',');
            getline(ss, priorityStr, ',');

            // Store the vehicle data
            vehicles[vehicleCount].id = vehicleId;
            vehicles[vehicleCount].source = getIntersectionId(sourceStr);
            vehicles[vehicleCount].destination = getIntersectionId(destinationStr);
            vehicles[vehicleCount].priority = priorityStr;

            vehicleCount++;
        }

        file.close();
    }

    void BFS(int start, int end)
    {
        // Arrays for BFS
        bool visited[vertices] = {false};
        int queue[vertices];
        int front = 0, rear = 0;

        // To track the shortest path
        int parent[vertices];
        for (int i = 0; i < vertices; i++)
            parent[i] = -1;

        // Enqueue the start vertex
        queue[rear++] = start;
        visited[start] = true;

        while (front != rear)
        {
            int current = queue[front++];
            if (current == end)
                break;

            for (int i = 0; i < vertices; i++)
            {
                if (adjMatrix[current][i] != INT_MAX && !visited[i])
                {
                    visited[i] = true;
                    queue[rear++] = i;
                    parent[i] = current;
                }
            }
        }

        // Print the shortest path
        if (!visited[end])
        {
            cout << "No path found from start to end." << endl;
            return;
        }

        // Trace back the path
        int path[vertices];
        int pathIndex = 0;
        for (int at = end; at != -1; at = parent[at])
            path[pathIndex++] = at;

        cout << "Shortest path: ";
        for (int i = pathIndex - 1; i >= 0; i--)
            cout << intersectionNames[path[i]] << (i > 0 ? " -> " : "");
        cout << endl;
    }

    void processVehicles()
    {
        // Process vehicles by priority
        for (int priorityLevel = 0; priorityLevel < 3; priorityLevel++)
        {
            string priorityStr = (priorityLevel == 0) ? "High" : (priorityLevel == 1) ? "Medium" : "Low";
            for (int i = 0; i < vehicleCount; i++)
            {
                if (vehicles[i].priority == priorityStr)
                {
                    cout << "Processing Vehicle ID: " << vehicles[i].id << " with priority: " << vehicles[i].priority << endl;
                    BFS(vehicles[i].source, vehicles[i].destination);
                }
            }
        }
    }

    void EmergencyRouting()
    {
        string sourceStr, destinationStr;

        cout << "Enter your desired source intersection: ";
        cin >> sourceStr;
        cout << "Enter your desired destination intersection: ";
        cin >> destinationStr;

        int sourceId = getIntersectionId(sourceStr);
        int destinationId = getIntersectionId(destinationStr);

        if (sourceId >= currentId || destinationId >= currentId)
        {
            cout << "Invalid intersections entered. Please try again." << endl;
            return;
        }

        BFS(sourceId, destinationId);
    }

    ~EmergencyVehicles()
    {
        for (int i = 0; i < vertices; i++)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};
int main()
{
    int vertices = 50;
    EmergencyVehicles Vehicles(vertices);

    // Load road network data
    string roadFilename = "road_network.csv";
    Vehicles.loadFromCSV(roadFilename);

    // Load emergency vehicle data
    string emergencyFilename = "emergency_vehicles.csv";
    Vehicles.loadEmergencyVehicles(emergencyFilename);

    // Process emergency vehicles
    Vehicles.processVehicles();

    Vehicles.EmergencyRouting();

    return 0;
}
