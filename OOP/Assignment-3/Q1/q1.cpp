#include "String.h" 
#include <iostream>

using namespace std;

int main()
{
    char name[] = "John Doe";
    String myString(name);

    //displaying the length of the string object
    cout << "Length of myString: " << myString.length() << endl;

    //creating another string object and initializing it with an integer
    String numString(123);

    //concatenating the two string objects using the + operator
    String result = myString + numString;

    //displaying the concatenated string
    result.Display();

    //checking if the string is empty using the ! operator
    if (!result) {
        cout << "String is empty" << endl;
    }

    //finding the index of a character in the string using the () operator
    int index = result('e');
    cout << "Index of 'e': " << index << endl;

    String minus('Do');

    //replacing a substring in the string using the - operator
    String newString = result - minus;
    newString.Display();

    //multiplying the string object using the * operator
    String multipliedString = result * 3;
    multipliedString.Display();

    //accessing the characters of the string using the [] operator
    for (int i = 0; i < multipliedString.length(); i++) {
        cout << multipliedString[i] << " ";
    }
    cout << endl;

    return 0;
}
