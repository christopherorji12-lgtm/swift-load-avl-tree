#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
using namespace std;
using namespace std::chrono;

// =======================
// 1. VALID INPUT CHECK
// =======================
float getValidWeight() {
    float weight;
    cout << "Enter cargo weight: ";
    cin >> weight;

    if (weight <= 0) {
        throw invalid_argument("Error: Weight must be positive!");
    }

    return weight;
}

// =======================
// 2. SORTING ALGORITHMS
// =======================

// Bubble Sort with swap count
void bubbleSort(vector<int>& arr, int& swaps) {
    int n = arr.size();
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) { // descending
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

// QuickSort with swap count
int partition(vector<int>& arr, int low, int high, int& swaps) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] > pivot) {
            i++;
            swap(arr[i], arr[j]);
            swaps++;
        }
    }
    swap(arr[i + 1], arr[high]);
    swaps++;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, int& swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, swaps);
        quickSort(arr, low, pi - 1, swaps);
        quickSort(arr, pi + 1, high, swaps);
    }
}

// =======================
// 3. FIFO QUEUE
// =======================
void testQueue() {
    queue<string> trucks;

    trucks.push("Truck A");
    trucks.push("Truck B");
    trucks.push("Truck C");

    cout << "\nFIFO Queue (Truck Loading Order):\n";
    while (!trucks.empty()) {
        cout << trucks.front() << " is loading...\n";
        trucks.pop();
    }
}

// =======================
// 4. LIFO STACK
// =======================
void testStack() {
    stack<string> packages;

    packages.push("Package 1");
    packages.push("Package 2");
    packages.push("Package 3");

    cout << "\nLIFO Stack (Package Unloading Order):\n";
    while (!packages.empty()) {
        cout << packages.top() << " is unloaded...\n";
        packages.pop();
    }
}

// =======================
// 5. AVL TREE
// =======================
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) {
        key = k;
        left = right = NULL;
        height = 1;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Rotations
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// =======================
// MAIN FUNCTION
// =======================
int main() {

    // 1. INPUT VALIDATION
    cout << "=== INPUT VALIDATION ===\n";
    try {
        float weight = getValidWeight();
        cout << "Valid weight entered: " << weight << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // 2. SORTING COMPARISON
    cout << "\n=== SORTING COMPARISON ===\n";

    vector<int> data = {120, 450, 200, 150, 300, 90, 600, 250, 175, 400, 50, 220};

    vector<int> arr1 = data;
    vector<int> arr2 = data;

    int swaps1 = 0, swaps2 = 0;

    // Bubble Sort timing
    auto start1 = high_resolution_clock::now();
    bubbleSort(arr1, swaps1);
    auto end1 = high_resolution_clock::now();

    // Quick Sort timing
    auto start2 = high_resolution_clock::now();
    quickSort(arr2, 0, arr2.size() - 1, swaps2);
    auto end2 = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>(end1 - start1);
    auto duration2 = duration_cast<microseconds>(end2 - start2);

    cout << "\nBubble Sort:\n";
    cout << "Time: " << duration1.count() << " microseconds\n";
    cout << "Swaps: " << swaps1 << endl;
    cout << "Memory (approx): " << sizeof(arr1) << " bytes\n";

    cout << "\nQuick Sort:\n";
    cout << "Time: " << duration2.count() << " microseconds\n";
    cout << "Swaps: " << swaps2 << endl;
    cout << "Memory (approx): " << sizeof(arr2) << " bytes\n";

    // 3. FIFO
    testQueue();

    // 4. LIFO
    testStack();

    // 5. AVL TREE
    cout << "\n=== AVL TREE ===\n";
    Node* root = NULL;
    vector<int> values = {30, 20, 40, 10, 25};

    for (int v : values)
        root = insert(root, v);

    cout << "Inorder traversal (sorted): ";
    inorder(root);
    cout << endl;

    return 0;
}
