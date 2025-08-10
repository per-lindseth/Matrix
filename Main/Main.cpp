// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Matrix.h"

using namespace std;
using namespace Math;

template <typename T>
void PrintMatrix(Matrix2<T> matrix)
{
    size_t nRows = matrix.GetNumRows();
    size_t nCols = matrix.GetNumCols();
    for (size_t row = 0; row < nRows; ++row)
    {
        for (size_t col = 0; col < nCols; ++col)
        {
            cout << matrix.GetElement(row, col) << " ";
        }
        cout << endl;
    }
}


int main()
{
    cout << "Code to test Matrix2\n";

    // ************************************************************************
    // Create an instance of the Matrix2 class.
    // This will contain a simple 2D 3x3 matrix.
    double simpleData[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> testMatrix(3, 4, simpleData);

    // Extract and print the elements of testMatrix
    cout << endl << "**************************\n";
    PrintMatrix(testMatrix);

    // ************************************************************************
    cout << endl << "**************************\n";
    cout << "Test element retrieval.\n";
    cout << "Element (0, 0) = " << testMatrix.GetElement(0, 0) << endl;
    cout << "Element (1, 0) = " << testMatrix.GetElement(1, 0) << endl;
    cout << "Element (2, 0) = " << testMatrix.GetElement(2, 0) << endl;
    cout << "Element (0, 1) = " << testMatrix.GetElement(0, 1) << endl;
    cout << "Element (1, 1) = " << testMatrix.GetElement(1, 1) << endl;
    cout << "Element (2, 1) = " << testMatrix.GetElement(2, 1) << endl;
    cout << "Element (0, 2) = " << testMatrix.GetElement(0, 2) << endl;
    cout << "Element (1, 2) = " << testMatrix.GetElement(1, 2) << endl;
    cout << "Element (2, 2) = " << testMatrix.GetElement(2, 2) << endl;
    cout << "Element (0, 3) = " << testMatrix.GetElement(0, 3) << endl;
    cout << "Element (1, 3) = " << testMatrix.GetElement(1, 3) << endl;
    cout << "Element (2, 0) = " << testMatrix.GetElement(2, 3) << endl;
    try
    {
        testMatrix.GetElement(5, 5);
        cout << "Element (5, 5) = failed" << endl;
    }
    catch (const exception& e)
    {
        cout << "Element (5, 5) = exception(" << e.what() << ")" << endl;
    }

    // ************************************************************************
    // Test matrix multiplication.
    cout << endl << "\n**************************\n";
    double simpleData2[12] = { 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> testMatrix2(4, 3, simpleData2);
    cout << "4x3 matrix (testMatrix2)\n";
    PrintMatrix(testMatrix2);
    cout << "Multiplication (testMatrix * testMatrix2) result:\n";
    Matrix2<double> multTest1 = testMatrix * testMatrix2;
    PrintMatrix(multTest1);

    cout << endl << "\n**************************\n";
    cout << "testMatrix2 * testMatrix\n";
    Matrix2<double> multTest2 = testMatrix2 * testMatrix;
    PrintMatrix(multTest2);

    cout << endl << "\n**************************\n";
    cout << "Test multiplicaton of column vector by matrix.\n";
    double columnData[3] = { 1.5, 2.5, 3.5 };
    double squareData[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
    Matrix2<double> testColumn(3, 1, columnData);
    Matrix2<double> squareMatrix(3, 3, squareData);
    cout << "Column vector = " << endl;
    PrintMatrix(testColumn);
    cout << "Square matrix = " << endl;
    PrintMatrix(squareMatrix);
    cout << "Column vector * SquareMatrix = " << endl;
    PrintMatrix(testColumn * squareMatrix);
    cout << "SquareMatrix * Column vector =" << endl;
    PrintMatrix(squareMatrix * testColumn);
    cout << "Square matrix + 1.0 = " << endl;
    Matrix2 squareMatrix2 = squareMatrix + 1.0;
    PrintMatrix(squareMatrix2);
    cout << "(Square matrix + 1.0) * Column vector = " << endl;
    PrintMatrix(squareMatrix2 * testColumn);

    // ************************************************************************
    // Test equality operator.
    cout << endl << "\n**************************\n";
    cout << "Test equality operator." << endl;
    cout << "testMatrix == testMatrix2: " << (testMatrix == testMatrix2) << endl;
    cout << "testMatrix2 == testMatrix: " << (testMatrix2 == testMatrix) << endl;
    cout << "(Let testMatrix3 = testMatrix)\n";
    Matrix2<double> testMatrix3 = testMatrix;
    cout << "tetstMatrix == testMatrix3: " << (testMatrix == testMatrix3) << endl;
    cout << "tetstMatrix3 == testMatrix: " << (testMatrix3 == testMatrix) << endl;


    // ************************************************************************
    // Test matrix addition by scalar.
    cout << endl << "\n**************************\n";
    cout << "Test addition by scalar \n";
    cout << "testMatrix + 2.0 = \n";
    PrintMatrix(testMatrix + 2.0);
    cout << endl;
    cout << "2.0 + testMatrix = \n";
    PrintMatrix(2.0 + testMatrix);

    // ************************************************************************
    // Test matrix subtraction by scalar.
    cout << endl << "\n**************************\n";
    cout << "Test subtraction by scalar \n";
    cout << "testMatrix - 2.0 = \n";
    PrintMatrix(testMatrix - 2.0);
    cout << endl;
    cout << "2.0 - testMatrix = \n";
    PrintMatrix(2.0 - testMatrix);

    // ************************************************************************
    // Test matrix multiplication by scalar.
    cout << endl << "\n**************************\n";
    cout << "Test multiplication by scalar \n";
    cout << "testMatrix * 2.0 = \n";
    PrintMatrix(testMatrix * 2.0);
    cout << endl;
    cout << "2.0 * testMatrix = \n";
    PrintMatrix(2.0 * testMatrix);
}
