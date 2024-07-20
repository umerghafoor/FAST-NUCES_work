#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;



class File
{
public:
	string path;
	string name;


	File(const string& name, const string& path)
		: path(path), name(name)
	{
	}

	File(const File& other) {
		path = other.path;
		name = other.name;
	}

	File& operator=(const File& other) 
	{
		path = other.path;
		name = other.name;

		return *this;
	}


	File() = default;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class btreenode
{
public:
	int* key;
	File* filepath;

	int t;
	btreenode** c;
	int n;
	bool leaf;


	btreenode(int _t, bool _leaf);
	void insertnonfull(int k, File f);

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
	void insert(int k,File f);
	btreenode* search(int k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}
	void remove(int k);
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Node
{
public:
    int data;
    Node* next;
    Node* prev;
    vector<Node*> routingTable;
    btree* Files_btree;

    Node(int value, int numBits);
};

class RingDHT
{
private:
    Node* head;
    int numBits; // Number of bits for the routing table

public:
    RingDHT(int bits);

    // Function to insert a node in order and update the routing table
    void insertInOrder(int value);

    // Function to update the routing table for a given node
    void updateRoutingTable(Node* node);

    // Helper function to find the successor for routing table entries
    Node* findSuccessor(Node* node, int index);
    // Function to delete a node with a specific value
    void deleteNode(int value);

    // Function to search for a node with a specific value
    Node* searchNode(int value);

    // Helper function to update routing tables for all nodes in the list
    void updateAllRoutingTables();


    // Function to display the double circular linked list with routing tables
    void display();

    int getIdentifierBits();

};

class Login {
private:
    RingDHT* dht;
    Node* loggedInUser;  // Pointer to the currently logged-in user
	int bits;

public:
	Login(RingDHT* dht, int bits) : dht(dht), loggedInUser(nullptr), bits(bits) {}
    bool authenticateUser(int);
    Node* getLoggedInUser() const;
    Node* searchNode(int) const;
    void insertFile(File);
    void removeFile(string);
    int searchFile(string);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
