#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

int max_value = 0;
vector<int> best_solution;

// Function to solve 0/1 Knapsack problem using backtracking
void knapsack_backtracking(int index, int current_weight, int current_value, int capacity, const vector<Item>& items, vector<int>& current_solution) {
    // Base case: If all items are considered
    if (index == items.size()) {
        if (current_value > max_value) {
            max_value = current_value;
            best_solution = current_solution;
        }
        return;
    }

    // Pruning: if the current weight exceeds capacity, stop
    if (current_weight > capacity) {
        return;
    }

    // Explore the branch where the current item is included
    if (current_weight + items[index].weight <= capacity) {
        current_solution.push_back(index);
        knapsack_backtracking(index + 1, current_weight + items[index].weight, current_value + items[index].value, capacity, items, current_solution);
        current_solution.pop_back(); // Backtrack
    }

    // Explore the branch where the current item is not included
    knapsack_backtracking(index + 1, current_weight, current_value, capacity, items, current_solution);
}

int main() {
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    int capacity = 50;
    vector<int> current_solution;

    knapsack_backtracking(0, 0, 0, capacity, items, current_solution);

    cout << "Maximum value: " << max_value << endl;
    cout << "Selected items (indices): ";
    for (int i : best_solution) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
