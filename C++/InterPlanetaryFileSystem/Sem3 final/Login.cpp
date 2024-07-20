#include "Login.h"
#include"Hash.h"
#include "copypaste.h"


bool Login::authenticateUser(int nodeIndex)
{
    loggedInUser = dht->searchNode(nodeIndex);

    if (loggedInUser == nullptr)
    {
        return 0;
    }
    return true;
}

ComputerMachine* Login::getLoggedInUser() const
{
    return loggedInUser;
}

ComputerMachine* Login::searchNode(int targetIndex) const
{
    if (!loggedInUser) {
        std::cerr << "No user logged in.\n";
        return nullptr;
    }

    ComputerMachine* current = loggedInUser;
    int steps = 0; // Counter to track the number of nodes traversed
    bool endindex = 0;
    if (targetIndex > current->data)
    {
        endindex = 1;
    }
    
    ComputerMachine* starting = current;
    bool startingFlag = 0;
    std::cout << "Nodes traversed: ";
    std::cout << "Node " << current->data << " -> ";
    for (size_t i = 0; i < dht->getIdentifierBits(); i++) 
    {
        steps++;
        if (startingFlag && starting==current)
        {
            return current;
        }
        if (targetIndex == current->data)
        {
            // Found the node with the target index
            std::cout << "Node " << current->data << "\n";
            return current;
        }
        if (targetIndex < current->routingTable[0]->data)
        {
            current = current->routingTable[0];
            std::cout << "Node " << current->data << "\n";
            return current;
        }
        if (current->routingTable[i]->data < current->data && current->data < targetIndex && endindex)
        {
            // Move to the previous node
            if (i == 0)
            {
                current = current->routingTable[i];
                i = -1; // Reset the loop to start from the beginning
                std::cout << "Node " << current->data << " -> ";
                startingFlag = 1;
                if (current->data < targetIndex)
                {
                    return current;
                }
            }
            else
            {
                current = current->routingTable[i - 1];
                i = -1; // Reset the loop to start from the beginning
                startingFlag = 1;
                std::cout << "Node " << current->data << " -> ";
            }
        }
        else if (targetIndex < current->routingTable[i]->data)
        {
            // Move to the previous node
            current = current->routingTable[i - 1];
            i = -1; // Reset the loop to start from the beginning
            startingFlag = 1;
            std::cout << "Node " << current->data << " -> ";
        }
        else if (i == dht->getIdentifierBits() - 1)
        {
            current = current->routingTable[i];
            i = -1;
            startingFlag = 1;
            std::cout << "Node " << current->data << " -> ";
        }
    }

    // Print the last traversed node when the loop completes
    std::cout << "Node " << current->data << "\n";
    
    return current;
}

void Login::insertFile(File file)
{
    if (loggedInUser)
    {
        int comp = HashforComputer(file.name) % (1 << bits);
        ComputerMachine* node = this->searchNode(comp);
        comp = node->data;
        std::cout << "\n";
        int key = HashforComputer(file.name);

        //check for valide file

        string pathofsourfile = file.path + "\\" + file.name;
        string pathofdestfile = "Computer Files " + to_string(comp) + "\\" + file.name;

        if (isValidFilePath(pathofsourfile))
        {
            if (copyFile(pathofsourfile, pathofdestfile))
            {
                file.path = pathofdestfile;
                node->Files_btree->insert(key, file);

                std::cout << "File is inserted at Computer : " << comp << "\n";
                std::cout << "Key of the File              : " << key << "\n";
            }
            else
            {
                std::cout << "Failed to copy File\n";
            }
        }
        else
        {
            std::cout << "File path is not valid " << comp << "\n";
        }
    }
}

void Login::removeFile(string file)
{
    if (loggedInUser)
    {
        int comp = HashforComputer(file) % (1 << bits);
        ComputerMachine* node = this->searchNode(comp);
        comp = node->data;
        std::cout << "\n";

        int key = HashforComputer(file);

        btreenode* result = node->Files_btree->search(key);
        if (result != nullptr)
        {
            deleteFile(result->filepath->path);
            node->Files_btree->remove(key);

            std::cout << "File is removed at Computer : " << comp << "\n";
            std::cout << "Key of the File              : " << key << "\n";
        }
        else
        {
            std::cout << "File not Found\n";
        }
    }
}

int Login::searchFile(string file)
{
    if (loggedInUser)
    {
        int comp = HashforComputer(file) % (1 << bits);
        ComputerMachine* node = this->searchNode(comp);
        comp = node->data;
        std::cout << "\n";

        int key = HashforComputer(file);
        btreenode* result = node->Files_btree->search(key);

        if (result)
        {
            std::cout << "File is present at Computer : " << comp << "\n";
            std::cout << "Key of the File             : " << key << "\n";
            std::cout << "Name                        : " << result->filepath->name << " \n";
            std::cout << "path                        : " << result->filepath->path << "\n";
            return 0;
        }
        return -1;
    }
    return -1;
}

void Login::printBtree()
{
    if (loggedInUser)
    {
        loggedInUser->Files_btree->displayAllData();
    }
}
