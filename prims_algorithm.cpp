#include <iostream>
#define max 20
using namespace std;

class graph
{
    int cost[max][max];
    int cities;

public:
    graph()
    {
        cout << "Enter the number of cities: ";
        cin >> cities;

        for (int i = 0; i < cities; i++)
        {
            for (int j = 0; j < cities; j++)
            {
                if (i == j)
                    cost[i][j] = 0;
                else
                    cost[i][j] = 999;
            }
        }
    }

    void create();
    void display();
    void primAlg(int startVertex);
};

void graph::create()
{
    char ch;
    for (int i = 0; i < cities; i++)
    {
        for (int j = i + 1; j < cities; j++)
        {
            cout << "Is there a connection between city " << i + 1 << " and city " << j + 1 << "? (y/n): ";
            cin >> ch;

            if (ch == 'y' || ch == 'Y')
            {
                int connectCost;
                cout << "Enter the distance between the two cities: ";
                cin >> connectCost;
                cost[i][j] = connectCost;
                cost[j][i] = connectCost;
            }
        }
    }
}

void graph::display()
{
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < cities; i++)
    {
        for (int j = 0; j < cities; j++)
        {
            if (cost[i][j] == 999)
                cout << "∞ ";
            else
                cout << cost[i][j] << " ";
        }
        cout << endl;
    }
}

void graph::primAlg(int startVertex)
{
    int nearest[max];
    int minCost = 0;

    for (int i = 0; i < cities; i++)
    {
        if (i != startVertex)
            nearest[i] = startVertex;
        else
            nearest[i] = -1;
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";

    for (int i = 0; i < cities - 1; i++)
    {
        int min = 999, j = -1;

        for (int k = 0; k < cities; k++)
        {
            if (nearest[k] != -1 && cost[k][nearest[k]] < min)
            {
                min = cost[k][nearest[k]];
                j = k;
            }
        }

        cout << "City " << nearest[j] + 1 << " -> City " << j + 1 << " (Cost: " << min << ")\n";
        minCost += min;
        nearest[j] = -1;

        for (int k = 0; k < cities; k++)
        {
            if (nearest[k] != -1 && cost[k][j] < cost[k][nearest[k]])
                nearest[k] = j;
        }
    }

    cout << "\nTotal cost of the Minimum Spanning Tree: " << minCost << endl;
}

int main()
{
    graph g;
    g.create();
    g.display();

    int startVertex;
    cout << "\nEnter the starting city (1-" << max << "): ";
    cin >> startVertex;

    if (startVertex < 1 || startVertex > max)
    {
        cout << "Invalid starting city!" << endl;
        return 1;
    }

    g.primAlg(startVertex - 1);
    return 0;
}
