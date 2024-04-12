/**
* @file G221210093
* @description AVL Ağaçları ve Yığınların Uygulanması
* @course Üniversite-2. Öğretim-B
* @assignment 2. Ödev
* @date 24.12.2023
* @author Yiğit Talha Adagülü - yigitadagulu@gmail.com
*/

#ifndef AVL_HW2_AVL_H
#define AVL_HW2_AVL_H

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Stack.h"

struct AVLNode {
    int key;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {

private:
    AVLNode *root;



    AVLNode* insert(AVLNode* node, int key);
    AVLNode* remove(AVLNode* node, int key);
    int getHeight(AVLNode* N) const;
    int getBalanceFactor(AVLNode* N) const;
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* deleteNode(AVLNode* root, int key);
    void postorderTraversal(AVLNode* root) const;
    void deleteTree(AVLNode* node);

public:
    AVLTree(int index);
    ~AVLTree();
    int index;
    void insert(int key);
    void remove(int key);
    void inorderTraversal() const;
    Stack *stack;
    bool isElementExist(int key);
    void insertNewTreetoNext(AVLTree* tree);
    AVLTree *next;
    AVLNode* getRoot();
    void addLeafsofAVLTree2Stack(AVLNode* node);
    AVLTree* getAVLTreebyIndex(int index);
    int sumAllNodes(AVLNode* node);

};

#endif // AVL_TREE_H



#endif //AVL_HW2_AVL_H
