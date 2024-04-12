/**
* @file G221210093
* @description AVL Ağaçları ve Yığınların Uygulanması
* @course Üniversite-2. Öğretim-B
* @assignment 2. Ödev
* @date 24.12.2023
* @author Yiğit Talha Adagülü - yigitadagulu@gmail.com
*/

#ifndef AVL_HW2_STACKNODE_H
#define AVL_HW2_STACKNODE_H

class StackNode {
    public:
        int value;
        StackNode *next;

        StackNode(int value);

};

#endif //AVL_HW2_STACKNODE_H
