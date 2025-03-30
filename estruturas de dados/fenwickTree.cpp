#include <iostream>
#include <vector>

class FenwickTree {
private:
    std::vector<int> bit; // Binary Indexed Tree
    int n;

public:
    // Construtor com tamanho
    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0); // índice 0 não é usado
    }

    // Construtor a partir de vetor
    FenwickTree(const std::vector<int>& a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); ++i) {
            update(i, a[i]);
        }
    }

    // Soma prefixada até o índice i (inclusive)
    int query(int i) {
        int sum = 0;
        for (++i; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    // Soma no intervalo [l, r]
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Adiciona valor 'delta' na posição 'i'
    void update(int i, int delta) {
        for (++i; i <= n; i += i & -i)
            bit[i] += delta;
    }
};

// Exemplo de uso
int main() {
    std::vector<int> a = {1, 7, 3, 0, 7, 8, 3, 2, 6, 2};
    FenwickTree ft(a);

    std::cout << "Soma de 0 a 4: " << ft.query(0, 4) << "\n";  // Deve imprimir 18
    ft.update(3, 5);  // Incrementa o valor da posição 3 em 5
    std::cout << "Soma de 0 a 4 após update: " << ft.query(0, 4) << "\n";  // Deve imprimir 23

    return 0;
}
