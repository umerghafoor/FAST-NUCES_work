#include"Class.h"




//////////////////////////////////////////////////////////////////////

int RingDHT::getSize()
{
	return size;
}

int RingDHT::getIdentifierBits()
{
	return identifierBits;
}

//void RingDHT::initializeRing()
//{
//    if (identifierBits <= 0) 
//    {
//        std::cerr << "Invalid number of bits." << std::endl;
//        return;
//    }
//    head = new Node(0, identifierBits, "");
//    Node* current = head;
//
//    for (int i = 1; i < size; ++i) {
//        current->next = new Node(i, identifierBits, "");
//        current->next->prev = current;
//        current = current->next;
//    }
//
//    // Close the ring
//    current->next = head;
//    head->prev = current;
//}

void RingDHT::displayRing() const
{
    if (!head) {
        std::cerr << "Ring is not initialized." << std::endl;
        return;
    }

    Node* current = head;
    do {
        if (current->state) {
            std::cout << "Node " << current->data << " (Computer: " << current->computer->name
                << ", State: " << current->state << "): ";

            for (int i = 0; i < identifierBits; ++i) {
                if (current->fingerTable[i]) {
                    std::cout << current->fingerTable[i]->data << " ";
                }
                else {
                    // Handle the case where the fingerTable entry is not valid
                    std::cout << "N/A ";
                }
            }

            std::cout << std::endl;
        }
        current = current->next;
    } while (current != head);
}

Node* RingDHT::findNode(int index) const
{
    Node* current = head;
    do {
        if (current->data == index) {
            return current;
        }
        current = current->next;
    } while (current != head);
    return nullptr; // Node not found or not active
}

void RingDHT::initializeFingerTables() {
    Node* current = head;
    do
    {
        for (int i = 0; i < identifierBits; ++i)
        {
            int fingerIndex = (current->data + (1 << i)) % size;
            Node* temp = findNextNode(fingerIndex);
            while (temp->state == 0)
            {
                temp = temp->next;
                if (temp == current)
                {
                    break;
                }
            }
            current->fingerTable[i] = temp;
        }
        current = current->next;
    } while (current != head);

}

Node* RingDHT::findNextNode(int index) const
{
    Node* current = head;
    int originalIndex = current->data;

    do {
        if (current->data == index) {
            return current;
        }
        current = current->next;
    } while (current->data != originalIndex);

    return nullptr;  // Node not found or not active
}

void RingDHT::addComputerToNode(int nodeIndex, const std::string& computerName)
{
    Node* targetNode = findNode(nodeIndex);
    if (targetNode) {
        targetNode->computer->name = computerName;
        targetNode->state = true;
        updateFingerTables();
    }
    else {
        std::cerr << "Node not found." << std::endl;
    }
}

void RingDHT::deleteComputerFromNode(int nodeIndex)
{
    Node* targetNode = findNode(nodeIndex);
    if (targetNode) {
        targetNode->computer->name = "";
        targetNode->state = false;
        updateFingerTables();
    }
    else {
        std::cerr << "Node not found." << std::endl;
    }
}

void RingDHT::updateFingerTables()
{
    // Update finger tables for all nodes
    initializeFingerTables();
}

bool Login::authenticateUser(int nodeIndex, const std::string& computerName)
{
    Node* userNode = dht->findNode(nodeIndex);
    if (userNode && userNode->computer->name == computerName) {
        std::cout << "Login successful. Welcome, " << computerName << "!\n";
        loggedInUser = userNode;  // Store the pointer to the logged-in user
        return true;
    }
    else {
        std::cout << "Login failed. Invalid credentials.\n";
        loggedInUser = nullptr;  // Clear the logged-in user pointer
        return false;
    }
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
    std::cout << "Node " << current->data << " (" << current->computer->name << ") -> ";
    for (size_t i = 0; i < dht->getIdentifierBits(); i++) {
        steps++;

        if (targetIndex == current->fingerTable[i]->data) {
            // Found the node with the target index
            std::cout << "Node " << current->data << " (" << current->computer->name << ") -> ";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }
        if (targetIndex < current->fingerTable[0]->data)
        {
            current = current->fingerTable[0];
            std::cout << "Node " << current->data << " (" << current->computer->name << ") -> ";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }

        //std::cout << "(" << i << ',' << current->fingerTable[i]->data << ')';
        if (targetIndex < current->fingerTable[i]->data)
        {
            // Move to the previous node
            current = current->fingerTable[i - 1];
            i = -1; // Reset the loop to start from the beginning
            std::cout << "Node " << current->data << " (" << current->computer->name << ") -> ";
        }
        else if (i == dht->getIdentifierBits() - 1)
        {
            current = current->fingerTable[i];
            i = -1;
            std::cout << "Node " << current->data << " (" << current->computer->name << ") -> ";
        }
    }

    // Print the last traversed node when the loop completes
    std::cout << "Node " << current->data << " (" << current->computer->name << ")\n";
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
