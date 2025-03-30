#include <iostream>
using namespace std;

int binomialRecursive(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomialRecursive(n - 1, k - 1) + binomialRecursive(n - 1, k);
}

long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

long long binomialAnalytical(int n, int k) {
    if (k < 0 || k > n) return 0;
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int n = 5, k = 2;

    cout << "Recursivo: C(" << n << "," << k << ") = " << binomialRecursive(n, k) << endl;
    cout << "Analítico: C(" << n << "," << k << ") = " << binomialAnalytical(n, k) << endl;

    return 0;
}
