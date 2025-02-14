#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;


class Graph {
private:
    int n;  // Number of vertices
    unordered_map<char, vector<char>> adjacentList; 

public:
    // Constructor
    Graph(int V) {
        n = V;
    }

    // Function to add an edge (undirected graph)
    void addEdge(char v, char w) {
        adjacentList[v].push_back(w);
        adjacentList[w].push_back(v); // Erase if working with directed graphs
    }

    // Function to print the adjacency list representation of graph
    void printGraph() {
        for (const auto& pair : adjacentList) {
            cout << "Vertex " << pair.first << " -> ";
            for (const auto& neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void dfs(char start) {
        unordered_map<char, bool> visited;
        stack<char> s;

        s.push(start);
        visited[start] = true;  // Mark as visited when pushing

        while (!s.empty()) {
            char v = s.top();
            s.pop();  // Pop after processing the node
            cout << "Visited " << v << endl;

            // Iterate over neighbors
            for (auto w : adjacentList[v]) {
                if (!visited[w]) {
                    cout << v << " -> " << w << endl;
                    s.push(w);           // Push neighbor onto the stack
                    visited[w] = true;   // Mark as visited when pushing
                }
            }
        }
    }

    void bfs(char start) {
        unordered_map<char, bool> visited;
        queue<char> q;

        q.push(start);
        visited[start] = true;  // Mark as visited when pushing

        while (!q.empty()) {
            char v = q.front();
            q.pop();  // Pop after processing the node
            cout << "Visited " << v << endl;

            // Iterate over neighbors
            for (auto w : adjacentList[v]) {
                if (!visited[w]) {
                    cout << v << " -> " << w << endl;
                    q.push(w);           
                    visited[w] = true;   
                }
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

    cout << "Dfs:" << endl;
    g.dfs('A');

    cout << "Bfs:" << endl;
    
    g.bfs('A');

    return 0;
}
