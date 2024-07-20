#pragma once
#include <iostream>

using namespace std;

class btreenode
{
    int* key;
    int t;
    btreenode** c;
    int n;
    bool leaf;

public:

    btreenode(int _t, bool _leaf);
    void insertnonfull(int k);

    void splitchild(int i, btreenode* y);
    void traverse();
    btreenode* search(int k);
    int findkey(int k);
    void remove(int k);
    void removefromleaf(int idx);
    void removefromnonleaf(int idx);
    int getpred(int idx);
    int getsucc(int idx);
    void fill(int idx);
    void borrowfromprev(int idx);
    void borrowfromnext(int idx);
    void merge(int idx);

    friend class btree;

};

class btree
{
    btreenode* root;
    int t;

public:

    btree(int _t)
    {
        root = NULL;
        t = _t;
    }
    void traverse()

    {
        if (root != NULL)

            root->traverse();

    }
    void insert(int k);
    btreenode* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
    void remove(int k);
};

btreenode::btreenode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    key = new int[2 * t - 1];
    c = new btreenode * [2 * t];
    n = 0;
}

void btreenode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            c[i]->traverse();
        cout << " " << key[i];

    }

    if (leaf == false)

        c[i]->traverse();

}

void btree::insert(int k, File f)

{
    if (root == NULL)
    {
        root = new btreenode(t, true);
        root->key[0] = k;
        root->n = 1;
    }

    else
    {
        if (root->n == 2 * t - 1)

        {

            btreenode* s = new btreenode(t, false);
            s->c[0] = root;
            s->splitchild(0, root);
            int i = 0;
            if (s->key[0] < k)
                i++;
            s->c[i]->insertnonfull(k);
            root = s;
        }
        else
            root->insertnonfull(k);

    }

}

void btreenode::insertnonfull(int k)

{

    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && key[i] > k)

        {

            key[i + 1] = key[i];

            i--;

        }

        key[i + 1] = k;

        n = n + 1;

    }

    else
    {

        while (i >= 0 && key[i] > k)

            i--;

        if (c[i + 1]->n == 2 * t - 1)

        {

            splitchild(i + 1, c[i + 1]);

            if (key[i + 1] < k)

                i++;

        }

        c[i + 1]->insertnonfull(k);

    }

}

void btreenode::splitchild(int i, btreenode* y)

{

    btreenode* z = new btreenode(y->t, y->leaf);

    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)

        z->key[j] = y->key[j + t];

    if (y->leaf == false)

    {

        for (int j = 0; j < t; j++)

            z->c[j] = y->c[j + t];

    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        c[j + 1] = c[j];
    c[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        key[j + 1] = key[j];
    key[i] = y->key[t - 1];

    n = n + 1;

}

btreenode* btreenode::search(int k)
{

    int i = 0;

    while (i < n && k > key[i])

        i++;
    if (key[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return c[i]->search(k);

}

int btreenode::findkey(int k)

{

    int idx = 0;

    while (idx < n && key[idx] < k)

        ++idx;

    return idx;

}

void btreenode::remove(int k)

{

    int idx = findkey(k);

    if (idx < n && key[idx] == k)

    {

        if (leaf)

            removefromleaf(idx);

        else

            removefromnonleaf(idx);

    }

    else

    {

        if (leaf)

        {

            cout << "The key " << k << " is not found in the tree\n";

            return;

        }

        bool flag = ((idx == n) ? true : false);

        if (c[idx]->n < t)

            fill(idx);
        if (flag && idx > n)

            c[idx - 1]->remove(k);

        else

            c[idx]->remove(k);

    }

    return;

}

void btreenode::removefromleaf(int idx)

{
    for (int j = idx + 1; j < n; ++j)

        key[j - 1] = key[j];

    n--;

    return;

}

void btreenode::removefromnonleaf(int idx)
{
    int k = key[idx];

    if (c[idx]->n >= t)

    {

        int pred = getpred(idx);

        key[idx] = pred;

        c[idx]->remove(pred);

    }

    else if (c[idx + 1]->n >= t)
    {


        int succ = getsucc(idx);

        key[idx] = succ;

        c[idx + 1]->remove(succ);

    }

    else

    {

        merge(idx);

        c[idx]->remove(k);

    }

    return;

}

int btreenode::getpred(int idx)
{
    btreenode* cur = c[idx];
    while (!cur->leaf)
        cur = cur->c[cur->n];
    return cur->key[cur->n - 1];
}

int btreenode::getsucc(int idx)

{

    btreenode* cur = c[idx + 1];

    while (!cur->leaf)
        cur = cur->c[0];

    return cur->key[0];

}

void btreenode::fill(int idx)

{

    if (idx != 0 && c[idx - 1]->n >= t)
        borrowfromprev(idx);

    else if (idx != n && c[idx + 1]->n >= t)
        borrowfromnext(idx);

    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);

    }

    return;

}

void btreenode::borrowfromprev(int idx)

{

    btreenode* child = c[idx];

    btreenode* sibling = c[idx - 1];
    for (int i = child->n - 1; i >= 0; --i)

        child->key[i + 1] = child->key[i];

    if (!child->leaf)

    {

        for (int i = child->n; i >= 0; --i)

            child->c[i + 1] = child->c[i];

    }

    child->key[0] = key[idx - 1];

    if (!child->leaf)

        child->c[0] = sibling->c[sibling->n];


    key[idx - 1] = sibling->key[sibling->n - 1];

    child->n += 1;

    sibling->n -= 1;

    return;

}

void btreenode::borrowfromnext(int idx)

{

    btreenode* child = c[idx];

    btreenode* sibling = c[idx + 1];

    child->key[(child->n)] = key[idx];


    if (!(child->leaf))

        child->c[(child->n) + 1] = sibling->c[0];

    key[idx] = sibling->key[0];

    for (int j = 1; j < sibling->n; ++j)

        sibling->key[j - 1] = sibling->key[j];

    if (!sibling->leaf)

    {

        for (int j = 1; j <= sibling->n; ++j)

            sibling->c[j - 1] = sibling->c[j];

    }

    child->n++;

    sibling->n--;

    return;

}

void btreenode::merge(int idx)

{

    btreenode* child = c[idx];

    btreenode* sibling = c[idx + 1];

    child->key[t - 1] = key[idx];

    for (int j = 0; j < sibling->n; ++j)

        child->key[j + t] = sibling->key[j];


    if (!child->leaf)

    {

        for (int j = 0; j <= sibling->n; ++j)

            child->c[j + t] = sibling->c[j];

    }

    for (int i = idx + 1; i < n; ++i)

        key[i - 1] = key[i];

    for (int j = idx + 2; j <= n; ++j)

        c[j - 1] = c[j];

    child->n += sibling->n + 1;

    n--;

    delete(sibling);

    return;

}

void btree::remove(int k)

{

    if (!root)

    {

        cout << "The tree is empty\n";

        return;

    }

    root->remove(k);

    if (root->n == 0)
    {
        btreenode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->c[0];

        delete tmp;
    }

    return;

}
