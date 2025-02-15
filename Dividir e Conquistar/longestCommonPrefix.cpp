#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Complexidade O(n*m) ou O(n*log n)
// Função para encontrar o pré-fixo comum mais longo
string commonPrefix(string &str1, string &str2) {
    int minLength = min(str1.length(), str2.length());
    for (int i = 0; i < minLength; i++) {
        if (str1[i] != str2[i]) {
            return str1.substr(0, i); // Retorna o pré-fixo comum encontrado
        }
    }
    return str1.substr(0, minLength); // Se as strings forem iguais
}

// Divide and Conquer approach based on MergeSort
string longestCommonPrefix(vector<string> &strs, int low, int high) {
    // Caso base, string sozinha
    if (low == high) {
        return strs[low];
    }

    // Pegar o index do meio
    int mid = (low + high) / 2;

    // Encontra recursivamente o pre-fixo em comum de cada metade
    string leftLCP = longestCommonPrefix(strs, low, mid);
    string rightLCP = longestCommonPrefix(strs, mid + 1, high);

    // Junção(Merge step): Encontra o prefixo comum entre as duas metades
    return commonPrefix(leftLCP, rightLCP);
}

int main() {
    vector<string> strs = {"flower", "flow", "flight"};

    // Chamada da função
    string result = longestCommonPrefix(strs, 0, strs.size() - 1);

    // Resultado
    cout << "Longest Common Prefix: " << result << endl;

    return 0;
}
