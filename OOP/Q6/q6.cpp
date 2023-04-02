#include "Scheduler.h"
#include <iostream>
using namespace std;

int main()
{
    Circle circle;
    int x, y, r;
    int size;
    cout << "\tCreating Circle Array" << endl;
    cout << "Enter Size : ";cin >> size;
    Circle* circles = new Circle[size];
    cout << "\tArray of " << size << " circles created" << endl;
    for (int i = 0 ; i < size;i++)
    {
        cout << "\n\tEnter data of " << i << " Circle" << endl;
        cout << "Enter X      : ";cin >> x;
        cout << "Enter Y      : ";cin >> y;
        cout << "Enter Radius : ";cin >> r;
        circles[i].setCenter(x, y);
        circles[i].setRadius(r);
    }
    system("pause");
    system("cls");
    int choice = 1;
    while (choice != 0) {
        cout << "1 Print Area of Circles" << endl;
        cout << "2 Return Largest Circle" << endl;
        cout << "3 Check Overlaping" << endl;
        cout << "4 Check Overlaping (Array)" << endl;
        cout << "0 Print Area of Circles" << endl;
        cout << "Enter choice : ";cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\tArea ofCircles" << endl;
            for (int i = 0;i < size;i++) {
                cout << "Area of Circle" << i << " : " << circles[i].getArea() << endl;
            }
            break;
        case 2:
            cout << "\tLargest Circle" << endl;
            circle = circle.returnLargestCircle(circles, size);
            cout << "Coordinates of largest circle : ";
            circle.PrintCoordinate();
            break;
        case 3:
            cout << "\tCheck Overlaping" << endl;
            cout << "Index of First Circle  : ";cin >> x;
            cout << "Index of Second Circle : ";cin >> y;
            if (circle.overlapping(circles[x], circles[y]))
            {
                cout << "Circles are Overlaping" << endl;
            }
            else
            {
                cout << "Circles are Not Overlaping" << endl;
            }
            break;
        case 4:
            cout << "\tCheck Overlaping (Array)" << endl;
            Circle* overlappingCirclesArr = circle.overlappingCircles(circles, size);
            cout << "Coodinates of Over laping Circles" << endl;
            for (int i = 0; i < size; i++)
            {
                overlappingCirclesArr[i].PrintCoordinate();
            }
            break;
        }
        system("pause");
        system("cls");
    }
}