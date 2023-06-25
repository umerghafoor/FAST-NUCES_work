#include <iostream>
using namespace std;

class Vehicle 
{
protected:
    string type;
    int year;
public:
    string getType()
    {
        return type;
    }
    void setType(string newType) {
        type = newType;
    }
    int getYear() const {
        return year;
    }
    void setYear(int newYear) {
        year = newYear;
    }
};

class TwoWheeler {
public:
    int numOfWheels = 2;
};

class Car : public Vehicle
{
    string model;
public:
    string getModel()
    {
        return model;
    }
    void setModel(string newModel) {
        model = newModel;
    }
    void honk()
    {
        cout << "Honk of Car" << endl;
    }
    void drive() {
        cout << "MOdel of Car : " << model << endl;;
    }
};

class Motorcycle : public Vehicle, public TwoWheeler {
    string make;
public:
    string getMake()
    {
        return make;
    }
    void setMake(string newMake) 
    {
        make = newMake;
    }
    void honk()
    {
        cout << "Honk of Motercycle" << endl;
    }
    void drive() {
        cout << "Maker of motercycle : " << make << endl;
    }
};

class Truck : public Vehicle {
public:
    int towingCapacity;
    int getTowingCapacity()
    {
        return towingCapacity;
    }
    void setTowingCapacity(int newCapacity) 
    {
        towingCapacity = newCapacity;
    }
    void honk()
    {
        cout << "Honk of Turck" << endl;
    }
    void drive() {
        cout << "Towing Capacity : " << towingCapacity << endl;
    }
};


int main()
{

    Car myCar;
    string temp;
    cout << "Enter car model : ";
    cin >> temp;
    myCar.setModel(temp);

    Motorcycle myMotorcycle;
    cout << "Enter motorcycle make : ";
    cin >> temp;
    myCar.setType(temp);

    Truck myTruck;
    cout << "Enter truck towing capacity : ";
    cin >> myTruck.towingCapacity;

    cout << "Car Model : " << myCar.getModel() << endl;
    myCar.honk();
    myCar.drive();
    cout << endl;

    cout << "Motorcycle Make : " << myMotorcycle.getMake() << endl;
    myMotorcycle.honk();
    myMotorcycle.drive();
    cout << endl;

    cout << "Truck Towing Capacity : " << myTruck.getTowingCapacity() << endl;
    myTruck.honk();
    myTruck.drive();
    cout << endl;

    return 0;
}
