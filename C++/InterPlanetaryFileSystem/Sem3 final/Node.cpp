#include "Node.h"


ComputerMachine::ComputerMachine(int value, int numBits) : data(value), next(nullptr), prev(nullptr) {
    this->Files_btree = new btree(numBits);
    for (int i = 0; i < numBits; ++i) {
        int entry = (value + (1 << i)) % (1 << numBits);
        routingTable.push_back(nullptr); 
    }
}
