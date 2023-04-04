#include "Vehicle.h"
#include <iostream>
#include <vector>
using namespace std;
const int noOfVehicle = 10;
Vehicle::Vehicle()
{
    registrationNumber[0] = '\0';
    make[0] = '\0';
    yearOfManufacture = -1;
    currentValue = 0.0;
}
Vehicle::Vehicle(char* str)
{
    strcpy_s(registrationNumber, str);
    make[0] = '\0';
    yearOfManufacture = -1;
    currentValue = 0;
}
Vehicle::Vehicle(double value) 
{
    registrationNumber[0] = '\0';
    make[0] = '\0';
    yearOfManufacture = -1;
    currentValue = value;
}
Vehicle::Vehicle(const Vehicle& other) 
{
    strcpy_s(registrationNumber, other.registrationNumber);
    strcpy_s(make, other.make);
    yearOfManufacture = other.yearOfManufacture;
    currentValue = other.currentValue;
}

void Vehicle::setRegistrationNumber(char* regNumber) 
{
    strcpy_s(registrationNumber, regNumber);
}
void Vehicle::setMake(char* carMake) 
{
    strcpy_s(make, carMake);
}
void Vehicle::setYearOfManufacture(int year) 
{
    yearOfManufacture = year;
}
void Vehicle::setCurrentValue(double value) 
{
    currentValue = value;
}
const char* Vehicle::getRegistrationNumber() const 
{
    return registrationNumber;
}
const char* Vehicle::getMake() const {
    return make;
}
int Vehicle::getYearOfManufacture() const {
    return yearOfManufacture;
}
double Vehicle::getCurrentValue() const {
    return currentValue;
}

void Vehicle::addVehicle(Vehicle arr[], int &index)
{
    Vehicle v;
    cout << "Enter registration number : ";
    cin >> v.registrationNumber;
    cout << "Enter make                : ";
    cin >> v.make;
    cout << "Enter year of manufacture : ";
    cin >> v.yearOfManufacture;
    cout << "Enter current value       : ";
    cin >> v.currentValue;
    arr[index] = v;
    index++;
}
int Vehicle::ageOfVehicle(int currentYear)
{
    return currentYear - yearOfManufacture;
}
void Vehicle::getVehicleDetails() const 
{
    cout <<registrationNumber<<'\t' << make << '\t' << yearOfManufacture <<'\t' << currentValue << endl;
}
void Vehicle::getVehicleDetailsAtIndex(Vehicle arr[], int index)
{
    if (index>=0 && arr[index].getYearOfManufacture() >= 0)
    {
        cout <<arr[index].registrationNumber << '\t' << arr[index].make << '\t' << arr[index].yearOfManufacture << '\t' << arr[index].currentValue << endl;
    }
    else {
        cout << "Invalid Index" << endl;
    }
}
bool Vehicle::isMatching(Vehicle v)
{
    if (strcmp(v.getRegistrationNumber(), registrationNumber) != 0)
    {
        return false;
    }
    else if (strcmp(v.getMake(), make) != 0)
    {
        return false;
    }
    else if (v.getYearOfManufacture() != yearOfManufacture)
    {
        return false;
    }
    else if (v.getCurrentValue() != currentValue)
    {
        return false;
    }
    else
        return true;
}
Vehicle* Vehicle::returnByMake(Vehicle arr[], char* make, int& size)
{
    vector<Vehicle> vehiclesByMakeT;
    for (int i = 0; i < noOfVehicle; i++)
    {
        if (strcmp(arr[i].getMake(), make) == 0)
        {
            vehiclesByMakeT.push_back(arr[i]);
        }
    }
    size = vehiclesByMakeT.size();
    Vehicle* vehiclesByMake = new Vehicle[size];
    for (int i = 0; i < size; i++) {
        vehiclesByMake[i] = vehiclesByMakeT[i];
    }
    return vehiclesByMake;
}

Vehicle* Vehicle::returnByValue(Vehicle arr[], double value, int& size)
{
    vector<Vehicle> vehiclesByMakeT;
    for (int i = 0; i < noOfVehicle; i++)
    {
        if (arr[i].getCurrentValue() == value)
        {
            vehiclesByMakeT.push_back(arr[i]);
        }
    }
    size = vehiclesByMakeT.size();
    Vehicle* vehiclesByMake = new Vehicle[size];
    for (int i = 0; i < size; i++) {
        vehiclesByMake[i] = vehiclesByMakeT[i];
    }
    return vehiclesByMake;
}
Vehicle* Vehicle::returnByYear(Vehicle arr[], int year, int& size)
{
    vector<Vehicle> vehiclesByMakeT;
    for (int i = 0; i < noOfVehicle; i++)
    {
        if (arr[i].getYearOfManufacture() == year)
        {
            vehiclesByMakeT.push_back(arr[i]);
        }
    }
    size = vehiclesByMakeT.size();
    Vehicle* vehiclesByMake = new Vehicle[size];
    for (int i = 0; i < size; i++) {
        vehiclesByMake[i] = vehiclesByMakeT[i];
    }
    return vehiclesByMake;
}
void Vehicle::vehicleSold(Vehicle arr[], int index)
{
    arr[index].registrationNumber[0] = '\0';
    arr[index].make[0] = '\0';
    arr[index].yearOfManufacture = -1;
    arr[index].currentValue = 0.0;
}

Vehicle::~Vehicle()
{

}