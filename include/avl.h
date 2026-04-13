#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

class myTree {
private:

    /* 
    Each node of the tree holds a unique set of data.
    Each node also contains the address of the left child
    and right child as well as the height of the node 
    relative to the furthest leaf node and the subtree size
    */
    struct Node {
        string data;
        Node* left;
        Node* right;
        int height;
        int subtreeSize;

        Node(string value);
    };

    Node* root;

    // Return height of the node
    int getHeight(Node* node);

    // Return the balance of the left and right nodes
    int getBalance(Node* node);

    // Update the height of the node
    int updateHeight(Node* node);

    // Return the number of children and grandchildren of the node
    int getSubtreeSize(Node* node);

    // Update the subtree size of the node
    int updateSubtreeSize(Node* node);

    // Check whether or not the node is unbalanced left or right
    int checkBalance(Node* node);

    // Restore balance to a right-heavy subtree 
    Node* rotateLeft(Node* x);

    // Restore balance to a left-heavy subtree
    Node* rotateRight(Node* y);

    // Recursive helper function for insert
    Node* insertRecursive(string value, Node* currentNode);

    // Count all values less than a given value starting from a given node
    int countLess(Node* node, string value);

    // Count all values less than or equal to a given value starting from a given node
    int countLessEqual(Node* node, string value);

public:

    // Constructor
    myTree();

    // Wrapper function to insert a unique value into the tree
    void insert(string value);

    // Our core feature to return the number of values between two given values
    int range (string val1, string val2);
};
#endif
