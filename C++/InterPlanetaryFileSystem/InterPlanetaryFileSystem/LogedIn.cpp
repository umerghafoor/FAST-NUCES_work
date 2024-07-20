#include "LogedIn.h"
//#include "RingDHT.h"

bool Login::authenticateUser(int nodeIndex, const std::string& computerName)
{
    Node* userNode = dht->searchNode(nodeIndex);
    if (userNode == nullptr)
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

    std::cout << "Nodes traversed: ";
    std::cout << "Node " << current->data << " -> ";
    for (size_t i = 0; i < dht->getIdentifierBits(); i++) {
        steps++;

        if (targetIndex == current->routingTable[i]->data) {
            // Found the node with the target index
            std::cout << "Node " << current->data << " -> ";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }
        if (targetIndex < current->routingTable[0]->data)
        {
            current = current->routingTable[0];
            std::cout << "Node " << current->data << " -> ";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }

        //std::cout << "(" << i << ',' << current->fingerTable[i]->data << ')';
        if (targetIndex < current->routingTable[i]->data)
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

void Login::insertFile(int file)
{
    if (loggedInUser)
    {
        //   loggedInUser->computer->insert(file);
    }
}

void Login::removeFile(int file)
{
    if (loggedInUser)
    {
        //   loggedInUser->computer->remove(file);
    }
}

int Login::searchFile(int file)
{
    if (loggedInUser)
    {
        // return loggedInUser->computer->Search(file);
    }
    return -1;
}
