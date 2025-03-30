#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

const int MAXN = 1000;
int parent[MAXN], rankSet[MAXN];

void make_set(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rankSet[i] = 0;
    }
}

int find(int u) {
    if (u != parent[u])
        parent[u] = find(parent[u]); // Path compression
    return parent[u];
}

bool union_sets(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (rankSet[u] < rankSet[v])
        swap(u, v);
    parent[v] = u;
    if (rankSet[u] == rankSet[v])
        rankSet[u]++;
    return true;
}

int kruskal(int n, vector<Edge>& edges) {
    make_set(n);
    sort(edges.begin(), edges.end());

    int mst_weight = 0;
    vector<Edge> mst;

    for (const Edge& e : edges) {
        if (union_sets(e.u, e.v)) {
            mst_weight += e.weight;
            mst.push_back(e);
        }
    }

    cout << "Arestas da Árvore Geradora Mínima (Kruskal):\n";
    for (const Edge& e : mst)
        cout << e.u << " - " << e.v << " = " << e.weight << '\n';

    return mst_weight;
}

int main() {
    int n, m;
    cout << "Número de vértices e arestas: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Digite as arestas (u v peso):\n";
    for (int i = 0; i < m; ++i)
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    int total = kruskal(n, edges);
    cout << "Peso total da AGM: " << total << endl;

    return 0;
}
