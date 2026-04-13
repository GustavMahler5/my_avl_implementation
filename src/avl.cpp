#include <iostream>
#include <string>
#include "avl.h"

using namespace std;

/*
A tree is imbalanced when the number of nodes on one side
outnumbers the number of nodes on the other side by 2 or greater
*/
#define LEFT_IMBALANCE 2
#define RIGHT_IMBALANCE -2

myTree::Node::Node(string value) {
	data = value;
	left = NULL;
	right = NULL;
	height = 1;
	subtreeSize = 1;
}


// Constructor
myTree::myTree() {
	root = NULL;
}


// Return the number of children and grandchildren + 1 (itself)
int myTree::getSubtreeSize(Node* node) {
	if (node == NULL) {
		return 0;
	}
	return node->subtreeSize;
}


// Return height of the node
int myTree::getHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}


// Update the height of the node
int myTree::updateHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}

	// Return the height of the greater of the left subtree and the right subtree
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	return node->height;
}


// Update the subtree size of the node
int myTree::updateSubtreeSize(Node* node) {
	if (node == NULL) {
		return 0;
	}

	// Return the sum of the left and right children's subtrees + 1 (itself)
	node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);
	return node->subtreeSize;
}


// Restore balance to a left-heavy subtree
myTree::Node* myTree::rotateRight(Node* nodeToRotate){

	// Create temporary nodes
	Node* newParent = nodeToRotate->left;
	Node* grandChild = newParent->right;

	// Update pointers
	newParent->right = nodeToRotate;
	nodeToRotate->left = grandChild;

	// Update heights of affected nodes
	updateHeight(nodeToRotate);
	updateHeight(newParent);

	// Update subtree sizes of affected nodes
	updateSubtreeSize(nodeToRotate);
	updateSubtreeSize(newParent);

	// Return the new root of the subtree
	return newParent;
}


// Restore balance to a right-heavy subtree
myTree::Node* myTree::rotateLeft(Node* nodeToRotate) {

	// Create temporary nodes
	Node* newParent = nodeToRotate->right;
	Node* grandChild = newParent->left;

	// Update pointers
	newParent->left = nodeToRotate;
	nodeToRotate->right = grandChild;

	// Update heights of affected nodes
	updateHeight(nodeToRotate);
	updateHeight(newParent);

	// Update subtree sizes of affected nodes
	updateSubtreeSize(nodeToRotate);
	updateSubtreeSize(newParent);

	// Return the new root of the subtree
	return newParent;
}	


/*
We return the difference of the heights of the left and right children.
If we return x such that x > 1, the subtree is left imbalanced.
If we return x such that x < -1, the subtree is right imbalanced.
*/
int myTree::checkBalance(Node* node) {
	if (node == NULL) { return 0; }
	return getHeight(node->left) - getHeight(node->right);
}


// Wrapper function to insert a unique value into the tree
void myTree::insert(string value) {
	root = insertRecursive(value, root);
}


// Recursive helper function for insert
myTree::Node* myTree::insertRecursive(string value, Node* currentNode) {

	// Insert into a leaf's null child
	if (currentNode == NULL) {
		return new Node(value);
	}

	// Recurse left
	if (currentNode->data > value) {
		currentNode->left = insertRecursive(value, currentNode->left);
	}
	// Recurse right
	else if (currentNode->data < value) {
		currentNode->right = insertRecursive(value, currentNode->right);
	}
	// In the case that the value is a duplicate, just return the node
	else {
		return currentNode;
	}

	// Update heights and subtree sizes for all traversed nodes
	updateHeight(currentNode);
	updateSubtreeSize(currentNode);
	int currentBalance = checkBalance(currentNode);

	// If our tree is left imbalanced, rotate right
	if (currentBalance >= LEFT_IMBALANCE) {
		if (value > currentNode->left->data) {
			currentNode->left = rotateLeft(currentNode->left);
			return rotateRight(currentNode);
		}
		else {
			return rotateRight(currentNode);
		}
	}

	// If our tree is right imbalanced, rotate left
	if (currentBalance <= RIGHT_IMBALANCE) {
		if (value < currentNode->right->data) {
			currentNode->right = rotateRight(currentNode->right);
			return rotateLeft(currentNode);
		}
		else {
			return rotateLeft(currentNode);
		}
	}

	return currentNode;
}


// Count all values less than a given value starting from a given node
int myTree::countLess(Node* node, string value) {
	if (node == NULL) {
		return 0;
	}
	if (value <= node->data) {
		return countLess(node->left, value);
	}
	else {
		return 1 + getSubtreeSize(node->left) + countLess(node->right, value);
	}
}


// Count all values less than or equal to a given value starting from a given node
int myTree::countLessEqual(Node* node, string value) {
	if (node == NULL) {
		return 0;
	}
	if (value < node->data) {
		return countLessEqual(node->left, value);
	}
	else {
		return 1 + getSubtreeSize(node->left) + countLessEqual(node->right, value);
	}
}


// Our core feature to return the number of values between two given values
int myTree::range (string val1, string val2) {
	if (root == NULL) {
		return 0;
	}
	string lesser = val1;
	string greater = val2;

	// Sort parameters
	if (val1 > val2) {
		lesser = val2;
		greater = val1;
	}

	// Return all values less than or equal to the high range - all values less than the low range
	return countLessEqual(root, greater) - countLess(root, lesser);
}
