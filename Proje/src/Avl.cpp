/**
* @file G221210093
* @description AVL Ağaçları ve Yığınların Uygulanması
* @course Üniversite-2. Öğretim-B
* @assignment 2. Ödev
* @date 24.12.2023
* @author Yiğit Talha Adagülü - yigitadagulu@gmail.com
*/

#include "../include/avl.h"
#include <iostream>

AVLTree::AVLTree(int index) : root(nullptr) {
    this->index = index;
    this->stack = new Stack();
}

AVLTree::~AVLTree() {
    deleteTree(root);
    delete stack;

    root = nullptr;
    stack = nullptr;

}

void AVLTree::addLeafsofAVLTree2Stack(AVLNode *node) {
    if (node != nullptr) {
        addLeafsofAVLTree2Stack(node->left);
        if (node->left == nullptr && node->right == nullptr) {
            this->stack->push(node->key);
            this->stack->size++;
        }
        addLeafsofAVLTree2Stack(node->right);
    }
}
AVLNode* AVLTree::getRoot() {
    return this->root;
}

void AVLTree::insert(int key) {
    root = insert(root, key);
}

void AVLTree::remove(int key) {
    root = remove(root, key);
}
AVLTree* AVLTree::getAVLTreebyIndex(int index) {
    AVLTree* temp = this;
    int counter = 0;
    while (temp != nullptr) {
        if (counter == index) {
            return temp;
        }
        counter++;
        temp = temp->next;
    }
    return temp;
}

void AVLTree::inorderTraversal() const {
    postorderTraversal(root);
}

int AVLTree::getHeight(AVLNode *N) const {
    if (N == nullptr)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* AVLTree::rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int AVLTree::getBalanceFactor(AVLNode *N) const {
    if (N == nullptr)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

AVLNode* AVLTree::insert(AVLNode* node, int key) {
    if (node == nullptr)
        return(new AVLNode(key));
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);
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

AVLNode* AVLTree::remove(AVLNode* root, int key) {
    if (root == nullptr)
        return root;
    if (key < root->key)
        root->left = remove(root->left, key);
    else if(key > root->key)
        root->right = remove(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode *temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
    }
    if (root == nullptr)
        return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void AVLTree::postorderTraversal(AVLNode *root) const {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << root->key << " ";
    }
}

void AVLTree::deleteTree(AVLNode* node) {
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

bool AVLTree::isElementExist(int key) {
    AVLNode *temp = this->root;
    while (temp != nullptr) {
        if (temp->key == key) {
            return true;
        } else if (temp->key > key) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return false;
}

void AVLTree::insertNewTreetoNext(AVLTree *tree) {
    this->next = tree;
}

int AVLTree::sumAllNodes(AVLNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->key + sumAllNodes(node->left) + sumAllNodes(node->right);
}
