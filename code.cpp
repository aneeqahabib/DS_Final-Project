#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits> // For INT_MAX

using namespace std;

class Graph
{
private:
    int vertices;
    int **adjMatrix; // Adjacency matrix to store weights of edges

public:
    Graph(int v)
    {
        vertices = v;

        // Dynamically allocate memory for adjacency matrix
        adjMatrix = new int *[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adjMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
            {
                adjMatrix[i][j] = INT_MAX; // Initialize to a large value to represent no connection
            }
        }
    }

    void addEdge(int source, int destination, int weight)
    {
        adjMatrix[source][destination] = weight;
        adjMatrix[destination][source] = weight; // Assuming undirected graph
    }

    // Utility function to find all paths between source and destination
    void findAllPaths(int current, int destination, bool *visited, int *path, int &pathIndex, int &pathWeight)
    {
        visited[current] = true;
        path[pathIndex++] = current;

        // If the current node is the destination, print the path and its weight
        if (current == destination)
        {
            cout << "Path: ";
            for (int i = 0; i < pathIndex; i++)
            {
                cout << char('A' + path[i]);
                if (i != pathIndex - 1)
                    cout << " -> ";
            }
            cout << " | Total Weight: " << pathWeight << endl;
        }
        else
        {
            // Explore adjacent vertices
            for (int i = 0; i < vertices; i++)
            {
                if (!visited[i] && adjMatrix[current][i] != INT_MAX)
                {
                    pathWeight += adjMatrix[current][i];
                    findAllPaths(i, destination, visited, path, pathIndex, pathWeight);
                    pathWeight -= adjMatrix[current][i]; // Backtrack
                }
            }
        }

        // Backtrack
        visited[current] = false;
        pathIndex--;
    }

    void findAllPaths(int start, int end)
    {
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; i++)
            visited[i] = false;

        int *path = new int[vertices];
        int pathIndex = 0;
        int pathWeight = 0;

        cout << "Displaying all possible paths from " << char('A' + start) << " to " << char('A' + end) << ":\n";
        findAllPaths(start, end, visited, path, pathIndex, pathWeight);

        delete[] visited;
        delete[] path;
    }

    void printPath(int node, int *prev)
    {
        if (node == -1)
            return; // Base case: reached the start of the path

        printPath(prev[node], prev);

        if (prev[node] != -1)
        { // Check if not at the start
            cout << " -> ";
        }
        cout << char('A' + node);
    }

    void dijkstra(int start, int end)
    {
        int dist[vertices];     // Shortest distance from start to each vertex
        bool visited[vertices]; // To track visited vertices
        int prev[vertices];     // To store the shortest path tree

        // Initialize distances and visited
        for (int i = 0; i < vertices; i++)
        {
            dist[i] = INT_MAX;
            visited[i] = false;
            prev[i] = -1; // -1 indicates no previous node
        }

        dist[start] = 0; // Distance from start to itself is 0

        for (int count = 0; count < vertices - 1; count++)
        {
            // Find the unvisited vertex with the smallest distance
            int minDist = INT_MAX, u = -1;

            for (int i = 0; i < vertices; i++)
            {
                if (!visited[i] && dist[i] < minDist)
                {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1)
                break; // No more vertices
            visited[u] = true;

            // Update distances for neighbors of u
            for (int v = 0; v < vertices; v++)
            {
                if (!visited[v] && adjMatrix[u][v] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }

        // Display the shortest path and its distance
        if (dist[end] == INT_MAX)
        {
            cout << "No path exists from " << char('A' + start) << " to " << char('A' + end) << ".\n";
        }
        else
        {
            cout << "Shortest distance from " << char('A' + start) << " to " << char('A' + end) << ": " << dist[end] << endl;
            cout << "Path: ";
            printPath(end, prev);
            cout << endl;
        }
    }

    void loadFromCSV(Graph &graph, const string &filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        string line;
        const int max_Intersaction = 100; // Maximum number of unique intersections
        string intersectionNames[max_Intersaction];
        int currentId = 0;

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

            // Assigning numeric IDs for source and destination
            int sourceId = -1, destinationId = -1;
            for (int i = 0; i < currentId; i++)
            {
                if (intersectionNames[i] == sourceStr)
                    sourceId = i;
                if (intersectionNames[i] == destinationStr)
                    destinationId = i;
            }
            if (sourceId == -1)
                intersectionNames[sourceId = currentId++] = sourceStr;
            if (destinationId == -1)
                intersectionNames[destinationId = currentId++] = destinationStr;

            // Converting weight and adding edge to graphs
            int weight = stoi(weightStr);
            graph.addEdge(sourceId, destinationId, weight);
        }

        file.close();
    }

    ~Graph()
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
    Graph graph(vertices);

    // Loading data from CSV
    string filename = "road_network.csv";
    graph.loadFromCSV(graph, filename);

    // Input
    char startChar, endChar;
    cout << "Enter starting intersection: ";
    cin >> startChar;
    cout << "Enter ending intersection: ";
    cin >> endChar;

    int start = startChar - 'A';
    int end = endChar - 'A';

    // Finding and displaying all paths
    graph.findAllPaths(start, end);

    // Find and display the shortest path
    graph.dijkstra(start, end);

    return 0;
}
