#include "BTreeNode.h"

btreenode::btreenode(int t1, bool leaf1)
{
    t = t1;
    isleaf = leaf1;
    keyofFile = new int[2 * t - 1];
    filepath = new File[2 * t - 1];
    c = new btreenode * [2 * t];
    n = 0;
}

void btreenode::displayAllData()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (isleaf == false)
            c[i]->displayAllData();
        std::cout << "File ";
        std::cout << "\t" << keyofFile[i];
        std::cout << "\t" << filepath[i].name;
        std::cout << "\t" << filepath[i].path;
        std::cout << "\n";
    }

    if (isleaf == false)

        c[i]->displayAllData();

}

void btreenode::insertnonfull(int k, File f)

{

    int i = n - 1;

    if (isleaf == true)
    {
        while (i >= 0 && keyofFile[i] > k)

        {

            keyofFile[i + 1] = keyofFile[i];
            filepath[i + 1] = filepath[i];

            i--;

        }

        keyofFile[i + 1] = k;
        filepath[i + 1] = f;

        n = n + 1;

    }

    else
    {

        while (i >= 0 && keyofFile[i] > k)

            i--;

        if (c[i + 1]->n == 2 * t - 1)

        {

            splitchild(i + 1, c[i + 1]);

            if (keyofFile[i + 1] < k)

                i++;

        }

        c[i + 1]->insertnonfull(k, f);

    }

}

void btreenode::splitchild(int i, btreenode* y)

{

    btreenode* z = new btreenode(y->t, y->isleaf);

    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)

        z->keyofFile[j] = y->keyofFile[j + t];

    if (y->isleaf == false)

    {

        for (int j = 0; j < t; j++)

            z->c[j] = y->c[j + t];

    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        c[j + 1] = c[j];
    c[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keyofFile[j + 1] = keyofFile[j];
    keyofFile[i] = y->keyofFile[t - 1];

    n = n + 1;

}

btreenode* btreenode::search(int k)
{

    int i = 0;

    while (i < n && k > keyofFile[i])

        i++;
    if (keyofFile[i] == k)
        return this;

    if (isleaf == true)
        return NULL;

    return c[i]->search(k);

}

int btreenode::findkey(int k)

{

    int idx = 0;

    while (idx < n && keyofFile[idx] < k)

        ++idx;

    return idx;

}

void btreenode::remove(int k)

{

    int idx = findkey(k);

    if (idx < n && keyofFile[idx] == k)

    {

        if (isleaf)

            removefromleaf(idx);

        else

            removefromnonleaf(idx);

    }

    else

    {

        if (isleaf)

        {

            std::cout << "The key " << k << " is not found in the tree\n";

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

        keyofFile[j - 1] = keyofFile[j];

    n--;

    return;

}

void btreenode::removefromnonleaf(int idx)
{
    int k = keyofFile[idx];

    if (c[idx]->n >= t)

    {

        int pred = getpred(idx);

        keyofFile[idx] = pred;

        c[idx]->remove(pred);

    }

    else if (c[idx + 1]->n >= t)
    {


        int succ = getsucc(idx);

        keyofFile[idx] = succ;

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
    while (!cur->isleaf)
        cur = cur->c[cur->n];
    return cur->keyofFile[cur->n - 1];
}

int btreenode::getsucc(int idx)

{

    btreenode* cur = c[idx + 1];

    while (!cur->isleaf)
        cur = cur->c[0];

    return cur->keyofFile[0];

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

        child->keyofFile[i + 1] = child->keyofFile[i];

    if (!child->isleaf)

    {

        for (int i = child->n; i >= 0; --i)

            child->c[i + 1] = child->c[i];

    }

    child->keyofFile[0] = keyofFile[idx - 1];

    if (!child->isleaf)

        child->c[0] = sibling->c[sibling->n];


    keyofFile[idx - 1] = sibling->keyofFile[sibling->n - 1];

    child->n += 1;

    sibling->n -= 1;

    return;

}

void btreenode::borrowfromnext(int idx)

{

    btreenode* child = c[idx];

    btreenode* sibling = c[idx + 1];

    child->keyofFile[(child->n)] = keyofFile[idx];


    if (!(child->isleaf))

        child->c[(child->n) + 1] = sibling->c[0];

    keyofFile[idx] = sibling->keyofFile[0];

    for (int j = 1; j < sibling->n; ++j)

        sibling->keyofFile[j - 1] = sibling->keyofFile[j];

    if (!sibling->isleaf)

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

    child->keyofFile[t - 1] = keyofFile[idx];

    for (int j = 0; j < sibling->n; ++j)

        child->keyofFile[j + t] = sibling->keyofFile[j];


    if (!child->isleaf)

    {

        for (int j = 0; j <= sibling->n; ++j)

            child->c[j + t] = sibling->c[j];

    }

    for (int i = idx + 1; i < n; ++i)

        keyofFile[i - 1] = keyofFile[i];

    for (int j = idx + 2; j <= n; ++j)

        c[j - 1] = c[j];

    child->n += sibling->n + 1;

    n--;

    delete(sibling);

    return;

}