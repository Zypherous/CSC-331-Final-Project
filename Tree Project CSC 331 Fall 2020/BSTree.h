#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <class T>
struct node
{
    T info;
    node* left;
    node* right;
    int timesUsed = 1;
    int length = 0;
};

template <class T>
class BSTree
{
private:
    node<T>* root;
    void printPreorder(node<T>*);
    void printPostorder(node<T>*);
    void printInorder(node<T>*);
    void deleteItem(node<T>*&, T);
    void deleteNode(node<T>*&);


public:
    BSTree();
    ~BSTree();
    void destroy(node<T>*&);
    const BSTree<T>& operator= (const BSTree<T>&);
    BSTree(const BSTree<T>&);
    void copy(node<T>*&, node<T>*);
    bool isEmpty();
    void insertItem(T item);
    void deleteItem(T item);
    bool searchItem(T item);
    void printPreorder();
    void printPostorder();
    void printInorder();
};

#endif