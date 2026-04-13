#include <iostream>
#include <string>
#include "avl.h"

using namespace std;

#define LEFT_IMBALANCE 2
#define RIGHT_IMBALANCE -2

myTree::Node::Node(string value) {
	data = value;
	left = NULL;
	right = NULL;
	height = 1;
	subtreeSize = 1;
}


myTree::myTree() {
	root = NULL;
}


int myTree::getSubtreeSize(Node* node) {
	if (node == NULL) {
		return 0;
	}
	return node->subtreeSize;
}


int myTree::getHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}


int myTree::updateHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	return node->height;
}


int myTree::updateSubtreeSize(Node* node) {
	if (node == NULL) {
		return 0;
	}
	node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);
	return node->subtreeSize;
}


myTree::Node* myTree::rotateRight(Node* nodeToRotate){
	Node* newParent = nodeToRotate->left;
	Node* grandChild = newParent->right;

	newParent->right = nodeToRotate;
	nodeToRotate->left = grandChild;

	updateHeight(nodeToRotate);
	updateHeight(newParent);

	updateSubtreeSize(nodeToRotate);
	updateSubtreeSize(newParent);

	return newParent;
}


myTree::Node* myTree::rotateLeft(Node* nodeToRotate) {
	Node* newParent = nodeToRotate->right;
	Node* grandChild = newParent->left;

	newParent->left = nodeToRotate;
	nodeToRotate->right = grandChild;

	updateHeight(nodeToRotate);
	updateHeight(newParent);

	updateSubtreeSize(nodeToRotate);
	updateSubtreeSize(newParent);

	return newParent;
}	


int myTree::checkBalance(Node* node) {
	if (node == NULL) { return 0; }
	return getHeight(node->left) - getHeight(node->right);
}


void myTree::insert(string value) {
	root = insertRecursive(value, root);
}


myTree::Node* myTree::insertRecursive(string value, Node* currentNode) {

	if (currentNode == NULL) {
		return new Node(value);
	}

	if (currentNode->data > value) {
		currentNode->left = insertRecursive(value, currentNode->left);
	}
	else if (currentNode->data < value) {
		currentNode->right = insertRecursive(value, currentNode->right);
	}
	else {
		return currentNode;
	}

	updateHeight(currentNode);
	updateSubtreeSize(currentNode);
	int currentBalance = checkBalance(currentNode);

	if (currentBalance >= LEFT_IMBALANCE) {
		if (value > currentNode->left->data) {
			currentNode->left = rotateLeft(currentNode->left);
			return rotateRight(currentNode);
		}
		else {
			return rotateRight(currentNode);
		}
	}
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


int myTree::range (string val1, string val2) {
	if (root == NULL) {
		return 0;
	}
	string lesser = val1;
	string greater = val2;

	if (val1 > val2) {
		lesser = val2;
		greater = val1;
	}

	return countLessEqual(root, greater) - countLess(root, lesser);
}
