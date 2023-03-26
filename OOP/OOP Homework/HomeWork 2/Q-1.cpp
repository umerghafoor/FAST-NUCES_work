#include <iostream>
using namespace std;

const int MAX_CUSTOMERS = 10;
const int MAX_RENTALS = 10;
int numCustomers = 0;
int numRentals = 0;

class customer
{
    int id;
    string name;
    string address;
    string phoneNo;
public:
    customer()
    {
        id = 0;
        name = "NULL";
        address = "NULL";
        phoneNo = "Null";
    }
    int getId() { return id; }
    string getName() { return name; }
    string getAddress() { return address; }
    string getPhone() { return phoneNo; }
    void setId(int id1) { id = id1; }
    void setName(string name) { this->name = name; }
    void setAddress(string address) { this->address = address; }
    void setPhone(string phone) { this->phoneNo = phone; }
};
class RentalItem 
{
private:
    int id;
    string title;
    string director;
    string status;
    int customer_id;
public:
    int getId() { return id; }
    string getTitle() { return title; }
    string getDirector() { return director; }
    string getStatus() { return status; }
    void setId(int id1) { id = id1; }
    void setTitle(string title1) { title = title1; }
    void setDirector(string d1) { director = d1; }
    void setStatus(string newStatus) { status = newStatus; }
    void setCustomerId(int id) { customer_id = id; }
    int getCustomerId() { return customer_id; }
};
class VideoSystem
{
private:
    customer customers[MAX_CUSTOMERS];
    RentalItem rentals[MAX_RENTALS];
public:
    void addCustomer(customer c)
    {
        customers[numCustomers++] = c;
     //   cout<< numCustomers<<customers[numCustomers].getId();
    }
    void addRental(RentalItem r)
    {
        rentals[numRentals++] = r;
    }
    bool hasOutstandingVideos(int id) {
        for (int i = 0; i < numRentals; i++) {
            if (rentals[i].getStatus() == "rented" && rentals[i].getId() == id) {
                return true;
            }
        }
        return false;
    } 
    int numRentalsRented() {
        int count = 0;
        for (int i = 0; i < numRentals; i++) {
            if (rentals[i].getStatus() == "rented") 
            {
                count++;
            }
        }
        return count;
    }
    customer findCustomer(int id) {
        for (int i = 0; i < MAX_CUSTOMERS; i++) 
        {
         //   cout << customers[i].getId();
            if (customers[i].getId() == id) 
            {
                return customers[i];
            }
        }
        return customer();
    }
    RentalItem findRental(int id) {
        for (int i = 0; i < numRentals; i++) {
            if (rentals[i].getId() == id) {
                return rentals[i];
            }
        }
        return RentalItem();
    }
    void rentItem(int customer_id, int rental_id) {
        customer customer = findCustomer(customer_id);
        RentalItem rental = findRental(rental_id);
    //    cout << customer.getId();
     //   cout << (customer.getId() != 0) << (rental.getId() != 0 )<<( rental.getStatus() == "available");
        if (customer.getId() != 0 && rental.getId() != 0 && rental.getStatus() == "available")
        {
            rental.setStatus("rented");
            cout << "Item rented to customer " << customer.getName() << endl;
        }
        else {
            cout << "Could not rent item." << endl;
        }
        for (int i = 0; i < numRentals; i++) {
            if (rentals[i].getId() == rental_id) {
                rentals[i].setStatus("rented");
                rentals[i].setCustomerId(customer_id);
            }
        }
    }
    void returnItem(int rental_id) {
        RentalItem rental = findRental(rental_id);
        if (rental.getId() != 0 && rental.getStatus() == "rented") {
            rental.setStatus("returned");
            cout << "Item returned." << endl;
        }
        else {
            cout << "Could not return item." << endl;
        }
    }
    void listRentalsCustomer(int customer_id) {
        cout << "Rentals for customer " << customer_id << ":" << endl;
        for (int i = 0; i < numRentals; i++) {
            if (rentals[i].getCustomerId() == customer_id) {
                cout << rentals[i].getTitle() << " (id " << rentals[i].getId() << ")" << endl;
            }
        }
    }
    customer findRentalCustomer(int rental_id) {
        RentalItem rental = findRental(rental_id);
        if (rental.getStatus() == "rented") {
            return findCustomer(rental.getCustomerId());
        }
        else {
            return customer();
        }
    }
};

