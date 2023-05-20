#include "Array.h"
#include <iostream>

using namespace std;

Array::Array()
{
    array = nullptr;
    this->size = 0;
}
Array::Array(int size)
{
    array = new int[size];
    this->size = size;
}
Array::Array(int* arr, int size)
{
    array = new int[size];
    for (int i = 0;i < size;i++)
    {
        array[i] = arr[i];
    }
    this->size = size;
}
Array::Array(const Array& otherArray)
{
    size = otherArray.size;
    array = new int[size];
    for (int i = 0; i < size; i++) 
    {
        array[i] = otherArray.array[i];
    }
}
int Array::operator[](int i) const
{
    return array[i];
}
Array Array::operator=(const Array otherArray)
{
    array = new int[otherArray.size];
    for (int i = 0;i < otherArray.size;i++)
    {
        array[i] = otherArray[i];
    }
    return *this;
}
Array Array::operator+(Array otherArray)
{
    Array result(size);
    if (otherArray.size < size)
    {
        for (int i = 0; i < otherArray.size; i++)
        {
            result.array[i] = array[i] + otherArray.array[i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            result.array[i] = array[i] + otherArray.array[i];
        }
    }
    return result;
}
Array Array::operator-(Array otherArray)
{
    Array result(size);
    if (otherArray.size < size)
    {
        for (int i = 0; i < otherArray.size; i++)
        {
            result.array[i] = array[i] - otherArray.array[i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            result.array[i] = array[i] - otherArray.array[i];
        }
    }
    return result;
}
void Array::operator++() 
{
    for (int i = 0; i < size; i++) 
    {
        array[i]++;
    }
}
Array& Array::operator--(int x)
{
    for (int i = 0; i < size; i++)
    {
        array[i]--;
    }
    return *this;
}
bool Array::operator==(const Array otherArray)
{
    if (size != otherArray.size)
    {
        return false;
    }
    for (int i = 0;i < size;i++)
    {
        if (array[i] != otherArray[i])
        {
            return false;
        }
    }
    return true;
}
bool Array::operator!()
{
    if (size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Array::operator+=(const Array& otherArray)
{
    if (otherArray.size < size)
    {
        for (int i = 0; i < otherArray.size; i++)
        {
            array[i] = array[i] + otherArray.array[i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = array[i] + otherArray.array[i];
        }
    }
}
void Array::operator-=(const Array& otherArray)
{
    if (otherArray.size < size)
    {
        for (int i = 0; i < otherArray.size; i++)
        {
            array[i] = array[i] - otherArray.array[i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            array[i] = array[i] - otherArray.array[i];
        }
    }
}
int Array::operator()(int idx, int val)
{
    if (idx < 0 || idx >= size)
    {
        return -1;
    }

    if (array[idx] != val) 
    {
        return -1;
    }
    for (int i = idx; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    size--;
    return 1;
}

istream& operator>>(istream& input, Array& arr) 
{
    int size = arr.size;
    for (int i = 0; i < size; i++) 
    {
        cout << "Enter " << i << " th element : ";
        input >> arr.array[i];
    }
    return input;
}
ostream& operator<<(ostream& output, const Array arr)
{
    int size = arr.size;
    output << "{";
    for (int i = 0; i < size; i++) 
    {
        output << arr[i];
        if (i != size - 1) 
        {
            output << ", ";
        }
    }
    output << "}";
    return output;
}
Array::~Array()
{
    delete[] array;
}
