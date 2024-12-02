#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// represent roads (destination and weight)
class Edge
{
public:
    int weight;
    char destination;
    Edge *next;

    Edge(char dest, int w)
    {
        destination = dest;
        weight = w;
        next = NULL;
    }
};

// represent each intersection
class Node
{
public:
    char car;
    Node *next;
    Edge *head;

    Node(char c)
    {
        car = c;
        next = NULL;
        head = NULL;
    }
};
class CityTrafficNetwork
{
    Node *head;

public:
    CityTrafficNetwork()
    {
        head = NULL;
    }
    Node *findcar(char c)
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->car == c)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
    // adding node
    void addcar(char c)
    {
        if (findcar(c) != nullptr)
        {
            // cout << "Node " << c << "already exist" << endl;
        }
        else
        {
            Node *newnode = new Node(c);
            // If the list is empty or the new node should be the first node
            if (head == nullptr || head->car > c)
            {
                newnode->next = head;
                head = newnode;
                return;
            }

            // Insert in sorted order
            Node *current = head;
            while (current->next != nullptr && current->next->car < c)
            {
                current = current->next;
            }

            newnode->next = current->next;
            current->next = newnode;
        }
    }
    // adding road
    void addroad(char car1, char car2, int weight)
    {
        Node *car1_intersection = findcar(car1);
        Node *car2_intersection = findcar(car2);
        if (car1_intersection == nullptr || car2_intersection == nullptr)
        {
            cout << "Intersection do not exist" << endl;
            return;
        }
        Edge *newnode = new Edge(car2, weight);
        // adjacency list
        if (car1_intersection->head == nullptr)
        {
            car1_intersection->head = newnode;
        }
        else
        {

            Edge *current = car1_intersection->head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newnode;
        }
    }
    // Removing a road
    void removeroad(char car1, char car2)
    {
        Node *car1_intersection = findcar(car1);

        if (car1_intersection == nullptr)
        {
            cout << "Intersection " << car1 << " does not exist" << endl;
            return;
        }

        Edge *current = car1_intersection->head;
        Edge *prev = nullptr;

        while (current != nullptr && current->destination != car2)
        {
            prev = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            cout << "Road from " << car1 << " to " << car2 << " does not exist" << endl;
            return; // Road not found
        }

        // Remove the edge
        if (prev == nullptr)
        { // The edge to remove is the first edge
            car1_intersection->head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        delete current; 
    }

    // Removing an intersection
    void removeintersection(char c)
    {
        Node *current = head, *prev = nullptr;

        while (current != nullptr && current->car != c)
        {
            prev = current;
            current = current->next;
        }

        if (current == nullptr)
        { // Intersection not found
            cout << "Intersection " << c << " does not exist" << endl;
            return;
        }

        // Remove all edges from this intersection
        while (current->head != nullptr)
        {
            Edge *tempEdge = current->head;
            current->head = current->head->next;
            delete tempEdge;
        }

        // Remove the node from the list of intersections
        if (prev == nullptr)
        { 
            // The node to remove is the head
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        delete current; // Free memory
    }

    void loadfromcsv(const string &filename)
    {
        ifstream file(filename);
        string line;

        if (!file.is_open())
        {
            cout << filename << "doesnot opened. " << endl;
            return;
        }
        while (getline(file, line))
        {
            stringstream ss(line);
            string intersection1, intersection2, time;
            char intersection1Name, intersection2Name;
            int travelTime;

            // Parse each line
            getline(ss, intersection1, ',');
            getline(ss, intersection2, ',');
            getline(ss, time);

            intersection1Name = intersection1[0];
            intersection2Name = intersection2[0];
            stringstream(time) >> travelTime;

            // Add cars
            addcar(intersection1Name);
            addcar(intersection2Name);

            // Add the road between the intersections
            addroad(intersection1Name, intersection2Name, travelTime);
        }

        file.close();
    }
    void displayGraph()
    {
        cout << "----- City Traffic Network ------" << endl;
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->car << " -->";
            Edge *edge = temp->head;
            while (edge != NULL)
            {
                cout << "(" << edge->destination << "," << edge->weight << ") ";
                edge = edge->next;
            }
            cout << endl;
            temp = temp->next;
        }
    }
};
int main()
{
    CityTrafficNetwork ctn;
    ctn.loadfromcsv("road_network.csv");
    ctn.displayGraph();
    return 0;
}