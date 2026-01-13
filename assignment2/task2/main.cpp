#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>
#include <random>
#include <iomanip>

using namespace std;

// Tree node
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree
class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int key) {
        if (!node) return node;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }
};

// Generate insertion order for a perfectly balanced BST
void createPerfectOrder(
    const vector<int>& sortedInput,
    vector<int>& output,
    int start,
    int end
) {
    if (start > end) return;

    int mid = start + (end - start) / 2;
    output.push_back(sortedInput[mid]);

    createPerfectOrder(sortedInput, output, start, mid - 1);
    createPerfectOrder(sortedInput, output, mid + 1, end);
}

// Generate shuffled array
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
        arr[i] = i;

    mt19937 gen(random_device{}());
    shuffle(arr.begin(), arr.end(), gen);
    return arr;
}

int main() {
    int N = 32767;

    cout << "Benchmarking BST with N=" << N << " elements..." << endl;
    cout << left << setw(25) << "Operation" << "Time (seconds)" << endl;
    cout << "---------------------------------------------" << endl;

    vector<int> randomKeys = generateRandomArray(N);

    vector<int> sortedKeys = randomKeys;
    sort(sortedKeys.begin(), sortedKeys.end());

    vector<int> perfectKeys;
    createPerfectOrder(sortedKeys, perfectKeys, 0, N - 1);

    BST treeRandom;
    {
        auto start = chrono::high_resolution_clock::now();
        for (int k : randomKeys)
            treeRandom.insert(k);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(25) << "BST Insert (Random)"
             << chrono::duration<double>(end - start).count() << endl;
    }

    BST treePerfect;
    {
        auto start = chrono::high_resolution_clock::now();
        for (int k : perfectKeys)
            treePerfect.insert(k);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(25) << "BST Insert (Perfect)"
             << chrono::duration<double>(end - start).count() << endl;
    }

    set<int> libSet;
    {
        auto start = chrono::high_resolution_clock::now();
        for (int k : randomKeys)
            libSet.insert(k);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(25) << "std::set Insert"
             << chrono::duration<double>(end - start).count() << endl;
    }

    cout << "---------------------------------------------" << endl;

    {
        vector<int> keysToRemove = randomKeys;
        auto start = chrono::high_resolution_clock::now();
        for (int k : keysToRemove)
            treeRandom.remove(k);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(25) << "BST Remove (Random)"
             << chrono::duration<double>(end - start).count() << endl;
    }

    {
        vector<int> keysToRemove = randomKeys;
        auto start = chrono::high_resolution_clock::now();
        for (int k : keysToRemove)
            libSet.erase(k);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(25) << "std::set Remove"
             << chrono::duration<double>(end - start).count() << endl;
    }

    return 0;
}