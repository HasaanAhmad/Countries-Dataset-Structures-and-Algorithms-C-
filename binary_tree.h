
// TODO:
// 1. This tree implementation is tested: NO (PENDING TEST)
// 2. This tree is applied on countries data: NO (PENDING IMPLEMENTATION)

//  START -

// Binary Tree Implementation

// Revision History:
// 1. June 3, 2023 - Initial commit. - Mujtaba SP22-BSE-036

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "countries.h"

class BinaryTree {
    private:
        typedef struct TreeNode {
            Node *data; // Node is the global Node defined in countries.h
            TreeNode* right;
            TreeNode* left;
        } TreeNode;
        TreeNode* root = NULL;
        int size = 0;
    public:
        BinaryTree();
        ~BinaryTree();
        void insert(Node *data);
        void remove(Node data);
        void print();
        int getSize();
        TreeNode* getRoot();
        Node* search(string name);
        void clear();
        void inorderTraversal(TreeNode* root);
        void levelOrderTraversal(TreeNode* root);
};

BinaryTree::BinaryTree() {
    root = NULL;
    size = 0;
}

BinaryTree::~BinaryTree() {
    clear();
}

void BinaryTree::insert(Node* data) {
    TreeNode* newNode = new TreeNode;
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    if (root == NULL) {
        root = newNode;
    } else {
        TreeNode* temp = root;
        while (temp != NULL) {
            if (data->name.compare(temp->data->name) < 0) {
                if (temp->left == NULL) {
                    temp->left = newNode;
                    break;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->right == NULL) {
                    temp->right = newNode;
                    break;
                } else {
                    temp = temp->right;
                }
            }
        }
    }
    size++;
}

void BinaryTree::remove(Node data) {
    TreeNode* temp = root;
    TreeNode* parent = NULL;
    while (temp != NULL) {
        if (data.name.compare(temp->data->name) == 0) {
            break;
        } else if (data.name.compare(temp->data->name) < 0) {
            parent = temp;
            temp = temp->left;
        } else {
            parent = temp;
            temp = temp->right;
        }
    }
    if (temp == NULL) {
        return;
    }
    if (temp->left == NULL && temp->right == NULL) {
        if (parent == NULL) {
            root = NULL;
        } else {
            if (parent->left == temp) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
    } else if (temp->left == NULL) {
        if (parent == NULL) {
            root = temp->right;
        } else {
            if (parent->left == temp) {
                parent->left = temp->right;
            } else {
                parent->right = temp->right;
            }
        }
    } else if (temp->right == NULL) {
        if (parent == NULL) {
            root = temp->left;
        } else {
            if (parent->left == temp) {
                parent->left = temp->left;
            } else {
                parent->right = temp->left;
            }
        }
    } else {
        TreeNode* min = temp->right;
        TreeNode* minParent = temp;
        while (min->left != NULL) {
            minParent = min;
            min = min->left;
        }
        if (minParent == temp) {
            min->left = temp->left;
            if (parent == NULL) {
                root = min;
            } else {
                if (parent->left == temp) {
                    parent->left = min;
                } else {
                    parent->right = min;
                }
            }
        } else {
            minParent->left = min->right;
            min->left = temp->left;
            min->right = temp->right;
            if (parent == NULL) {
                root = min;
            } else {
                if (parent->left == temp) {
                    parent->left = min;
                } else {
                    parent->right = min;
                }
            }
        }
    }
    size--;
}

void BinaryTree::print() {
    if (root == NULL) {
        cout << "Tree is empty" << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();
        cout << temp->data->name << " ";
        if (temp->left != NULL) {
            q.push(temp->left);
        }
        if (temp->right != NULL) {
            q.push(temp->right);
        }
    }
    cout << endl;
}

int BinaryTree::getSize() {
    return size;
}

BinaryTree::TreeNode* BinaryTree::getRoot() {
    return root;
}

Node* BinaryTree::search(string name) {
    TreeNode* temp = root;
    while (temp != NULL) {
        if (name.compare(temp->data->name) == 0) {
            return temp->data;
        } else if (name.compare(temp->data->name) < 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return NULL;
}

void BinaryTree::clear() {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();
        if (temp->left != NULL) {
            q.push(temp->left);
        }
        if (temp->right != NULL) {
            q.push(temp->right);
        }
        delete temp;
    }
    root = NULL;
    size = 0;
}
void BinaryTree::inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data->name << " ";
    inorderTraversal(root->right);
}
void BinaryTree::levelOrderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();
        cout << temp->data->name << " ";
        if (temp->left != NULL) {
            q.push(temp->left);
        }
        if (temp->right != NULL) {
            q.push(temp->right);
        }
    }
}

// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
// # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

void applyBinaryTreeOnCountriesData(CSVParser& parser){
    cout << "Applying Binary Tree on Countries Data" << endl;
    BinaryTree tree;
    for (int i = 0; i < parser.get_rows(); i++) {
        Node* node = new Node;
        vector<vector<string>> data = parser.get_data();
        node->name = data[i][0];
        node->latitude = to_double(data[i][1]);
        node->longitude = to_double(data[i][2]);
        node->code = data[i][3];

        tree.insert(node);

       
    }
    // create a menu for the user to choose from
    int choice;
    do {
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Print" << endl;
        cout << "5. Size" << endl;
        cout << "6. Clear" << endl;
        cout << "7. Inorder Traversal" << endl;
        cout << "8. Level Order Traversal" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                Node* node = new Node;
                cout << "Enter name: ";
                cin >> node->name;
                cout << "Enter latitude: ";
                cin >> node->latitude;
                cout << "Enter longitude: ";
                cin >> node->longitude;
                cout << "Enter code: ";
                cin >> node->code;
                tree.insert(node);
                break;
            }
            case 2: {
                string name;
                cout << "Enter name: ";
                cin >> name;
                if(tree.search(name) == NULL){
                    cout << "Not found" << endl;
                    break;
                }else{
                    cout << "Found" << endl;
                    Node *node = tree.search(name);
                     tree.remove(*node);
                     break;

                }
                
               
            }
            case 3: {
                string name;
                cout << "Enter name: ";
                cin >> name;
                Node* node = tree.search(name);
                if (node == NULL) {
                    cout << "Not found" << endl;
                } else {
                    cout << node->name << " " << node->latitude << " " << node->longitude << " " << node->code << endl;
                }
                break;
            }
            case 4: {
                tree.print();
                break;
            }
            case 5: {
                cout << tree.getSize() << endl;
                break;
            }
            case 6: {
                tree.clear();
                break;
            }
            case 7: {
                tree.inorderTraversal(tree.getRoot());
                cout << endl;
                break;
            }
            case 8: {
                tree.levelOrderTraversal(tree.getRoot());
                cout << endl;
                break;
            }
            case 9: {
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
            }
        }
    } while (choice != 9);

}

#endif

// - END
