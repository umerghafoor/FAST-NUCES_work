#include "RingDHT.h"

int HashforComputer(const std::string& input) {
    int hash = 0;

    for (char c : input) {
        hash += static_cast<int>(c);
    }

    std::cout << "hash : " << hash << "\n";

    return hash;
}

Node::Node(int value, int numBits) : data(value), next(nullptr), prev(nullptr) {
    this->Files_btree = new btree(numBits);
    // Initialize routing table with entries for succ(p + 2^i), i = 1, ..., log2(N)
    for (int i = 0; i < numBits; ++i) {
        int entry = (value + (1 << i)) % (1 << numBits);
        routingTable.push_back(nullptr); // Initialize with nullptr, update later
    }
}

RingDHT::RingDHT(int bits) : head(nullptr), numBits(bits) 
{
}

// Function to insert a node in order and update the routing table
void RingDHT::insertInOrder(int value) {
    Node* newNode = new Node(value, numBits);

    if (head == nullptr || value <= head->data)
    {
        // If the list is empty or the value is less than or equal to the head's data,
        // insert at the beginning
        if (head == nullptr)
        {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            Node* last = head->prev;
            last->next = newNode;
            newNode->prev = last;
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

    }
    else
    {
        // Otherwise, find the correct position to insert the new node
        Node* current = head->next;

        while (current != head && value > current->data)
        {
            current = current->next;
        }

        // Insert the new node before the current node
        Node* prevNode = current->prev;

        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = current;
        current->prev = newNode;

        // Update routing table for the new node
    }

    Node* c = head;
    do
    {
        updateRoutingTable(c);

        c = c->next;
    } while (c != head);
}

// Function to update the routing table for a given node
void RingDHT::updateRoutingTable(Node* node)
{
    for (int i = 0; i < numBits; ++i)
    {
        Node* successor = findSuccessor(node, i);
        node->routingTable[i] = successor;
    }
}

// Helper function to find the successor for routing table entries
Node* RingDHT::findSuccessor(Node* node, int index) {
    int target = (node->data + (1 << index)) % (1 << numBits);
    Node* current = head;

    while (current->next != head && (current->next->data % (1 << numBits)) < target)
    {
        current = current->next;
    }

    return current->next;
}
// Function to delete a node with a specific value
void RingDHT::deleteNode(int value) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    Node* current = head;
    Node* nodeToDelete = nullptr;

    // Find the node with the specified value
    do {
        if (current->data == value) {
            nodeToDelete = current;
            break;
        }
        current = current->next;
    } while (current != head);

    // If the node is found, delete it
    if (nodeToDelete != nullptr) {
        if (nodeToDelete == head) {
            // If the node to delete is the head, update the head
            head = head->next;
        }

        // Adjust the pointers of neighboring nodes
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;

        // Delete the node
        delete nodeToDelete;

        // Update routing tables for all nodes
        updateAllRoutingTables();
    }
    else {
        cout << "Node with value " << value << " not found." << endl;
    }
}

// Function to search for a node with a specific value
Node* RingDHT::searchNode(int value) {
    if (head == nullptr) {
        cout << "List is empty. Cannot search." << endl;
        return nullptr;
    }

    Node* current = head;

    // Search for the node with the specified value
    do {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    } while (current != head);

    cout << "Node with value " << value << " not found." << endl;
    return nullptr;
}

// Helper function to update routing tables for all nodes in the list
void RingDHT::updateAllRoutingTables() {
    Node* current = head;
    do {
        updateRoutingTable(current);
        current = current->next;
    } while (current != head);
}


// Function to display the double circular linked list with routing tables
void RingDHT::display() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* current = head;

    do {
        cout << "Computer " << current->data << ":\t [ ";
        for (Node* entry : current->routingTable) {
            cout << (entry ? to_string(entry->data) : "null") << " ";
        }
        cout << "]" << endl;

        current = current->next;
    } while (current != head);

    cout << endl;
}