int main()
{
    VideoSystem vs;

    int customerId, rentalId;
    customer c;
    RentalItem r;
    int id;
    string name, address, phone;
    string title, director;

    int choice = 1;
    while (choice != 7)
    {
        cout << "Welcome to the video rental system!" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. Add customer" << endl;
        cout << "2. Add rental item" << endl;
        cout << "3. Rent item" << endl;
        cout << "4. Return item" << endl;
        cout << "5. List rentals by customer" << endl;
        cout << "6. Find rental customer" << endl;
        cout << "7. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter customer ID: ";
            cin >> id;
            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter customer address: ";
            cin >> address;
            cout << "Enter customer phone number: ";
            cin >> phone;
            c.setId(id);
            c.setName(name);
            c.setAddress(address);
            c.setPhone(phone);
            vs.addCustomer(c);
            cout << "Customer added." << endl;
            break;
        case 2:
            cout << "Enter item ID: ";
            cin >> id;
            cout << "Enter item title: ";
            cin >> title;
            cout << "Enter item director: ";
            cin >> director;
            r.setId(id);
            r.setTitle(title);
            r.setDirector(director);
            r.setStatus("available");
            vs.addRental(r);
            cout << "Item added." << endl;
            break;
        case 3: {
            cout << "Enter customer ID: ";
            cin >> customerId;
            cout << "Enter rental item ID: ";
            cin >> rentalId;
            c = vs.findCustomer(customerId);
            r = vs.findRental(rentalId);
            if (c.getId() == -1)
            {
                cout << "Customer not found." << endl;
                break;
            }
            if (r.getId() == -1)
            {
                cout << "Rental item not found." << endl;
                break;
            }
            if (r.getStatus()[0] != 'a')
            {
                cout << "Item is not available for rent." << endl;
                break;
            }
            vs.rentItem(customerId, rentalId);
            cout << "Item rented." << endl;
            break;
        }
        case 4: {
            int rentalId;
            cout << "Enter rental item ID: ";
            cin >> rentalId;
            r = vs.findRental(rentalId);
            if (r.getId() == -1) {
                cout << "Rental item not found." << endl;
                break;
            }
         //   cout << r.getStatus();
            if (r.getStatus()[0] == 'a') {
                cout << "Item was not rented." << endl;
                break;
            }
            vs.returnItem(rentalId);
         //   cout << "Item returned." << endl;
            break;
        }
        case 5:
            int customerId;
            cout << "Enter customer ID: ";
            cin >> customerId;
            c = vs.findCustomer(customerId);
            if (c.getId() == -1) {
                cout << "Customer not found." << endl;
                break;
            }
            vs.listRentalsCustomer(customerId);
            break;
        case 6:
            cout << "Enter rental item ID: ";
            cin >> rentalId;
            r = vs.findRental(rentalId);
            if (r.getId() == -1) {
                cout << "Rental item not found." << endl;
                break;
            }
            c = vs.findRentalCustomer(rentalId);
            if (c.getId() == -1) {
                cout << "No customer found for rental item." << endl;
                break;
            }
            cout << "Customer ID: " << c.getId() << endl;
            cout << "Customer name: " << c.getName() << endl;
            cout << "Customer address: " << c.getAddress() << endl;
            cout << "Customer phone number: " << c.getPhone() << endl;
            break;
        case 7: 
            cout << "Goodbye!" << endl;
            break;
        default: 
            cout << "Invalid choice. Please select a valid option." << endl;
            break;
        }
        system("pause");
        system("cls");
    }

    return 0;
}