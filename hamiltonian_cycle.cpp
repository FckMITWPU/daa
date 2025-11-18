#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Number of vertices in the graph
#define V 5

void printSolution(const vector<int>& path) {
    cout << "Solution Exists: Following is one Hamiltonian Cycle" << endl;
    for (int i = 0; i < V; i++) {
        cout << path[i] << " ";
    }
    // Print the first vertex again to show the complete cycle
    cout << path[0] << " " << endl;
}

/* A utility function to check if the vertex v can be added at index 'pos'
   in the Hamiltonian Cycle constructed so far (stored in 'path') */
bool isSafe(int v, bool graph[V][V], vector<int>& path, int pos) {
    // Check if this vertex is an adjacent vertex of the previously added vertex.
    if (!graph[path[pos - 1]][v]) {
        return false;
    }

    // Check if the vertex has already been included.
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

/* A recursive utility function to solve hamiltonian cycle problem */
bool hamCycleUtil(bool graph[V][V], vector<int>& path, int pos) {
    // Base case: If all vertices are included in the path
    if (pos == V) {
        // And if there is an edge from the last included vertex to the first vertex
        if (graph[path[pos - 1]][path[0]]) {
            return true;
        } else {
            return false;
        }
    }

    // Try different vertices as a next candidate in Hamiltonian Cycle.
    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            // Recur to construct rest of the path
            if (hamCycleUtil(graph, path, pos + 1)) {
                return true;
            }

            // If adding vertex v doesn't lead to a solution, then remove it
            path[pos] = -1; // Backtrack
        }
    }

    return false;
}

/* This function solves the Hamiltonian Cycle problem using Backtracking.
   It mainly uses hamCycleUtil() to solve the problem. It returns false
   if there is no Hamiltonian Cycle possible, otherwise, it returns true
   and prints the path. */
bool hamCycle(bool graph[V][V]) {
    vector<int> path(V, -1);

    /* Let's put vertex 0 as the first vertex in the path. If there is
       a Hamiltonian Cycle, then the path can be started from any point
       of the cycle as it is a cycle. */
    path[0] = 0;

    if (!hamCycleUtil(graph, path, 1)) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    printSolution(path);
    return true;
}

// Driver program to test above functions
int main() {
    /* Let us create the following graph
       (0)--(1)--(2)
        |   / \   |
        |  /   \  |
        | /     \ |
       (3)-------(4)    */
    bool graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0},
    };

    hamCycle(graph);

    return 0;
}