int RingDHT::getIdentifierBits()
{
    return numBits;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Login::authenticateUser(int nodeIndex)
{
    loggedInUser = dht->searchNode(nodeIndex);

    if (loggedInUser == nullptr)
    {
        return 0;
    }
    return true;
}

Node* Login::getLoggedInUser() const
{
    return loggedInUser;
}

Node* Login::searchNode(int targetIndex) const
{
    if (!loggedInUser) {
        std::cerr << "No user logged in.\n";
        return nullptr;
    }

    Node* current = loggedInUser;
    int steps = 0; // Counter to track the number of nodes traversed
    bool endindex = 0;
    if (targetIndex > current->data)
    {
        endindex = 1;
    }

    std::cout << "Nodes traversed: ";
    std::cout << "Node " << current->data << " -> ";
    for (size_t i = 0; i < dht->getIdentifierBits(); i++) {
        steps++;
        if (targetIndex == current->data) 
        {
            // Found the node with the target index
            std::cout << "Node " << current->data << "\n";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }
        if (targetIndex < current->routingTable[0]->data)
        {
            current = current->routingTable[0];
            std::cout << "Node " << current->data << "\n";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }

        //std::cout << "(" << i << ',' << current->fingerTable[i]->data << ')';
        

        if (current->routingTable[i]->data < current->data && current->data < targetIndex && endindex)
        {
            // Move to the previous node
            if (i == 0)
            {
                current = current->routingTable[i];
                i = -1; // Reset the loop to start from the beginning
                std::cout << "Node " << current->data << " -> ";
                if (current->data < targetIndex)
                {
                    std::cout << "Total nodes traversed: " << steps << "\n";
                    return current;
                }
            }
            else
            {
                current = current->routingTable[i - 1];
                i = -1; // Reset the loop to start from the beginning
                std::cout << "Node " << current->data << " -> ";
            }
        }
        
        else if (targetIndex < current->routingTable[i]->data)
        {
            // Move to the previous node
            current = current->routingTable[i - 1];
            i = -1; // Reset the loop to start from the beginning
            std::cout << "Node " << current->data << " -> ";
        }
        else if (i == dht->getIdentifierBits() - 1)
        {
            current = current->routingTable[i];
            i = -1;
            std::cout << "Node " << current->data << " -> ";
        }
    }

    // Print the last traversed node when the loop completes
    std::cout << "Node " << current->data << "\n";
    std::cout << "Total nodes traversed: " << steps << "\n";

    return current;
}

void Login::insertFile(File file)
{
    if (loggedInUser)
    {
        int comp = HashforComputer(file.name) % (1 << bits);
        Node* node = this->searchNode(comp);
        int key = HashforComputer(file.name);

        node->Files_btree->insert(key, file);
    }
}

void Login::removeFile(string file)
{
    if (loggedInUser)
    {
        int comp = HashforComputer(file) % (1 << bits);
        Node* node = this->searchNode(comp);

        int key = HashforComputer(file);

        node->Files_btree->remove(key);
    }
}

int Login::searchFile(string file)
{
    if (loggedInUser)
    {
        int comp = HashforComputer(file) % (1 << bits);
        Node* node = this->searchNode(comp);

        int key = HashforComputer(file);
        btreenode* result = node->Files_btree->search(key);

        if (result)
        {
            std::cout << "Name " << result->filepath->name << " \n";
            std::cout << "path " << result->filepath->path << "\n";
            return 0;
        }
        return -1;
    }
    return -1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

btreenode::btreenode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    key = new int[2 * t - 1];
    filepath = new File[2 * t - 1];
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
        root->filepath[0] = f;
        //root->filepath[0].path = f.path;

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
            s->c[i]->insertnonfull(k, f);
            root = s;
        }
        else
            root->insertnonfull(k, f);

    }

}

void btreenode::insertnonfull(int k,File f)

{

    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && key[i] > k)

        {

            key[i + 1] = key[i];
            filepath[i + 1] = filepath[i];

            i--;

        }

        key[i + 1] = k;
        filepath[i + 1] = f;

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

        c[i + 1]->insertnonfull(k, f);

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
