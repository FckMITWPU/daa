#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>

using namespace std;

// A Huffman tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of two heap nodes (needed in priority_queue)
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

// Prints huffman codes from the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str) {
    if (!root)
        return;

    if (root->data != '$') // '$' is a special value for internal nodes
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and
// prints codes by traversing the built Huffman Tree
void HuffmanCodes(map<char, int>& freq) {
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (auto const& [key, val] : freq) {
        minHeap.push(new MinHeapNode(key, val));
    }

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the
        // sum of the two nodes' frequencies. Make the two extracted
        // node as left and right children of this new node.
        // '$' is a special value for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    cout << "Huffman Codes:\n";
    printCodes(minHeap.top(), "");
}

int main() {
    string str = "this is an example for huffman encoding";
    map<char, int> freq;

    for (char c : str) {
        freq[c]++;
    }

    HuffmanCodes(freq);

    return 0;
}
