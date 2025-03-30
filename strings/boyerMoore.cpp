#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ALPHABET_SIZE 256

void buildBadCharTable(const string &pattern, vector<int> &badChar) {
    fill(badChar.begin(), badChar.end(), -1);
    for (int i = 0; i < pattern.size(); i++) {
        badChar[(int)pattern[i]] = i;
    }
}

void BoyerMooreSearch(const string &text, const string &pattern) {
    vector<int> badChar(ALPHABET_SIZE);
    buildBadCharTable(pattern, badChar);

    int m = pattern.size();
    int n = text.size();
    int s = 0;

    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            cout << "Pattern found at index " << s << endl;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }
}
