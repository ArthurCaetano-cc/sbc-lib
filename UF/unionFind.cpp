#include <iostream>

using namespace std;

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
        parent[u] = find(parent[u]);  // Path compression
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

int main() {
    int n = 5;
    make_set(n);

    union_sets(0, 1);
    union_sets(1, 2);
    union_sets(3, 4);

    cout << "0 e 2 estão no mesmo conjunto? " << (find(0) == find(2)) << endl;
    cout << "0 e 4 estão no mesmo conjunto? " << (find(0) == find(4)) << endl;

    union_sets(2, 4);
    cout << "0 e 4 estão no mesmo conjunto após união? " << (find(0) == find(4)) << endl;

    return 0;
}
