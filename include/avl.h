#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

class myTree {
private:
    struct Node {
        string data;
        Node* left;
        Node* right;
        int height;
        int subtreeSize;

        Node(string value);
    };

    Node* root;
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* y);
    Node* insert(Node* node, string value);

public:
    myTree();
    void insert(string value);
    int range (string val1, string val2);
};
#endif
