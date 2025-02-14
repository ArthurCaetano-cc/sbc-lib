#include <iostream>
#include <vector>

using namespace std;

// Function to merge two sorted vectors
vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    int i = 0, j = 0;

    // Merge elements in sorted order
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) result.push_back(left[i++]);
    while (j < right.size()) result.push_back(right[j++]);

    return result;
}

// MergeSort function
vector<int> mergesort(vector<int> numbers) {
    int size = numbers.size();
    
    if (size <= 1) return numbers;  // Base case

    int m = size / 2;

    vector<int> firstMiddle(numbers.begin(), numbers.begin() + m);
    vector<int> secondMiddle(numbers.begin() + m, numbers.end());

    vector<int> sortedFirst = mergesort(firstMiddle);
    vector<int> sortedSecond = mergesort(secondMiddle);

    return merge(sortedFirst, sortedSecond);
}

int main() {
    vector<int> numbers = {5, 3, 8, 4, 2, 7, 1, 6};

    vector<int> sortedNumbers = mergesort(numbers);

    for (int num : sortedNumbers) {
        cout << num << " ";
    }
    
    return 0;
}
