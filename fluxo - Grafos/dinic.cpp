#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 1000;
vector<int> adj[MAXN];
int capacity[MAXN][MAXN];
int level[MAXN];       // Nível de cada vértice
int ptr[MAXN];         // Ponteiro usado no DFS

bool bfs(int s, int t, int n) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    return level[t] != -1;
}

int dfs(int u, int t, int flow) {
    if (u == t) return flow;

    for (int& i = ptr[u]; i < adj[u].size(); ++i) {
        int v = adj[u][i];

        if (capacity[u][v] > 0 && level[v] == level[u] + 1) {
            int pushed = dfs(v, t, min(flow, capacity[u][v]));
            if (pushed > 0) {
                capacity[u][v] -= pushed;
                capacity[v][u] += pushed;
                return pushed;
            }
        }
    }

    return 0;
}

int dinic(int s, int t, int n) {
    int max_flow = 0;

    while (bfs(s, t, n)) {
        memset(ptr, 0, sizeof(ptr));
        while (int pushed = dfs(s, t, INT_MAX)) {
            max_flow += pushed;
        }
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
        if (capacity[u][v] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        capacity[u][v] += cap;
    }

    int s, t;
    cout << "Digite o vértice de origem e o de destino: ";
    cin >> s >> t;

    int maxFlow = dinic(s, t, n);
    cout << "O fluxo máximo é: " << maxFlow << endl;

    return 0;
}
