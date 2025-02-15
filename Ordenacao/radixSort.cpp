#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A utility function to get the maximum value in the array
int getMax(const vector<int>& numbers) {
    return *max_element(numbers.begin(), numbers.end());
}

// A function to perform counting sort based on a specific digit (exp)
void countingSort(vector<int>& numbers, int exp) {
    int n = numbers.size();
    vector<int> output(n); // Output array
    vector<int> count(10, 0); // Count array for digits 0-9

    // Count occurrences of each digit in the given place (exp)
    for (int i = 0; i < n; i++) {
        int digit = (numbers[i] / exp) % 10;
        count[digit]++;
    }

    // Compute prefix sum to get the actual positions in output array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array by placing elements in the correct order
    for (int i = n - 1; i >= 0; i--) {
        int digit = (numbers[i] / exp) % 10;
        output[count[digit] - 1] = numbers[i];
        count[digit]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++) {
        numbers[i] = output[i];
    }
}

// The main function to implement Radix Sort
void radixSort(vector<int>& numbers) {
    int maxNumber = getMax(numbers);

    // Apply counting sort for every digit (1s, 10s, 100s, ...)
    for (int exp = 1; maxNumber / exp > 0; exp *= 10) {
        countingSort(numbers, exp);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    radixSort(numbers);

    for (int i = 0; i < n; i++) {
        cout << numbers[i];
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}
