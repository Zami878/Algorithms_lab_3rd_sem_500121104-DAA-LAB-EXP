#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace std;
using namespace chrono;  // hgih precision flock for this question performance test

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};


Node* recursiveInsert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = recursiveInsert(root->left, val);
    } else {
        root->right = recursiveInsert(root->right, val);
    }
    return root;
}


Node* iterativeInsert(Node* root, int val) {
    Node* newNode = new Node(val);
    if (root == nullptr) {
        return newNode;
    }
    Node* current = root;
    while (true) {
        if (val < current->data) {
            if (current->left == nullptr) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = newNode;
                break;
            }
            current = current->right;
        }
    }
    return root;
}


vector<int> generateRandomNumbers(int n, int max_val) {
    vector<int> numbers;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, max_val);

    for (int i = 0; i < n; ++i) {
        numbers.push_back(dis(gen));
    }
    return numbers;
}

int main() {
    vector<int> test_sizes = {100, 1000, 10000, 50000, 100000, 200000, 500000}; // Varying test sizes
    int max_val = 1000000; 

    for (int n : test_sizes) {
   
        vector<int> numbers = generateRandomNumbers(n, max_val);

       
        auto start = high_resolution_clock::now();
        Node* rootRecursive = nullptr;
        for (int i = 0; i < n; ++i) {
            rootRecursive = recursiveInsert(rootRecursive, numbers[i]);
        }
        auto end = high_resolution_clock::now();
        auto durationRecursive = duration_cast<microseconds>(end - start);
        cout << "Test Size: " << n << " | Recursive Insertion Time: " << durationRecursive.count() << " microseconds" << endl;

        
        start = high_resolution_clock::now();
        Node* rootIterative = nullptr;
        for (int i = 0; i < n; ++i) {
            rootIterative = iterativeInsert(rootIterative, numbers[i]);
        }
        end = high_resolution_clock::now();
        auto durationIterative = duration_cast<microseconds>(end - start);
        cout << "Test Size: " << n << " | Iterative Insertion Time: " << durationIterative.count() << " microseconds" << endl;
    }

    return 0;
}
