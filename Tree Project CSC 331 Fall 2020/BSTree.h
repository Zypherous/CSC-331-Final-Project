/******************************************************/
/* Programmer:Jonathan Rosario                        */
/* Date: 12/10/2020                                   */
/* Purpose: Binary Search Tree heade file             */
/******************************************************/
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

    // Variable to keep track of how many times a word is used
    int timesUsed = 1;

    // Variable to hold the number of characters in word stored
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

    // Functions added for this project
    void printInorderIndex(node<T>* , char , ofstream&);
    int uniqueWordsTotal(const node<T>*);
    int printOften(node<T>* , int , ofstream&);
    int uniqueWordsTotalAll(const node<T>*);

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

    // Functions added for this project
    void printInorderIndex(char firstLetter, ofstream&);
    int uniqueWordsUsed();
    void printOften(int, ofstream&);
    int uniqueWordsUsedAll();
};

#endif