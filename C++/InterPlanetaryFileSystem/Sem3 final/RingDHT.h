#pragma once
#include"Node.h"
#include<iostream>
using namespace std;

class RingDHT
{
private:
    ComputerMachine* head;
    int numBits; // Number of bits for the routing table

public:
    RingDHT(int);

    // Function to insert a node in order and update the routing table
    void insertInOrder(int);

    // Function to update the routing table for a given node
    void updateRoutingTable(ComputerMachine*);

    // Helper function to find the successor for routing table entries
    ComputerMachine* findSuccessor(ComputerMachine*, int);
    // Function to delete a node with a specific value
    void deleteNode(int);

    // Function to search for a node with a specific value
    ComputerMachine* searchNode(int);

    // Helper function to update routing tables for all nodes in the list
    void updateAllRoutingTables();


    // Function to display the double circular linked list with routing tables
    void display();

    int getIdentifierBits();

};