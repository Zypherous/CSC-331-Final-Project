#include "BSTree.h"

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
        cout << p->info
             << " Times Used:"
             << p->timesUsed
             << " Length: "
             << p->length
             << endl;
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
                cout << "Duplicate, increasing coutner\n";
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
    trail->length = trail->info.length(); // Solve for the length issue, look at the previous lines. It seems
    // like I might have to make it so that temp.length is = to temp.info.length();
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

