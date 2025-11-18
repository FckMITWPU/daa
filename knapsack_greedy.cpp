#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Item structure
struct Item {
    int value;
    int weight;
    int id;
    double ratio; // value / weight
};

// Comparison function to sort items by ratio
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

// Greedy algorithm for 0/1 Knapsack problem
// Note: This greedy approach is optimal for the Fractional Knapsack problem.
// For the 0/1 Knapsack problem, it provides an approximation but not always the optimal solution.
void knapsackGreedy(int capacity, vector<Item>& items) {
    // Calculate ratio for each item
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }

    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), compareItems);

    int currentWeight = 0;
    double finalValue = 0.0;
    vector<int> selectedItems;

    // Loop through all items
    for (const auto& item : items) {
        // If adding the item doesn't exceed the capacity, add it
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            finalValue += item.value;
            selectedItems.push_back(item.id);
        }
    }

    cout << "Greedy approach for 0/1 Knapsack:" << endl;
    cout << "Maximum value: " << finalValue << endl;
    cout << "Selected item IDs: ";
    for (int id : selectedItems) {
        cout << id << " ";
    }
    cout << endl;
}

int main() {
    int capacity = 50;
    vector<Item> items = {
        {60, 10, 1},
        {100, 20, 2},
        {120, 30, 3}
    };

    knapsackGreedy(capacity, items);

    return 0;
}
