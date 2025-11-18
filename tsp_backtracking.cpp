#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int N = 4; // Number of cities

int final_path[N + 1];
bool visited[N];
int final_res = INT_MAX;

void copyToFinal(int curr_path[]) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

void TSP_backtracking(int graph[N][N], int curr_bound, int curr_weight, int level, int curr_path[]) {
    if (level == N) {
        if (graph[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + graph[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i] && graph[curr_path[level - 1]][i] != 0) {
            int temp = curr_bound;
            curr_weight += graph[curr_path[level - 1]][i];

            // Different computation of curr_bound for level 2 from the other levels
            if (level == 1)
                curr_bound -= ((graph[curr_path[level - 1]][i] + graph[i][0]) / 2);
            else
                curr_bound -= ((graph[curr_path[level - 2]][curr_path[level - 1]] + graph[curr_path[level - 1]][i]) / 2);


            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSP_backtracking(graph, curr_bound, curr_weight, level + 1, curr_path);
            }

            curr_weight -= graph[curr_path[level - 1]][i];
            curr_bound = temp;

            fill(visited, visited + N, false);
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = true;
        }
    }
}

void TSP(int graph[N][N]) {
    int curr_path[N + 1];
    int curr_bound = 0;
    fill(curr_path, curr_path + N + 1, -1);
    fill(visited, visited + N, false);

    for (int i = 0; i < N; i++)
        curr_bound += (graph[i][0] + graph[i][1]);

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;

    TSP_backtracking(graph, curr_bound, 0, 1, curr_path);
}

int main() {
    int graph[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP(graph);

    cout << "Minimum cost: " << final_res << endl;
    cout << "Path: ";
    for (int i = 0; i <= N; i++) {
        cout << final_path[i] << " ";
    }
    cout << endl;

    return 0;
}
