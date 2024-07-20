#include "Matrix.h" 
#include <iostream>

using namespace std;

int main()
{
    int rows, colm;
    cout << "Enter dimensions of matrix 1 (rows cols)\n";
    cin >> rows >> colm;
    Matrix matrix1(rows, colm);
    
    cout << "Enter dimensions of matrix 2 (rows cols)\n";
    cin >> rows >> colm;
    Matrix matrix2(rows, colm);
    

	int choice = 1;
	system("cls");
	while (choice != 0)
	{
        cout << "1  Add matrices" << endl;
        cout << "2  Subtract matrices" << endl;
        cout << "3  Multiply matrices" << endl;
        cout << "4  Increment matrix" << endl;
        cout << "5  Add matrix to matrix1 using += operator" << endl;
        cout << "6  Subtract matrix from matrix1 using -= operator" << endl;
        cout << "7  Check if two matrices are equal" << endl;
        cout << "8  Print matrices" << endl;
        cout << "9  Enter matrices" << endl;
        cout << "10 Start Over" << endl;
        cout << "0  Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\tResult of addition is " << endl;
            cout << matrix1 + matrix2;
            break;
        case 2:
            cout << "\tResult of subtraction is " << endl;
            cout << matrix1 - matrix2;
            break;
        case 3:
            cout << "\tResult of multiplication is " << endl;
            cout << matrix1 * matrix2;
            break;
        case 4:
            matrix1++;
            cout << "\tMatrix 1 after increment " << endl;
            cout << matrix1;
            break;
        case 5:
            matrix1 += matrix2;
            cout << "\tMatrix 1 after adding matrix 2 " << endl;
            cout << matrix1;
            break;
        case 6:
            matrix1 -= matrix2;
            cout << "\tMatrix 1 after subtracting matrix 2 " << endl;
            cout << matrix1;
            break;
        case 7:
            if (matrix1 == matrix2) {
                cout << "Matrices are equal." << endl;
            }
            else {
                cout << "Matrices are not equal." << endl;
            }
            break;
        case 8:
            cout << "\tMatrix 1 is: " << endl;
            cout << matrix1;
            cout << "\tMatrix 2 is: " << endl;
            cout << matrix2;
            break;
        case 9:
            cout << "Enter matrix 1: " << endl;
            cin >> matrix1;
            cout << "Enter matrix 2: " << endl;
            cin >> matrix2;
            break;
        case 10:
            system("cls");
            main();
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
		system("pause");
		system("cls");
	}
}
