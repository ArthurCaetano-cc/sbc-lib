#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the minimum number of coins using a greedy approach
void coinChange(int amount, vector<int>& coins) {
    sort(coins.rbegin(), coins.rend()); 
    vector<int> result;

    for (int coin : coins) {
        while (amount >= coin) {
            amount -= coin;
            result.push_back(coin);
        }
    }

    for (int coin : result) {
        cout << coin << " ";
    }
    cout << endl;
}

int main() {
    int amount;
    cin >> amount;

    int n;
    cin >> n;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    coinChange(amount, coins);

    return 0;
}
