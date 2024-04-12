/**
* @file G221210093
* @description AVL Ağaçları ve Yığınların Uygulanması
* @course Üniversite-2. Öğretim-B
* @assignment 2. Ödev
* @date 24.12.2023
* @author Yiğit Talha Adagülü - yigitadagulu@gmail.com
*/

#ifndef AVL_HW2_STACK_H
#define AVL_HW2_STACK_H
#include "StackNode.h"
class Stack{
    public:
        StackNode *top;
        int size;

        Stack();
        void push(int value);
        int pop();
        int peek();
        bool isEmpty();
        void print();
        ~Stack();
        int sumStackValues();
};


#endif //AVL_HW2_STACK_H
