#include <iostream>
#include <vector>
#include <algorithm>
#include <map> // Use map instead of unordered_map

using namespace std;

void bucketSort(vector<int>& numbers, int n) {

    map<int, vector<int>> buckets; 

    // Putting the numbers inside their corresponding buckets
    for (int i = 0; i < n; i++) {
        buckets[numbers[i]].push_back(numbers[i]);
    }

    // Sorting and placing back into original vector
    int index = 0;
    for (auto& [key, numberVector] : buckets) { 
        for (int value : numberVector) {
            numbers[index++] = value;
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    bucketSort(numbers, n);

    for (int i = 0; i < n; i++) {
        cout << numbers[i];
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl; 

    return 0;
}
