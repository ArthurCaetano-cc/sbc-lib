#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

// Function to compare items based on value/weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2; 
}

// Function to solve the Fractional Knapsack problem
double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += item.value * ((double)capacity / item.weight);
            break; 
        }
    }
    
    return totalValue;
}

int main() {
    int n, capacity;
    cin >> n;
    
    vector<Item> items(n);
    
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;
    }

    cin >> capacity;

    double maxValue = fractionalKnapsack(capacity, items);
    cout << maxValue << endl;

    return 0;
}
