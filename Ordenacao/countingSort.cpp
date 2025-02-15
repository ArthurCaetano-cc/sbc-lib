#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    // Find the maximum and minimum element
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    // Create and initialize count array
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    
    // Store the count of each element
    for (int num : arr) {
        count[num - minVal]++;
    }
    
    // Change count[i] so that it contains the actual position of this element
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // Build the output array
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    // Copy sorted elements back to original array
    arr = output;
}

int main() {
    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    countingSort(numbers);

    for (int i = 0; i < n; i++) {
        cout << numbers[i];
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl; 
    
    return 0;
}
