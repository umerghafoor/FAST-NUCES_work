#pragma once
#include<iostream>
#include<string>
#include"BTreeClass.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
class Computer {
public:
    std::string name;
    //BTree* tree;

    
    Computer(const std::string& computerName,int btreeSize) : name(computerName) 
    {
      //  tree = new BTree(btreeSize);
    }

    //void insert(int key)
    //{
    //    tree->insert(key);
    //}
    //void remove(int key)
    //{
    //    tree->remove(key);
    //}
    //int Search(int key)
    //{
    //    BTreeNode* node = tree->search(key);
    //    if(node)
    //        return node->getFile(key);
    //    return -1;
    //}


    Computer() = default;
};

class Node {
public:
    int data;
    bool state;
    Node* next;
    Node* prev;
    Node** fingerTable;
    Computer *computer;

    Node() : data(-1), next(nullptr), prev(nullptr), fingerTable(nullptr), state(false), computer(nullptr) {}
    Node(int value, int bits, const std::string& computerName)
        : data(value), next(nullptr), prev(nullptr), state(false)
    {
        computer = new Computer(computerName, bits);
        fingerTable = new Node * [bits];
        for (int i = 0; i < bits; ++i)
        {
            fingerTable[i] = nullptr;
        }
    }

    ~Node() {
        delete[] fingerTable;
    }
};

class RingDHT {
private:
    int identifierBits;
    int size;
    Node* head;
    Computer loggedInComputer;

public:
    RingDHT(int bits) : identifierBits(bits), size(1 << bits) {
        head = nullptr;
        initializeFingerTables();
    }

    int getSize();
    int getIdentifierBits();
    //void initializeRing();
    void displayRing() const;
    Node* findNode(int) const;
    void initializeFingerTables();
    Node* findNextNode(int) const;
    void addComputerToNode(int, const std::string&);
    void deleteComputerFromNode(int);
    void updateFingerTables();

    ~RingDHT() {
        if (head) {
            Node* current = head;
            Node* temp;
            do {
                temp = current->next;
                delete current;
                current = temp;
            } while (current != head);
        }
    }
};

class Login {
private:
    RingDHT* dht;
    Node* loggedInUser;  // Pointer to the currently logged-in user

public:
    Login(RingDHT* dht) : dht(dht), loggedInUser(nullptr) {}
    bool authenticateUser(int, const std::string&);
    Node* getLoggedInUser() const;
    Node* searchNode(int) const;
    void insertFile(int file);
    void removeFile(int file);
    int searchFile(int file);
};