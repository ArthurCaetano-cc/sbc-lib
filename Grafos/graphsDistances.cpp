#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <set>

using namespace std;

class Graph {
private:
    int n;  // Number of vertices
    unordered_map<int, vector<int>> adjacentList;
    vector<vector<float>> weightMatrix;

public:
    // Constructor
    Graph(int V) {
        n = V;
    }

    // Function to add an edge (undirected graph)
    void addEdge(int v, int w, float weight) {
        adjacentList[v].push_back(w);
        weightMatrix[v][w] = weight;
    }

    // Function to print the adjacency list representation of graph
    void printGraph() {
        for (int vertex = 0; vertex < n; vertex++) {
            cout << "Vertex " << vertex << " -> ";
            for (auto neighbor : adjacentList[vertex]) {
                float weight = weightMatrix[vertex][neighbor];
                cout << "(" << vertex << ", " << weight << ")"<< " ";
            }
            cout << endl;
        }
    }

    // dijkistra algorithm
    void dijkistra();


};

int main() {


    return 0;
}
