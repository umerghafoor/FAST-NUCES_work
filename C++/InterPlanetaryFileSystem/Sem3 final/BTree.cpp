#include "BTree.h"

// Constructor for a B-tree, initializes the root to nullptr and sets the order of the tree.
btree::btree(int key)
{
    root = nullptr;
    t = key;
}

// Searches for a key in the B-tree and returns the corresponding node; returns nullptr if the tree is empty.
btreenode* btree::search(int keytosearch)
{
    return (root == nullptr) ? nullptr : root->search(keytosearch);
}

// Inserts a key-value pair into the B-tree. If the root is empty, it creates a new root; otherwise, it inserts into the existing tree.
void btree::insert(int keytoinsert, File file)

{
    if (root == nullptr)
    {
        // Create a new root and insert the key-value pair.
        root = new btreenode(t, true);
        root->keyofFile[0] = keytoinsert;
        root->filepath[0] = file;
        root->n = 1;
    }

    else
    {
        if (root->n == 2 * t - 1)

        {
            // If the root is full, split it and create a new root.
            btreenode* s = new btreenode(t, false);
            s->c[0] = root;
            s->splitchild(0, root);
            int i = 0;
            if (s->keyofFile[0] < keytoinsert)
                i++;
            s->c[i]->insertnonfull(keytoinsert, file);
            root = s;
        }
        else
            // If the root is not full, insert into the existing tree.
            root->insertnonfull(keytoinsert, file);

    }

}

// Initiates the traversal of the B-tree starting from the root, if it is not nullptr.
void btree::displayAllData()
{
    if (root != nullptr)
        root->displayAllData();
}

// Removes a key from the B-tree. If the root is empty, displays an empty tree message; otherwise, delegates the removal to the root node.
void btree::remove(int keytoremove)

{

    if (root == nullptr)
    {
        std::cout << "The tree is empty\n";
        return;
    }

    // Delegate the removal operation to the root node.
    root->remove(keytoremove);

    // If the root becomes empty after removal, adjust the tree.
    if (root->n == 0)
    {
        btreenode* temporary = root;

        // If the root is a leaf, set it to nullptr; otherwise, update the root to its child
        if (root->isleaf)
            root = nullptr;
        else
            root = root->c[0];

        delete temporary;
    }

    return;
}