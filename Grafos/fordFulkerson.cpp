#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// A structure to represent an edge in the adjacency list.
// 'rev' is the index of the reverse edge in the adjacency list of 'to'.
struct Edge {
    int to;       // The endpoint of this edge
    int rev;      // Index of the reverse edge (needed for updating residual capacity)
    int capacity; // Capacity of this edge
};

// Adds a directed edge u->v to the flow network with the given capacity.
// Also adds the reverse edge v->u with 0 capacity initially.
void addEdge(vector<vector<Edge>>& graph, int u, int v, int capacity) {
    Edge forward = {v, (int)graph[v].size(), capacity};
    Edge reverse = {u, (int)graph[u].size(), 0};
    graph[u].push_back(forward);
    graph[v].push_back(reverse);
}

// DFS-based function to send flow after finding a path.
// Tries to send 'flow' units from 'u' to 't' in the residual graph.
int sendFlowFordFulkerson(vector<vector<Edge>>& graph, int u, int t, int flow, vector<bool>& visited) {
    // If we reached the sink, we can send the current flow
    if (u == t) return flow;

    visited[u] = true;

    // Explore all adjacent edges
    for (auto &e : graph[u]) {
        if (!visited[e.to] && e.capacity > 0) {
            // Try sending the minimum of the available capacity and the requested flow
            int curr_flow = min(flow, e.capacity);
            int temp_flow = sendFlowFordFulkerson(graph, e.to, t, curr_flow, visited);

            // If we could send some flow
            if (temp_flow > 0) {
                // Adjust residual capacities
                e.capacity -= temp_flow;                     // Reduce forward capacity
                graph[e.to][e.rev].capacity += temp_flow;    // Increase reverse capacity
                return temp_flow;
            }
        }
    }
    return 0; // No flow could be sent from this path
}

// Ford-Fulkerson main function
int fordFulkerson(vector<vector<Edge>>& graph, int s, int t) {
    int max_flow = 0;
    while (true) {
        // Use DFS to find if more flow can be sent
        vector<bool> visited(graph.size(), false);

        // Find a flow in the residual graph
        int flow = sendFlowFordFulkerson(graph, s, t, INT_MAX, visited);
        if (flow <= 0)
            break; // No augmenting path found

        // Add path flow to overall flow
        max_flow += flow;
    }
    return max_flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // Create an adjacency list for the flow network
    vector<vector<Edge>> graph(N);

    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v, capacity;
        cin >> u >> v >> capacity; 
        // Adjust if input is 1-based indexing; 
        // if your input is 0-based, remove these adjustments
        // For example: if vertices are 1..N, do (u-1, v-1).
        addEdge(graph, u, v, capacity);
    }

    int source, sink;
    cin >> source >> sink; 
    // If your input is 1-based, do source--, sink--;

    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "Max Flow (Ford-Fulkerson) = " << maxFlow << "\n";

    return 0;
}
