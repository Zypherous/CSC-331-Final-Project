/******************************************************/
/* Programmer:Jonathan Rosario                        */
/* Date: 12/10/2020                                   */
/* Purpose: Binary Search Tree implementation file    */                                      
/******************************************************/
#include "BSTree.h"
#include <iomanip>

template <class T>
BSTree<T> ::BSTree()
{
    root = NULL;
}

template <class T>
BSTree<T> :: ~BSTree()
{
    destroy(root);
}

template <class T>
void BSTree<T> ::destroy(node<T>*& p)
{
    if (p != NULL)
    {
        destroy(p->left);
        destroy(p->right);
        delete p;
        p = NULL;
    }

}

template <class T>
BSTree<T> ::BSTree(const BSTree<T>& other)
{
    copy(root, other.root);
}

template <class T>
const BSTree<T>& BSTree<T> :: operator= (const BSTree<T>& other)
{
    if (&other != this)
    {
        if (root != NULL)
            destroy(root);
        if (other.root == NULL)
            root = NULL;
        else
            copy(root, other.root);
    }
    return *this;
}

template <class T>
void BSTree<T> ::copy(node<T>*& nroot, node<T>* croot)
{
    if (croot == NULL)
        nroot = NULL;
    else
    {
        nroot = new node<T>;
        nroot->info = croot->info;
        copy(nroot->left, croot->left);
        copy(nroot->right, croot->right);
    }
}

template <class T>
bool BSTree<T> ::isEmpty()
{
    return root == NULL;
}

template <class T>
void BSTree<T> ::printPreorder()
{
    printPreorder(root);

}

template <class T>
void BSTree<T> ::printPreorder(node<T>* p)
{
    if (p != NULL)
    {
        cout << p->info << " " << endl;
        printPreorder(p->left);
        printPreorder(p->right);
    }
}

template <class T>
void BSTree<T> ::printPostorder()
{
    printPostorder(root);

}

template <class T>
void BSTree<T> ::printPostorder(node<T>* p)
{
    if (p != NULL)
    {

        printPostorder(p->left);
        printPostorder(p->right);
        cout << p->info << " " << endl;
    }
}

template <class T>
void BSTree<T> ::printInorder()
{
    printInorder(root);

}

template <class T>
void BSTree<T> ::printInorder(node<T>* p)
{
    if (p != NULL)
    {

        printInorder(p->left);
        // Prints information in tree using a modification of the normal print in order function to display other variables in each node
        cout << p->info
             << " Times Used:"
             << p->timesUsed
             << " Length: "
             << p->length
             << "\n";
        printInorder(p->right);

    }

}


template <class T>
void BSTree<T> ::insertItem(T item)
{
    node<T>* p = NULL;
    node<T>* trail = NULL;
    node<T>* temp = NULL;

    temp = new node<T>;
    temp->info = item;
    temp->left = NULL;
    temp->right = NULL;

    if (root == NULL)
        root = temp;
    else
    {
        p = root;

        while (p != NULL)
        {
            trail = p;

            if (p->info == item)
            {
                // Increasing counter of times used in node
                p->timesUsed += 1;
                delete temp;
                return;
            }
            else if (p->info > item)
                p = p->left;
            else
                p = p->right;
        }

        if (trail->info > item)
            trail->left = temp;
        else
            trail->right = temp;
    }
    // Saving the length information to node
    temp->length = temp->info.length(); 
}

template <class T>
bool BSTree<T> ::searchItem(T item)
{
    bool found;
    node<T>* p;

    found = false;
    p = root;

    while (p != NULL && !found)
    {
        if (p->info == item)
            found = true;
        else if (p->info > item)
            p = p->left;
        else
            p = p->right;
    }

    return found;
}

template <class T>
void BSTree<T> ::deleteItem(T item)
{
    deleteItem(root, item);
}

template <class T>
void BSTree<T> ::deleteItem(node<T>*& p, T item)
{
    if (p == NULL)
        cout << "ITEM NOT IN THE TREE";
    else if (item < p->info)
        deleteItem(p->left, item);
    else if (item > p->info)
        deleteItem(p->right, item);
    else
        deleteNode(p);
}

template <class T>
void BSTree<T> ::deleteNode(node<T>*& p)
{
    node<T>* q;

    q = p;

    if (p->left == NULL)
    {
        p = p->right;
        delete q;
    }
    else if (p->right == NULL)
    {
        p = p->left;
        delete q;
    }
    else
    {
        node<T>* q = p->left;
        node<T>* r = NULL;

        while (q->right != NULL)
        {
            r = q;
            q = q->right;
        }

        p->info = q->info;

        if (r != NULL)
            r->right = q->left;
        else
            p->left = q->left;

        delete q;
    }
}

