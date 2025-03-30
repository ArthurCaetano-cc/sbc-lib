#include <iostream>
#include <vector>
using namespace std;

vector<int> buildLPS(const string &pattern) {
    int n = pattern.size();
    vector<int> lps(n, 0);
    int len = 0, i = 1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

void KMPSearch(const string &text, const string &pattern) {
    vector<int> lps = buildLPS(pattern);
    int i = 0, j = 0;
    while (i < text.size()) {
        if (text[i] == pattern[j]) {
            i++, j++;
        }
        if (j == pattern.size()) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < text.size() && text[i] != pattern[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}
