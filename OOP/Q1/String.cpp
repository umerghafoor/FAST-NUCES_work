#include "String.h"
#include <iostream>

using namespace std;

String::String()
{
    string = new char[1];
    string[0] = '\0';
}
String::String(char* str)
{
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    string = new char[len + 1];
    for (int i = 0; i < len; i++) {
        string[i] = str[i];
    }
    string[len] = '\0';

}
String::String(const String& otherString)
{
    int len = otherString.length();
    string = new char[len + 1];
    for (int i = 0; i < len; i++) 
    {
        string[i] = otherString.string[i];
    }
    string[len] = '\0';
}
String::String(int x)
{
    string = new char[x];
    for (int i = 0;i < x;i++)
    {
        string[i] = '\0';
    }
}
char String::operator[](int i) const
{
    return string[i];
}
String& String::operator+(String str)
{
    int newLength = length() + str.length();
    char* newString = new char[newLength + 1];
    int i = 0;
    for (; i < length(); i++) 
    {
        newString[i] = string[i];
    }
    for (int j = 0; j < str.length(); j++, i++) 
    {
        newString[i] = str.string[j];
    }
    newString[newLength] = '\0';
    String* result = new String(newString);
    delete[] newString;
    return *result;
}
String String::operator-(String substr)
{
    int substrLength = substr.length();
    int i, j;
    for (i = 0; i <= length() - substrLength; i++) 
    {
        for (j = 0; j < substrLength; j++) 
        {
            if (string[i + j] != substr.string[j]) 
            {
                break;
            }
        }
        if (j == substrLength) 
        {
            for (int k = i + substrLength; k <= length(); k++) 
            {
                string[k - substrLength] = string[k];
            }
            i = i - substrLength;
        }
    }
    String ret(string);
    return ret;
}
bool String::operator!()
{
    if (length() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
String& String::operator=(const String& otherString)
{
    for (int i = 0;i < otherString.length() ;i++)
    {
        string[i] = otherString[i];
    }
    string[otherString.length()] = '\0';
    String ret(string);
    return ret;
}
bool String::operator==(const String& otherString)
{
    bool isEqual=1;
    for (int i = 0;i < length();i++)
    {
        if (string[i] != otherString.string[i])
            isEqual = 0;
    }
    return isEqual;
}
int String::operator()(char search)
{
    int index = 0;
    for (index = 0;index < length();index++)
    {
        if (string[index] == search)
            break;
    }
    return index;
}
String String::operator*(int a)
{
    if (a <= 0) 
    {
        return String();
    }
    String result;
    for (int i = 0; i < a; i++) 
    {
        result = result + string;
    }
    return result;
}
int String::length() const
{
    int len = 0;
    while (string[len] != '\0')
    {
        len++;
    }
    return len;
}
ostream& operator<<(ostream& output, const String str)
{
    output << str.string;
    return output;
}
istream& operator>>(istream& input,String& str)
{
    char temp[100];
    input.ignore();
    input.getline(temp, 100);
    str = String(temp);
    return input;
}
String::~String()
{
    delete[] string;
}
