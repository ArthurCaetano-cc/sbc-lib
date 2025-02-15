#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to;
    int rev;
    int capacity;
};

void addEdge(vector<vector<Edge>>& graph, int u, int v, int capacity) {
    Edge forward = {v, (int)graph[v].size(), capacity};
    Edge reverse = {u, (int)graph[u].size(), 0};
    graph[u].push_back(forward);
    graph[v].push_back(reverse);
}

// Perform a BFS to find an augmenting path.
// parent[u] will store: (node from which we came to 'u', index of the edge in its adjacency list)
bool bfsEdmondsKarp(vector<vector<Edge>>& graph, int s, int t, vector<pair<int,int>>& parent) {
    fill(parent.begin(), parent.end(), make_pair(-1, -1));
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)graph[u].size(); i++) {
            Edge &e = graph[u][i];
            if (parent[e.to].first == -1 && e.capacity > 0 && e.to != s) {
                parent[e.to] = {u, i}; // came to 'e.to' from 'u' via edge index i
                if (e.to == t) {
                    return true; // We reached the sink
                }
                q.push(e.to);
            }
        }
    }
    return false;
}

int edmondsKarp(vector<vector<Edge>>& graph, int s, int t) {
    int max_flow = 0;
    // parent[v] = (u, i) means "we got to v from u using adjacency index i of u"
    vector<pair<int,int>> parent(graph.size());

    // While there is an augmenting path, send flow through it
    while (bfsEdmondsKarp(graph, s, t, parent)) {
        // Find the bottleneck capacity along the path
        int flow = INT_MAX;
        int v = t;
        while (v != s) {
            auto [u, idx] = parent[v];
            Edge &e = graph[u][idx];
            flow = min(flow, e.capacity);
            v = u;
        }

        // Update residual capacities
        v = t;
        while (v != s) {
            auto [u, idx] = parent[v];
            Edge &e = graph[u][idx];
            e.capacity -= flow;                       // Reduce forward edge capacity
            graph[e.to][e.rev].capacity += flow;      // Increase reverse edge capacity
            v = u;
        }

        // Add to max flow
        max_flow += flow;
    }

    return max_flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N);

    for (int i = 0; i < M; i++) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        // If 1-based indexing in input, do (u-1, v-1)
        addEdge(graph, u, v, capacity);
    }

    int source, sink;
    cin >> source >> sink;
    // If 1-based indexing in input, do source--, sink--;

    int maxFlow = edmondsKarp(graph, source, sink);
    cout << "Max Flow (Edmonds-Karp) = " << maxFlow << "\n";

    return 0;
}
