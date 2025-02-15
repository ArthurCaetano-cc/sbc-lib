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

// BFS to build level graph
bool buildLevelGraph(vector<vector<Edge>>& graph, int s, int t, vector<int>& level) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &e : graph[u]) {
            if (level[e.to] < 0 && e.capacity > 0) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] >= 0;
}

// DFS to send flow along blocking paths in level graph
int sendFlowDinic(vector<vector<Edge>>& graph, int u, int t, int flow, vector<int>& level, vector<int>& start) {
    if (u == t) return flow;

    for (int &i = start[u]; i < (int)graph[u].size(); i++) {
        Edge &e = graph[u][i];
        if (level[e.to] == level[u] + 1 && e.capacity > 0) {
            int curr_flow = min(flow, e.capacity);
            int temp_flow = sendFlowDinic(graph, e.to, t, curr_flow, level, start);

            if (temp_flow > 0) {
                e.capacity -= temp_flow;                      // Reduce capacity in forward edge
                graph[e.to][e.rev].capacity += temp_flow;     // Increase capacity in reverse edge
                return temp_flow;
            }
        }
    }
    return 0;
}

int dinicMaxFlow(vector<vector<Edge>>& graph, int s, int t) {
    int max_flow = 0;
    vector<int> level(graph.size());

    // While we can build a level graph
    while (buildLevelGraph(graph, s, t, level)) {
        // 'start' will track which edges have been visited from a node
        // to speed up DFS
        vector<int> start(graph.size(), 0);

        // Send flow while possible
        while (true) {
            int flow = sendFlowDinic(graph, s, t, INT_MAX, level, start);
            if (flow <= 0) break;
            max_flow += flow;
        }
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
        // If 1-based indexing, do (u-1, v-1)
        addEdge(graph, u, v, capacity);
    }

    int source, sink;
    cin >> source >> sink;
    // If 1-based indexing, do source--, sink--;

    int maxFlow = dinicMaxFlow(graph, source, sink);
    cout << "Max Flow (Dinic) = " << maxFlow << "\n";

    return 0;
}
