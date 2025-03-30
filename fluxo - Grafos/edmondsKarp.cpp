#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 1000;
int capacity[MAXN][MAXN];
int parent[MAXN];
vector<int> adj[MAXN];

bool bfs(int s, int t, int n) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(s);
    parent[s] = -2;  // Para identificar a origem
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == t)
                    return true;
                q.push(v);
            }
        }
    }
    return false;
}

int edmondsKarp(int s, int t, int n) {
    int max_flow = 0;

    while (bfs(s, t, n)) {
        int flow = INT_MAX;

        // Voltar pelo caminho e encontrar gargalo
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow = min(flow, capacity[u][v]);
        }

        // Atualizar capacidades no grafo residual
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= flow;
            capacity[v][u] += flow;
        }

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
        capacity[u][v] += cap;  // Suporta múltiplas arestas entre os mesmos nós
        adj[u].push_back(v);
        adj[v].push_back(u);    // Grafo residual
    }

    int s, t;
    cout << "Digite o vértice de origem e o de destino: ";
    cin >> s >> t;

    int maxFlow = edmondsKarp(s, t, n);
    cout << "O fluxo máximo é: " << maxFlow << endl;

    return 0;
}
