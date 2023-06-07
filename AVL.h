#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "countries.h"
using namespace std;

class AVL
{
private:
    struct AVLNODE
    {
        Node data;
        AVLNODE *left;
        AVLNODE *right;
        int height;
    };
    AVLNODE *root;

    // Private member functions
    int getHeight(AVLNODE *node);
    int getBalanceFactor(AVLNODE *node);
    AVLNODE *rotateLeft(AVLNODE *node);
    AVLNODE *rotateRight(AVLNODE *node);
    AVLNODE *insertNode(AVLNODE *node, const Node &data);
    AVLNODE *deleteNode(AVLNODE *node, const Node &data);
    AVLNODE *findMinNode(AVLNODE *node);
    void inOrderTraversal(AVLNODE *node);

public:
    AVL()
    {
        root = nullptr;
    }

    // Public member functions
    void insert(const Node &data);
    void remove(const Node &data);
    void printInOrder();
};

// Private member functions

int AVL::getHeight(AVLNODE *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVL::getBalanceFactor(AVLNODE *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVL::AVLNODE *AVL::rotateLeft(AVLNODE *node)
{
    AVLNODE *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AVL::AVLNODE *AVL::rotateRight(AVLNODE *node)
{
    AVLNODE *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AVL::AVLNODE *AVL::insertNode(AVLNODE *node, const Node &data)
{
    if (node == nullptr)
    {
        AVLNODE *newNode = new AVLNODE;
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (data.code < node->data.code)
    {
        node->left = insertNode(node->left, data);
    }
    else if (data.code > node->data.code)
    {
        node->right = insertNode(node->right, data);
    }
    else
    {
        // Duplicate values are not allowed in AVL tree
        return node;
    }

    // Update height of the current node
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Perform rotations if necessary
    int balance = getBalanceFactor(node);
    if (balance > 1 && data.code < node->left->data.code)
    {
        // Left-Left case
        return rotateRight(node);
    }
    if (balance < -1 && data.code > node->right->data.code)
    {
        // Right-Right case
        return rotateLeft(node);
    }
    if (balance > 1 && data.code > node->left->data.code)
    {
        // Left-Right case
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && data.code < node->right->data.code)
    {
        // Right-Left case
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVL::AVLNODE *AVL::deleteNode(AVLNODE *node, const Node &data)
{
    if (node == nullptr)
        return node;

    if (data.code < node->data.code)
    {
        node->left = deleteNode(node->left, data);
    }
    else if (data.code > node->data.code)
    {
        node->right = deleteNode(node->right, data);
    }
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        {
            AVLNODE *temp = node->left ? node->left : node->right;

            if (temp == nullptr)
            {
                temp = node;
                node = nullptr;
            }
            else
            {
                *node = *temp;
            }

            delete temp;
        }
        else
        {
            AVLNODE *temp = findMinNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }

    if (node == nullptr)
        return node;

    // Update height of the current node
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Perform rotations if necessary
    int balance = getBalanceFactor(node);
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
    {
        // Left-Left case
        return rotateRight(node);
    }
    if (balance > 1 && getBalanceFactor(node->left) < 0)
    {
        // Left-Right case
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
    {
        // Right-Right case
        return rotateLeft(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) > 0)
    {
        // Right-Left case
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVL::AVLNODE *AVL::findMinNode(AVLNODE *node)
{
    if (node == nullptr || node->left == nullptr)
        return node;
    return findMinNode(node->left);
}

void AVL::inOrderTraversal(AVLNODE *node)
{
    if (node == nullptr)
        return;

    inOrderTraversal(node->left);
    cout << node->data.code << " ";
    inOrderTraversal(node->right);
}

// Public member functions

void AVL::insert(const Node &data)
{
    root = insertNode(root, data);
}

void AVL::remove(const Node &data)
{
    root = deleteNode(root, data);
}

void AVL::printInOrder()
{
    inOrderTraversal(root);
    cout << endl;
}

void applyAVLOnCountriesData(CSVParser parser)
{
    // Create a menu for the user to interact with the AVL tree
    AVL avl;
    vector<vector<string>> data = parser.get_data();
    for (int i = 0; i < parser.get_rows(); i++)
    {
        Node node;
        node.code = data[i][0];
        node.latitude = to_double(data[i][1]);
        node.longitude = to_double(data[i][2]);
        node.name = data[i][3];
        avl.insert(node);
    }
    int choice;
    while (true)
    {
        cout << "1. Delete a country" << endl;
        cout << "2. Print the countries in the AVL tree" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            Node node;
            cout << "Enter the country code: ";
            cin >> node.code;
            avl.remove(node);
        }
        else if (choice ==2)
        {
            avl.printInOrder();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}

#endif // AVL_H
