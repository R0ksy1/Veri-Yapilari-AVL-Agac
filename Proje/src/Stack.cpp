/**
* @file G221210093
* @description AVL Ağaçları ve Yığınların Uygulanması
* @course Üniversite-2. Öğretim-B
* @assignment 2. Ödev
* @date 24.12.2023
* @author Yiğit Talha Adagülü - yigitadagulu@gmail.com
*/

#include "../include/Stack.h"
#include "../include/StackNode.h"

Stack::Stack() {
    this->top = nullptr;
}

bool Stack::isEmpty() {
    return this->top == nullptr;
}

void Stack::push(int value) {
    StackNode *temp = new StackNode(value);
    temp->next = this->top;
    this->top = temp;
}

int Stack::pop() {
    if (this->isEmpty()) {
        throw "Stack is empty";
    }
    StackNode *temp = this->top;
    this->top = this->top->next;
    temp->next = nullptr;
    return temp->value;
}

int Stack::peek() {
    if (this->isEmpty()) {
        throw "Stack is empty";
    }
    return this->top->value;
}

Stack::~Stack() {
    while (top != nullptr) {
        StackNode* temp = top;
        top = top->next;
        temp->next = nullptr;
        delete temp;
    }
}


int Stack::sumStackValues() {
    int total = 0;
    StackNode* temp = this->top;
    while (temp != nullptr) {
        total += temp->value;
        temp = temp->next;
    }
    return total;
}

// Path: src/AVL.cpp