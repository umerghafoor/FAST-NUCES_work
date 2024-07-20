#pragma once

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

void displayLoginMenu(Login& myComputer, RingDHT& ring)
{
    int choice;
    while (true) {
        std::cout << "\nLogin Menu:\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Display Logged-In User\n";
        std::cout << "3. Search for other computer\n";
        std::cout << "4. Insert File\n";
        std::cout << "5. Remove File\n";
        std::cout << "6. Search File\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int nodeIndex;
            std::string computerName;
            std::cout << "Enter the index of the node to log in: ";
            std::cin >> nodeIndex;
            std::cout << "Enter the name of the computer: ";
            std::cin >> computerName;
            myComputer.authenticateUser(nodeIndex, computerName);
            break;
        }
        case 2: {
            Node* loggedInUser = myComputer.getLoggedInUser();
            if (loggedInUser) {
                std::cout << "Logged-in user: Node " << loggedInUser->data << "\n";
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

                Node* targetNode = myComputer.searchNode(targetIndex);
                if (targetNode) {
                    std::cout << "Found target node: Node " << targetNode->data << "\n";
                }
                else 
                {
                    std::cout << "Target node not found.\n";
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
            int file;
            std::cout << "Enter file: ";
            std::cin >> file;
            myComputer.insertFile(file);
            break;
        }
        case 5:
        {
            int file;
            std::cout << "Enter file: ";
            std::cin >> file;
            myComputer.removeFile(file);
            break;
        }
        case 6: {
            int file;
            std::cout << "Enter file: ";
            std::cin >> file;
            std::cout << myComputer.searchFile(file);
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