#pragma region Functions added to BSTree for this project
// uniqueWordsTotal //
//******************************************************************************
// Parameters: Pointer to node
// Function: Takes a pointer to a node of type T, the root of a BS Tree and
//           traverses the tree, counting only words with a length greater than 3
//           and that have only been used once.
// Returns:  integer holding the total number of unique words used
//******************************************************************************
template <class T>
int BSTree<T> :: uniqueWordsTotal(const node<T>* root)
{
    int used;
    if (root->timesUsed == 1 && root->length > 3) {
        used = 1;
    }
    else {
        used = 0;
    }
    if (root->left != NULL) {
        
        used += uniqueWordsTotal(root->left);
    }
    if (root->right != NULL) {
        used += uniqueWordsTotal(root->right);
    }
    return used;
}

// uniqueWordsUsed//
//******************************************************************************
// Parameters: None
// Function: Calls uniqueWordsTotal preventing user from accessing private node
//
// Returns:  integer holding the total number of unique words with length > 3 
//******************************************************************************
template <class T>
int BSTree<T> :: uniqueWordsUsed()
{
    int count = 0;
    if (root != NULL) {
        count = uniqueWordsTotal(root);
    }
    return count;
}


// uniqueWordsTotalAll //
//******************************************************************************
// Parameters: Pointer to node
// Function: Takes a pointer to a node of type T, the root of a BS Tree and
//           traverses the tree, counting words that have only been used once.
// Returns:  integer holding the total number of unique words used
//******************************************************************************
template <class T>
int BSTree<T> ::uniqueWordsTotalAll(const node<T>* root)
{
    int used;
    if (root->timesUsed == 1 ) {
        used = 1;
    }
    else {
        used = 0;
    }
    if (root->left != NULL) {

        used += uniqueWordsTotalAll(root->left);
    }
    if (root->right != NULL) {
        used += uniqueWordsTotalAll(root->right);
    }
    return used;
}

// uniqueWordsUsedAll//
//******************************************************************************
// Parameters: None
// Function: Calls uniqueWordsTotalAll preventing user from accessing private node
//
// Returns:  integer holding the total number of unique words used
//******************************************************************************
template <class T>
int BSTree<T> ::uniqueWordsUsedAll()
{
    int count = 0;
    if (root != NULL) {
        count = uniqueWordsTotalAll(root);
    }
    return count;
}


// printInorderIndex //
//******************************************************************************
// Parameters: character, output file stream address
// Function: Takes a character and output file stream to call printInorderIndex
//           that has root node access. Some formatting for index
// Returns:  None
//******************************************************************************
template <class T>
void BSTree<T> ::printInorderIndex(char firstLetter , ofstream &output)
{ 
    output  << setw(8) << firstLetter << right << "\n";
    printInorderIndex(root, firstLetter, output);
}

// printInorderIndex //
//******************************************************************************
// Parameters: pointer to node, character, output file stream address
// Function: Takes the root node, then a character to compare the first character
//           of each node's info and then outputs it to the file stream if it is
//           a match.
// Returns:  None
//******************************************************************************
template <class T>
void BSTree<T> ::printInorderIndex(node<T>* p , char firstLetter, ofstream &output)
{
    if (p != NULL)
    {

        printInorderIndex(p->left,firstLetter,  output);
        //Attempt to print alphabet index
        if(p->info[0] == firstLetter){
            output<< p->info << "\n";
        }
        printInorderIndex(p->right,firstLetter,  output);

    }
}

// printOften //
//******************************************************************************
// Parameters: integer, output file stream address
// Function: Takes an integer and output file stream to call printOften
//           that has root node access. 
// Returns:  None
//******************************************************************************
template <class T>
void BSTree<T> ::printOften(int totalWords, ofstream &output)
{
    printOften(root,totalWords,  output);
}

// printOften //
//******************************************************************************
// Parameters: pointer to node, integer, output file stream address
// Function: Takes the root node, then an integer of total words to compare  
//           the times used of each node and then outputs it to the file stream 
//           if it is used more than 5% of the total words
// Returns:  None
//******************************************************************************
template <class T>
int BSTree<T> ::printOften(node<T>* p, int totalWords , ofstream &output)
{
    int count = 0;
    if (p != NULL)
    {

        count += printOften(p->left, totalWords,  output);
        //Attempt to print alphabet index
        if (p->timesUsed/static_cast<float>(totalWords) > .05 && p->length > 3) {
            output << count + 1 <<  ") " << p->info << "\n";
            count++;
        }
        count += printOften(p->right, totalWords,  output);

    }
    return count;
}

#pragma endregion BS Tree functions specifically for this project