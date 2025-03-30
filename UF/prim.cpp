#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // (peso, vértice)

const int MAXN = 1000;
vector<pii> adj[MAXN];
bool visited[MAXN];

int prim(int start, int n) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    int mst_weight = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        mst_weight += w;

        for (auto [v_w, v] : adj[u]) {
            if (!visited[v])
                pq.push({v_w, v});
        }
    }

    return mst_weight;
}

int main() {
    int n, m;
    cout << "Número de vértices e arestas: ";
    cin >> n >> m;

    cout << "Digite as arestas (u v peso):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    int total = prim(0, n);
    cout << "Peso total da AGM: " << total << endl;

    return 0;
}
