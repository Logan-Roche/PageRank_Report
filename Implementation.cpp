/******************************************************************************
 *                                                                            *
 *                               Page Rank Project                            *
 *                                   CSCI 411                                 *
 *                                                                            *
 *                              Author: Logan Roche                           *
 *                                                                            *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <memory>
#include <numeric>
#include <string>

using namespace std;

// Node class representing a single webpage in the graph
class Node
{
public:
    string name;                       // Name or identifier for the node
    vector<shared_ptr<Node>> children; // Outgoing links (children)
    vector<shared_ptr<Node>> parents;  // Incoming links (parents)
    float hub;                         // Hub score (optional, for extensions)
    float pagerank;                    // PageRank score

    // Constructor to initialize the node with a name and default scores
    Node(string n)
    {
        name = n;
        hub = 1.0;
        pagerank = 1.0;
    }

    // Method to update the PageRank value for the node based on its neighbors
    void Update_PageRank(shared_ptr<Node> page, float damping_factor, float n);
};

// Update PageRank for a node based on its parents and the damping factor
void Node::Update_PageRank(shared_ptr<Node> page, float damping_factor, float n)
{
    vector<shared_ptr<Node>> in_neighbors = page->parents;

    // Calculate the sum of the PageRank contributions from incoming links
    float pagerank_sum = 0;
    for (const auto &neighbor : in_neighbors)
    {
        if (!neighbor->children.empty())
        {
            pagerank_sum += (neighbor->pagerank / neighbor->children.size());
        }
    }

    // Apply the PageRank formula with a random walk component and damping factor
    float random_walk = (1 - damping_factor) / n;
    page->pagerank = random_walk + damping_factor * pagerank_sum;
}

// Graph class representing the entire web of nodes/pages
class Graph
{
public:
    vector<shared_ptr<Node>> nodes; // Collection of nodes in the graph
};

// Perform one iteration of the PageRank algorithm for the entire graph
void PageRank_One_Iteration(shared_ptr<Graph> graph, float damping_factor)
{
    vector<shared_ptr<Node>> node_list = graph->nodes;

    // Update the PageRank value for each node
    for (int i = 0; i < node_list.size(); i++)
    {
        node_list[i]->Update_PageRank(node_list[i], damping_factor, graph->nodes.size());
    }

    // Normalize the PageRank values to ensure they sum to 1
    float total_pagerank = 0.0;
    for (const auto &node : graph->nodes)
    {
        total_pagerank += node->pagerank;
    }

    for (auto &node : graph->nodes)
    {
        node->pagerank /= total_pagerank;
    }
}

// Compute PageRank iteratively until convergence
void Compute_PageRank(shared_ptr<Graph> graph, float damping_factor)
{
    bool has_converged = false;
    float epsilon = 1e-6; // Small threshold for convergence

    while (!has_converged)
    {
        has_converged = true; // Assume convergence until proven otherwise
        vector<float> old_pageranks;

        // Store the current PageRank values
        for (const auto &node : graph->nodes)
        {
            old_pageranks.push_back(node->pagerank);
        }

        // Perform one iteration of the PageRank algorithm
        PageRank_One_Iteration(graph, damping_factor);

        // Check if the PageRank values have converged
        for (size_t i = 0; i < graph->nodes.size(); ++i)
        {
            if (abs(old_pageranks[i] - graph->nodes[i]->pagerank) > epsilon)
            {
                has_converged = false; // If any value changes significantly, not converged
                break;
            }
        }
    }
}

// Build the graph from user input
shared_ptr<Graph> Build_Graph()
{
    shared_ptr<Graph> Temp_Graph = make_shared<Graph>();
    int Number_of_Nodes;
    int Number_of_Vertices;

    // Prompt the user to enter the number of nodes
    cout << "===================================" << endl;
    cout << "         Graph Input Setup         " << endl;
    cout << "===================================" << endl;
    cout << "Enter the number of nodes: ";
    cin >> Number_of_Nodes;

    // Prompt the user to enter the number of vertices
    cout << "Enter the number of edges (vertices): ";
    cin >> Number_of_Vertices;

    cout << "\nCreating " << Number_of_Nodes << " nodes..." << endl;

    // Create nodes and add them to the graph
    for (int i = 1; i <= Number_of_Nodes; i++)
    {
        Temp_Graph->nodes.push_back(make_shared<Node>(to_string(i)));
    }

    cout << "\nNodes created successfully!" << endl;
    cout << "Now, enter the edges (connections) between nodes:" << endl;
    cout << "Format: <Start_Node> <End_Node>" << endl;
    cout << "Example: 1 2 (indicating a link from Node 1 to Node 2)" << endl;
    cout << "-----------------------------------" << endl;

    // Input edges and create connections
    for (int i = 0; i < Number_of_Vertices; i++)
    {
        int Start_Node, End_Node;

        cout << "Edge " << i + 1 << ": ";
        cin >> Start_Node >> End_Node;

        // Establish relationships between nodes
        shared_ptr<Node> Start_Node_Pointer = Temp_Graph->nodes[Start_Node - 1];
        shared_ptr<Node> End_Node_Pointer = Temp_Graph->nodes[End_Node - 1];

        Start_Node_Pointer->children.push_back(End_Node_Pointer);
        End_Node_Pointer->parents.push_back(Start_Node_Pointer);
    }

    cout << "\nGraph successfully built!" << endl
         << endl;

    return Temp_Graph;
}

// Print the PageRank of all nodes in the graph
void Print_Graph(shared_ptr<Graph> graph)
{
    cout << "===================================" << endl;
    cout << "            Page Rank              " << endl;
    cout << "===================================" << endl;

    // Print each node's PageRank in a clean format
    for (const auto &node : graph->nodes)
    {
        cout << "Node " << node->name << ": ";
        printf("%.3f", node->pagerank);
        cout << endl;
    }

    cout << "===================================" << endl;
}

// Main function to execute the PageRank algorithm
int main()
{
    shared_ptr<Graph> graph = Build_Graph(); // Build the graph from user input

    Compute_PageRank(graph, .85); // Compute PageRank with a damping factor of 0.85

    Print_Graph(graph); // Print the computed PageRank values

    return 0;
}
