#include <iostream>
#include <vector>

using namespace std;

// Merge function to count inversions
int merge(vector<int>& leftVetor, vector<int>& rightVetor, vector<int>& mergedVector, int& numInversions) {
    int i = 0, j = 0, k = 0;
    int p = leftVetor.size(), q = rightVetor.size();

    // Merging the two sorted subarrays
    while (i < p && j < q) {
        if (leftVetor[i] <= rightVetor[j]) {
            mergedVector[k++] = leftVetor[i++];
        } else {
            mergedVector[k++] = rightVetor[j++];
            numInversions += p - i; // Count inversions
        }
    }

    // Copy remaining elements
    while (i < p) {
        mergedVector[k++] = leftVetor[i++];
    }
    while (j < q) {
        mergedVector[k++] = rightVetor[j++];
    }

    return numInversions;
}

// Merge Sort function to count inversions
int numberInversions(vector<int>& numbers) {
    int size = numbers.size();
    if (size <= 1) return 0;  // Base case

    int m = size / 2;
    vector<int> left(numbers.begin(), numbers.begin() + m);
    vector<int> right(numbers.begin() + m, numbers.end());

    int inversions1 = numberInversions(left);
    int inversions2 = numberInversions(right);

    int totalInversions = inversions1 + inversions2;
    return merge(left, right, numbers, totalInversions);
}

int main() {
    vector<int> A = {10, 9, 8, 7, 6};

    int numInversions = numberInversions(A);
    cout << "Number of inversions: " << numInversions << endl;

    return 0;
}
