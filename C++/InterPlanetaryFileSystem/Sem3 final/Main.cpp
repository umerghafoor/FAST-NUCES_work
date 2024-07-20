#include "BTree.h"
#include "BTreeNode.h"
#include "File.h"
#include "Login.h"
#include "Node.h"
#include "RingDHT.h"
#include<iostream>
using namespace std;

void displayLoginMenu(Login& myComputer, RingDHT& ring)
{
    int choice;
    while (true) {

        std::cout << "\n\n\n\n\n\n\n\n";
        system("pause");
        system("cls");
        std::cout << "\nLogin Menu:\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Display Logged-In User\n";
        std::cout << "3. Search for other computer\n";
        std::cout << "4. Insert File\n";
        std::cout << "5. Remove File\n";
        std::cout << "6. Search File\n";
        std::cout << "7. print all Files\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int nodeIndex;
            std::string computerName;
            std::cout << "Enter the index of the Computer to log in: ";
            std::cin >> nodeIndex;
            myComputer.authenticateUser(nodeIndex);
            break;
        }
        case 2: {
            ComputerMachine* loggedInUser = myComputer.getLoggedInUser();
            if (loggedInUser) {
                std::cout << "Logged-in user: Computer " << loggedInUser->data << "\n";
            }
            else
            {
                std::cout << "No user logged in.\n";
            }
            break;
        }
        case 3: {

            if (myComputer.getLoggedInUser())
            {
                int targetIndex;
                std::cout << "Enter the index of the target node to search: ";
                std::cin >> targetIndex;

                ComputerMachine* targetNode = myComputer.searchNode(targetIndex);
                if (targetNode) {
                    std::cout << "You are at Computer No. " << targetNode->data << "\n";
                }
                else
                {
                    std::cout << "Target Computer not found.\n";
                }
            }
            else
            {
                std::cout << "Please log in first.\n";
            }
            break;
        }
        case 4:
        {
            std::string name, path;

            std::cout << "Enter Name of the file: ";
            std::cin >> name;

            std::cout << "Enter Path of the file: ";
            std::cin >> path;

            File file(name, path);

            myComputer.insertFile(file);

            break;
        }
        case 5:
        {
            string file;
            std::cout << "Enter file: ";
            std::cin >> file;
            myComputer.removeFile(file);
            break;
        }
        case 6: {
            string file;
            std::cout << "Enter file: ";
            std::cin >> file;
            if (myComputer.searchFile(file) == -1)
            {
                std::cout << "File Not Found.\n";
            }
            break;
        }
        case 7:
        {
            myComputer.printBtree();
            break;
        }
        case 0:
            std::cout << "Returning to the main menu.\n";
            return;
        default:
            std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

void networkMenu(RingDHT& list, int numBits)
{
    int choice;
    do {

        std::cout << "\n\n\n\n\n\n\n\n";
        system("pause");
        system("cls");
        // Display menu options
        std::cout << "\nNetwork Menu:\n";
        std::cout << "1. Insert Node\n";
        std::cout << "2. Display Network\n";
        std::cout << "3. Delete Node\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Insert node
            int nodeId;
            std::cout << "Enter the Computer ID to insert: ";
            std::cin >> nodeId;
            if (nodeId < (1 << numBits))
            {
                list.insertInOrder(nodeId);
            }
            else
            {
                std::cout << "ID Not Valid\n";
            }
            break;
        }
        case 2:
            // Display network
            std::cout << "Computer \t [Routing Table] : " << std::endl;
            list.display();
            break;
        case 3:
        {
            // Delete node
            int nodeId;
            std::cout << "Enter the Computer ID to delete: ";
            std::cin >> nodeId;
            list.deleteNode(nodeId);
            break;
        }
        case 0:
            std::cout << "Exiting the network menu." << std::endl;
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);
}


int main() {

    int numBits;
    std::cout << "Enter the number of bits for the routing table: ";
    std::cin >> numBits;

    RingDHT list(numBits);
    Login comp(&list, numBits);

    int mainChoice;

    do {
        std::cout << "\n\n\n\n\n\n\n\n";
        system("pause");
        system("cls");
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Network Menu\n";
        std::cout << "2. Login Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            networkMenu(list, numBits);
            break;
        case 2:
            displayLoginMenu(comp, list);
            break;
        case 0:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (mainChoice != 3);
    return 0;
}
