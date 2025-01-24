#include <iostream>
#include <iomanip>
#include <string>
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

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int score) {
        if (!node) return nullptr;
        
        if (score < node->score)
            node->left = deleteNode(node->left, score);
        else if (score > node->score)
            node->right = deleteNode(node->right, score);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Node* temp = node->right;
                if (temp) temp->parent = node->parent;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                if (temp) temp->parent = node->parent;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->score = temp->score;
            node->name = temp->name;
            node->right = deleteNode(node->right, temp->score);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { deleteTree(root); }
    
    void insert(string name, int score) {
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
                return;  // Duplicate score
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

    void printStructure() {
        cout << "Current tree structure:";
        printTree(root);
        cout << endl;
    }

    string search(int score) {
        return findPath(root, score);
    }
    
    void remove(int score) {
        root = deleteNode(root, score);
    }
};

int main() {
    BST tree;

    tree.insert("Amy", 32);      // Root
    tree.insert("Daniel", 16);   // Right subtree
    tree.insert("Albert", 8);
    tree.insert("Hens", 5);
    tree.insert("Ben", 4);
    tree.insert("Chen", 2);
    tree.insert("Frank", 1);

    while (true) {
        cout << "\n1. Print tree\n2. Search score\n3. Delete node\n4. Exit\nChoice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                tree.printStructure();
                break;
            case 2: {
                int score;
                cout << "Enter score to search: ";
                cin >> score;
                cout << "Path: " << tree.search(score) << endl;
                break;
            }
            case 3: {
                int score;
                cout << "Enter score to delete: ";
                cin >> score;
                tree.remove(score);
                cout << "After deletion:";
                tree.printStructure();
                break;
            }
            case 4:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}