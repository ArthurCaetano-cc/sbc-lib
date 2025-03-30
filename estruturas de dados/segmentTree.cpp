#include <iostream>
#include <vector>

class SegmentTree {
private:
    std::vector<int> tree, lazy;
    int n;

    void build(const std::vector<int>& a, int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node, start, mid);
            build(a, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;  // fora do intervalo
        if (l <= start && end <= r) return tree[node]; // completamente dentro

        int mid = (start + end) / 2;
        int q1 = query(2 * node, start, mid, l, r);
        int q2 = query(2 * node + 1, mid + 1, end, l, r);
        return q1 + q2;
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (r < start || end < l) return;  // fora do intervalo

        if (l <= start && end <= r) {
            tree[node] += (end - start + 1) * val;
            if (start != end) {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }

        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val);
        updateRange(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

public:
    SegmentTree(const std::vector<int>& a) {
        n = a.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(a, 1, 0, n - 1);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void updateRange(int l, int r, int val) {
        updateRange(1, 0, n - 1, l, r, val);
    }
};

// Exemplo de uso
int main() {
    std::vector<int> a = {1, 3, 5, 7, 9, 11};
    SegmentTree st(a);

    std::cout << "Soma de 1 a 3: " << st.query(1, 3) << "\n";  // 3 + 5 + 7 = 15
    st.update(1, 10);  // altera a[1] para 10
    std::cout << "Soma de 1 a 3 após update: " << st.query(1, 3) << "\n";  // 10 + 5 + 7 = 22
    st.updateRange(1, 4, 2);  // incrementa de 1 a 4 com +2
    std::cout << "Soma de 1 a 3 após incremento em intervalo: " << st.query(1, 3) << "\n";  // 12 + 7 + 9 = 28

    return 0;
}
