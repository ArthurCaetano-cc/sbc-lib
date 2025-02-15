#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// DFS:

// A helper (recursive) function that visits nodes reachable from `vertex`.
void DFSUtil(const vector<vector<int>>& adjMatrix, int vertex, vector<bool>& visited)
{
    // Mark the current vertex as visited
    visited[vertex] = true;
    cout << vertex << " ";

    // For every adjacent vertex to 'vertex', visit if not visited
    for (int i = 0; i < (int)adjMatrix.size(); i++)
    {
        // If there is an edge from 'vertex' to 'i' and 'i' is not visited
        // (We check `adjMatrix[vertex][i] != 0` to see if an edge exists.)
        if (adjMatrix[vertex][i] != 0 && !visited[i])
        {
            DFSUtil(adjMatrix, i, visited);
        }
    }
}

// Depth-First Search (entry point)
void DFS(const vector<vector<int>>& adjMatrix, int start)
{
    int n = (int)adjMatrix.size();
    vector<bool> visited(n, false);

    // Call the recursive helper function
    DFSUtil(adjMatrix, start, visited);
    cout << endl;
}

// BFS:

void BFS(const vector<vector<int>>& adjMatrix, int start)
{
    int n = (int)adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;

    // Mark the start vertex as visited and enqueue it
    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        cout << current << " ";

        // Enqueue all adjacent vertices not yet visited
        for (int i = 0; i < n; i++)
        {
            // If there is an edge from 'current' to 'i' and 'i' is not visited
            if (adjMatrix[current][i] != 0 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

// -------------------- MAIN FUNCTION (Example Usage) --------------------

int main()
{
    int N;
    cout << "Enter the number of vertices: ";
    cin >> N;

    // Initialize an NxN adjacency matrix
    vector<vector<int>> adjMatrix(N, vector<int>(N, 0));

    cout << "Enter the adjacency matrix (row by row):\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> adjMatrix[i][j];
        }
    }

    int start;
    cout << "Enter the starting vertex for DFS/BFS: ";
    cin >> start;

    cout << "DFS traversal starting from vertex " << start << ": ";
    DFS(adjMatrix, start);

    cout << "BFS traversal starting from vertex " << start << ": ";
    BFS(adjMatrix, start);

    return 0;
}
