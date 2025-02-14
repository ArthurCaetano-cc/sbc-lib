#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

class Graph {
private:
    int n; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix
    unordered_map<char, int> vertexToIndex; // Mapping from vertex labels to indices
    unordered_map<int, char> indexToVertex; // Mapping from indices to vertex labels
    int indexCounter = 0;

    // Helper function to get index for a vertex, creating if it doesn't exist
    int getIndex(char vertex) {
        if (vertexToIndex.find(vertex) == vertexToIndex.end()) {
            vertexToIndex[vertex] = indexCounter;
            indexToVertex[indexCounter] = vertex;
            indexCounter++;
            // Resize the matrix if needed
            adjMatrix.resize(indexCounter, vector<int>(indexCounter, 0));
        }
        return vertexToIndex[vertex];
    }

public:
    // Constructor
    Graph(int V) {
        n = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    // Function to add an edge (undirected graph)
    void addEdge(char v, char w) {
        int i = getIndex(v);
        int j = getIndex(w);
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1; // Remove this line if working with directed graphs
    }

    // Function to print the adjacency matrix
    void printGraph() {
        cout << "  ";
        for (int i = 0; i < indexCounter; i++) {
            cout << indexToVertex[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < indexCounter; i++) {
            cout << indexToVertex[i] << " ";
            for (int j = 0; j < indexCounter; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void dfs(char start) {
        unordered_map<int, bool> visited;
        stack<int> s;
        int startIndex = getIndex(start);

        s.push(startIndex);
        visited[startIndex] = true;

        while (!s.empty()) {
            int v = s.top();
            s.pop();
            cout << "Visited " << indexToVertex[v] << endl;

            for (int w = 0; w < indexCounter; w++) {
                if (adjMatrix[v][w] && !visited[w]) {
                    cout << indexToVertex[v] << " -> " << indexToVertex[w] << endl;
                    s.push(w);
                    visited[w] = true;
                }
            }
        }
    }

    void bfs(char start) {
        unordered_map<int, bool> visited;
        queue<int> q;
        int startIndex = getIndex(start);

        q.push(startIndex);
        visited[startIndex] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << "Visited " << indexToVertex[v] << endl;

            for (int w = 0; w < indexCounter; w++) {
                if (adjMatrix[v][w] && !visited[w]) {
                    cout << indexToVertex[v] << " -> " << indexToVertex[w] << endl;
                    q.push(w);
                    visited[w] = true;
                }
            }
        }
    }

    // Handle disconnected graphs
    void dfsAll() {
        unordered_map<int, bool> visited;
        for (int i = 0; i < indexCounter; i++) {
            if (!visited[i]) {
                dfs(indexToVertex[i]);
            }
        }
    }

    void bfsAll() {
        unordered_map<int, bool> visited;
        for (int i = 0; i < indexCounter; i++) {
            if (!visited[i]) {
                bfs(indexToVertex[i]);
            }
        }
    }
};

int main() {
    Graph g(9);
    g.addEdge('A', 'G');
    g.addEdge('A', 'B');
    g.addEdge('B', 'C');
    g.addEdge('B', 'D');
    g.addEdge('B', 'E');
    g.addEdge('E', 'F');
    g.addEdge('G', 'H');
    g.addEdge('H', 'I');

    cout << "Adjacency Matrix:" << endl;
    g.printGraph();

    cout << "\nDFS (all components):" << endl;
    g.dfsAll();

    cout << "\nBFS (all components):" << endl;
    g.bfsAll();

    return 0;
}