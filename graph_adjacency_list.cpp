#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


class Node {
public:
    int id;
    vector<Node*> friends;

    Node(int id) : id(id) {}
};

class Graph {
public:
    unordered_map<int, Node*> nodes;

    void addNode(int id) {
        if (nodes.find(id) == nodes.end()) {
            nodes[id] = new Node(id);
        }
    }

    void addFriendship(int id1, int id2) {
        addNode(id1);
        addNode(id2);
        nodes[id1]->friends.push_back(nodes[id2]);
        nodes[id2]->friends.push_back(nodes[id1]);
    }

    void displayGraph() {
        for (const auto& pair : nodes) {
            cout << "Friend ID: " << pair.first << " -> Friends: ";
            for (Node* friendNode : pair.second->friends) {
                cout << friendNode->id << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;

    g.addFriendship(1, 2);
    g.addFriendship(1, 3);
    g.addFriendship(2, 4);
    g.addFriendship(3, 5);
    g.addFriendship(5, 6);

    cout << "Graph representation (Adjacency List):" << endl;
    g.displayGraph();

    return 0;
}
