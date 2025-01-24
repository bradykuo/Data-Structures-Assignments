#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    string name;
    int score;
    Node* left;
    Node* right;
    Node* parent;
    Node(string n, int s) : name(n), score(s), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
private:
    Node* root;
    
    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void balanceTree() {
        // Store nodes in sorted order
        vector<Node*> nodes;
        storeInOrder(root, nodes);
        
        // Clear original tree
        root = nullptr;
        
        // Rebuild as complete BST
        root = buildComplete(nodes, 0, nodes.size() - 1);
    }
    
    void storeInOrder(Node* node, vector<Node*>& nodes) {
        if (!node) return;
        storeInOrder(node->left, nodes);
        nodes.push_back(new Node(node->name, node->score));
        storeInOrder(node->right, nodes);
    }
    
    Node* buildComplete(vector<Node*>& nodes, int start, int end) {
        if (start > end) return nullptr;
        
        int mid = (start + end) / 2;
        Node* node = nodes[mid];
        
        node->left = buildComplete(nodes, start, mid - 1);
        if (node->left) node->left->parent = node;
        
        node->right = buildComplete(nodes, mid + 1, end);
        if (node->right) node->right->parent = node;
        
        return node;
    }
    
    void printTree(Node* node, int space = 0) {
        if (!node) return;
        space += 6;
        printTree(node->right, space);
        cout << endl;
        for (int i = 6; i < space; i++) 
            cout << " ";
        cout << "(" << node->name << ")" << node->score;
        printTree(node->left, space);
    }

    string findPath(Node* node, int target) {
        if (!node) return "";
        string result = "(" + node->name + ")" + to_string(node->score);
        
        if (node->score == target) 
            return result;
        
        if (target < node->score) {
            string path = findPath(node->left, target);
            return path.empty() ? "" : result + "->" + path;
        } else {
            string path = findPath(node->right, target);
            return path.empty() ? "" : result + "->" + path;
        }
    }

    // Other helper functions remain the same...

public:
    BST() : root(nullptr) {}
    ~BST() { deleteTree(root); }
    
    void insert(string name, int score) {
        // Same insert function...
        if (!root) {
            root = new Node(name, score);
            return;
        }
        
        Node* current = root;
        Node* parent = nullptr;
        
        while (current != nullptr) {
            parent = current;
            if (score < current->score) {
                current = current->left;
            } else if (score > current->score) {
                current = current->right;
            } else {
                return;
            }
        }
        
        Node* newNode = new Node(name, score);
        newNode->parent = parent;
        
        if (score < parent->score) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    void makeComplete() {
        balanceTree();
    }

    void printLevelOrder() {
        if (!root) return;
        
        queue<Node*> q;
        q.push(root);
        cout << "Level order traversal:" << endl;
        
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node* current = q.front();
                q.pop();
                cout << "(" << current->name << ")" << current->score << " ";
                
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            cout << endl;
        }
    }

    void printStructure() {
        cout << "Current tree structure:";
        printTree(root);
        cout << endl;
    }

    // Other public functions remain the same...
};

int main() {
    BST tree;

    tree.insert("Amy", 32);
    tree.insert("Daniel", 16);
    tree.insert("Albert", 8);
    tree.insert("Hens", 5);
    tree.insert("Ben", 4);
    tree.insert("Chen", 2);
    tree.insert("Frank", 1);

    cout << "Before making complete BST:" << endl;
    tree.printStructure();
    tree.printLevelOrder();

    cout << "\nAfter making complete BST:" << endl;
    tree.makeComplete();
    tree.printStructure();
    tree.printLevelOrder();

    return 0;
}