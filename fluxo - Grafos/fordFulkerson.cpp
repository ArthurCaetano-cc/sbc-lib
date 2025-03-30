#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 1000;
int capacity[MAXN][MAXN];  // Capacidade da aresta de u para v
vector<int> adj[MAXN];     // Lista de adjacência
bool visited[MAXN];

int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            int curr_flow = min(flow, capacity[u][v]);
            int temp_flow = dfs(v, t, curr_flow);

            if (temp_flow > 0) {
                capacity[u][v] -= temp_flow;
                capacity[v][u] += temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

int fordFulkerson(int s, int t, int n) {
    int max_flow = 0;

    while (true) {
        memset(visited, 0, sizeof(visited));
        int flow = dfs(s, t, INT_MAX);
        if (flow == 0) break;
        max_flow += flow;
    }

    return max_flow;
}

int main() {
    int n, m;
    cout << "Digite o número de vértices e arestas: ";
    cin >> n >> m;

    memset(capacity, 0, sizeof(capacity));

    cout << "Digite as arestas (u v capacidade):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u);  // Para grafo residual
    }

    int s, t;
    cout << "Digite o vértice de origem e o de destino: ";
    cin >> s >> t;

    int maxFlow = fordFulkerson(s, t, n);
    cout << "O fluxo máximo é: " << maxFlow << endl;

    return 0;
}
