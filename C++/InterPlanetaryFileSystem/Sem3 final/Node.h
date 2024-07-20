#pragma once


#include"BTree.h"
#include"RoutningTable.h"
class ComputerMachine
{
public:
    int data;
    ComputerMachine* next;
    ComputerMachine* prev;
    vector<ComputerMachine*> routingTable;
    btree* Files_btree;

    ComputerMachine(int, int);
};

