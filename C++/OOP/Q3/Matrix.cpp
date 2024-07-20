#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix()
{
    rows = 0;
    colm = 0;
    matrix = nullptr;
}
Matrix::Matrix(int rows, int colm)
{
    matrix = new float* [rows];
    for (int i = 0; i < rows; i++) 
    {
        matrix[i] = new float[colm];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colm; j++)
        {
            matrix[i][j] = 0;
        }
    }
    this->rows = rows;
    this->colm = colm;
}
Matrix::Matrix(const Matrix& otherMatrix)
{
    this->rows = otherMatrix.rows;
    this->colm = otherMatrix.colm;
    this->matrix = new float* [rows];
    for (int i = 0; i < rows; i++) 
    {
        this->matrix[i] = new float[colm];
    }
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < colm; j++) 
        {
            this->matrix[i][j] = otherMatrix.matrix[i][j];
        }
    }
}
void Matrix::operator()(int i, int j, float val)
{
    matrix[i][j] = val;
}
Matrix& Matrix::operator=(const Matrix& otherMatrix)
{
    if (rows == otherMatrix.rows && colm == otherMatrix.colm)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < colm; j++)
            {
                matrix[i][j] = otherMatrix.matrix[i][j];
            }
        }
    }
    else
    {
        cout << "Order is not Same" << endl;
    }
    return *this;
}
bool Matrix::operator==(const Matrix& otherMatrix)
{
    if (rows != otherMatrix.rows || colm != otherMatrix.colm)
    {
        return false;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colm; j++)
        {
            if (matrix[i][j] == otherMatrix.matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
Matrix Matrix::operator+(const Matrix& otherMatrix)
{
    if (rows != otherMatrix.rows || colm != otherMatrix.colm) 
    {
        cout << "Order is not same" << endl;
        Matrix empty(0, 0);
        return empty;
    }
    Matrix result(rows, colm);
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < colm; j++) 
        {
            result.matrix[i][j] = matrix[i][j] + otherMatrix.matrix[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& otherMatrix)
{
    if (rows != otherMatrix.rows || colm != otherMatrix.colm)
    {
        cout << "Order is not same" << endl;
        Matrix empty(0, 0);
        return empty;
    }
    Matrix result(rows, colm);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colm; j++)
        {
            result.matrix[i][j] = matrix[i][j] - otherMatrix.matrix[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& otherMatrix)
{
    float sum;
    if (colm != otherMatrix.rows) 
    {
        cout << "Matrices cannot be multiplied." << endl;
        Matrix empty(0, 0);
        return empty;
    }
    Matrix result(rows, otherMatrix.colm);
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < otherMatrix.colm; j++) 
        {
            sum = 0;
            for (int k = 0; k < colm; k++)
            {
                sum += matrix[i][k] * otherMatrix.matrix[k][j];
            }
            result(i, j, sum);
        }
    }
    return result;
}
Matrix& Matrix::operator++(int)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0;j < colm;j++)
        {
            matrix[i][j]++;
        }
    }
    return *this;
}
void Matrix::operator+=(const Matrix& otherMatrix)
{
    if (rows != otherMatrix.rows || colm != otherMatrix.colm)
    {
        cout << "Order is not same" << endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colm; j++)
        {
            matrix[i][j] += otherMatrix.matrix[i][j];
        }
    }
}
void Matrix::operator-=(const Matrix& otherMatrix)
{
    if (rows != otherMatrix.rows || colm != otherMatrix.colm)
    {
        cout << "Order is not same" << endl;
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < colm; j++)
        {
            matrix[i][j] -= otherMatrix.matrix[i][j];
        }
    }
}
istream& operator>>(istream& input, Matrix& matrix)
{
 //   cout << "Working"<< matrix.rows;
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.colm; j++)
        {
            cout << "Enter Element [" << i << "],[" << j << "] : ";
            input >> matrix.matrix[i][j];
        }
        cout << endl;
    }
    return input;
}
ostream& operator<<(ostream& output, const Matrix matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.colm; j++)
        {
            output << matrix.matrix[i][j] << '\t';
        }
        output << endl;
    }
    return output;
}
Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}