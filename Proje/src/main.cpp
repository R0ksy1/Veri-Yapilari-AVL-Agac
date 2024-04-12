/**
* @file G221210093
* @description AVL Ağaçları ve Yığınların Uygulanması
* @course Üniversite-2. Öğretim-B
* @assignment 2. Ödev
* @date 24.12.2023
* @author Yiğit Talha Adagülü - yigitadagulu@gmail.com
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Avl.h"
#include <windows.h>

int global_string_index = 0;
char convertAscii(int value) {
    char character = static_cast<char>(value);
    return character;
}

int calculate_ascii(int number){
    return number%26 + 65;;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void removeCharAtIndexAndPrint(std::string& str, size_t index) {
    
    Sleep(45);
    if (index < str.size()) {
        str.erase(index, 1);
        gotoxy(0, 0);
        std::cout << str << std::flush;
        std::cout << std::string(50, ' ');
        gotoxy(0, 0);
    }
}

AVLTree* readFromFile(AVLTree* rootTree, std::string filePath) {
    std::ifstream inputFile(filePath);
    std::string currentLine;

    if (!inputFile.is_open()) {
        return nullptr;
    }
    int treeIndex = 1;
    while (std::getline(inputFile, currentLine)) {
        AVLTree *newTree = new AVLTree(treeIndex);
        newTree->next = nullptr;
        std::istringstream lineStream(currentLine);
        int element;

        while (lineStream >> element) {
            bool isElementFound = newTree->isElementExist(element);
            if (!isElementFound) {
                newTree->insert(element);
            }
        }
        AVLTree* tempTree = rootTree;
        if (tempTree == nullptr){
            rootTree = newTree;
        }
        else {
            while(tempTree->next != nullptr){
                tempTree = tempTree->next;
            }
            tempTree->insertNewTreetoNext(newTree);
        }

        treeIndex += 1;
    }

    inputFile.close();
    return rootTree;
}


AVLTree* delete_min_max(AVLTree* root, bool is_min){
    AVLTree *node = root;
    if (is_min){
        int min_index = 0;
        int min_value = 999999;
        int counter = 0;
        int current_value;
        while (node != nullptr) {
            current_value = node->stack->peek();
            if (current_value < min_value) {
                min_value = current_value;
                min_index = counter;
            }
            counter += 1;
            node = node->next;
        }
        AVLTree *min_tree = root->getAVLTreebyIndex(min_index);
        min_tree->stack->pop();
        if (min_tree->stack->isEmpty()) {
            global_string_index = min_index;
            if (min_index != 0) {
                root->getAVLTreebyIndex(min_index - 1)->next = min_tree->next;
            } else {
                root = root->getAVLTreebyIndex(min_index + 1);
            }
            min_tree->next = nullptr;
            delete min_tree;
            return root;
        }
    } else {
        int max_index = 0;
        int max_value = -999999;
        int counter = 0;
        int current_value;
        while (node != nullptr) {
            current_value = node->stack->peek();
            if (current_value > max_value) {
                max_value = current_value;
                max_index = counter;
            }
            counter += 1;
            node = node->next;
        }
        AVLTree *min_tree = root->getAVLTreebyIndex(max_index);
        min_tree->stack->pop();
        if (min_tree->stack->isEmpty()) {
            global_string_index = max_index;
            if (max_index != 0) {
                root->getAVLTreebyIndex(max_index - 1)->next = min_tree->next;
            } else {
                root = root->getAVLTreebyIndex(max_index + 1);
            }
            min_tree->next = nullptr;
            delete min_tree;
            return root;
        }
    }
    return nullptr;
}

std::string print(AVLTree* root){
    int ascii = calculate_ascii(root->sumAllNodes(root->getRoot()) - root->stack->sumStackValues());
    char character = convertAscii(ascii);
    std::string str(1,character);
    return str;
}


int main() {
    AVLTree* root = NULL;
    root = readFromFile(root, "Veri.txt");
    AVLTree* node = root;
    while(node != nullptr){
        node->addLeafsofAVLTree2Stack(node->getRoot());
        node = node->next;
    }
    std::string str = "";

    bool is_min = true;
    while(root->next != nullptr){
        AVLTree* deletedTree = delete_min_max(root, is_min);
        if (deletedTree){
            root = deletedTree;


            AVLTree* node = root;
            while (node != nullptr){
                delete node->stack;
                node->stack = new Stack();
                node->addLeafsofAVLTree2Stack(node->getRoot());
                node = node->next;
            }
            is_min = true;
            str = "";
            AVLTree* strtemp = root;
            while(strtemp != nullptr){
                str += print(strtemp);
                strtemp = strtemp->next;
            }
            removeCharAtIndexAndPrint(str, global_string_index);
        }
        else is_min = !is_min;
    }
    removeCharAtIndexAndPrint(str, 0);
    removeCharAtIndexAndPrint(str, 1);
    int ascii = calculate_ascii(root->sumAllNodes(root->getRoot()) - root->stack->sumStackValues());
    char character = convertAscii(ascii);
    std::cout << std::endl << "Son Karakter: " << character << std::endl;
    std::cout << "AVL No: " << root->index << std::endl;
    Sleep(4000);


}

                                                                                                                                                    //B
