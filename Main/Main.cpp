// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Matrix.h"

using namespace std;
using namespace Math;

void test()
{
    cout << "Code to test Matrix2\n";

    // ************************************************************************
    // Create an instance of the Matrix2 class.
    // This will contain a simple 2D 3x3 matrix.
    std::vector<double> simpleData { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> testMatrix(3, 4, simpleData);

    // Extract and print the elements of testMatrix
    cout << endl << "**************************\n";
    testMatrix.PrintMatrix();

    // ************************************************************************
    cout << endl << "**************************\n";
    cout << "Test element retrieval.\n";
    cout << "Element (0, 0) = " << testMatrix.At(0, 0) << endl;
    cout << "Element (1, 0) = " << testMatrix.At(1, 0) << endl;
    cout << "Element (2, 0) = " << testMatrix.At(2, 0) << endl;
    cout << "Element (0, 1) = " << testMatrix.At(0, 1) << endl;
    cout << "Element (1, 1) = " << testMatrix.At(1, 1) << endl;
    cout << "Element (2, 1) = " << testMatrix.At(2, 1) << endl;
    cout << "Element (0, 2) = " << testMatrix.At(0, 2) << endl;
    cout << "Element (1, 2) = " << testMatrix.At(1, 2) << endl;
    cout << "Element (2, 2) = " << testMatrix.At(2, 2) << endl;
    cout << "Element (0, 3) = " << testMatrix.At(0, 3) << endl;
    cout << "Element (1, 3) = " << testMatrix.At(1, 3) << endl;
    cout << "Element (2, 0) = " << testMatrix.At(2, 3) << endl;
    try
    {
        testMatrix.At(5, 5);
        cout << "Element (5, 5) = failed" << endl;
    }
    catch (const exception& e)
    {
        cout << "Element (5, 5) = exception(" << e.what() << ")" << endl;
    }

    cout << "Test m(2,2)\n";
    Matrix2<double> m(2, 2);
    m.PrintMatrix();

    // ************************************************************************
    // Test matrix multiplication.
    cout << endl << "\n**************************\n";
    std::vector<double> simpleData2{ 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> testMatrix2(4, 3, simpleData2);
    cout << "4x3 matrix (testMatrix2)\n";
    testMatrix2.PrintMatrix();
    cout << "Multiplication (testMatrix * testMatrix2) result:\n";
    Matrix2<double> multTest1{ testMatrix * testMatrix2 };
    multTest1.PrintMatrix();

    cout << endl << "\n**************************\n";
    cout << "testMatrix2 * testMatrix\n";
    Matrix2<double> multTest2{ testMatrix2 * testMatrix };
    multTest2.PrintMatrix();

    cout << endl << "\n**************************\n";
    cout << "Test multiplicaton of column vector by matrix.\n";
    std::vector<double> columnData{ 1.5, 2.5, 3.5 };
    std::vector<double> squareData{ 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
    Matrix2<double> testColumn(3, 1, columnData);
    Matrix2<double> squareMatrix(3, 3, squareData);
    cout << "Column vector = " << endl;
    testColumn.PrintMatrix();
    cout << "Square matrix = " << endl;
    squareMatrix.PrintMatrix();
    cout << "Column vector * SquareMatrix = " << endl;
    (testColumn * squareMatrix).PrintMatrix();
    cout << "SquareMatrix * Column vector =" << endl;
    (squareMatrix * testColumn).PrintMatrix();
    cout << "Square matrix + 1.0 = " << endl;
    Matrix2 squareMatrix2 = squareMatrix + 1.0;
    squareMatrix2.PrintMatrix();
    cout << "(Square matrix + 1.0) * Column vector = " << endl;
    (squareMatrix2 * testColumn).PrintMatrix();

    // ************************************************************************
    // Test equality operator.
    cout << endl << "\n**************************\n";
    cout << "Test equality operator." << endl;
    cout << "testMatrix == testMatrix2: " << (testMatrix == testMatrix2) << endl;
    cout << "testMatrix2 == testMatrix: " << (testMatrix2 == testMatrix) << endl;
    cout << "(Let testMatrix3 = testMatrix)\n";
    Matrix2<double> testMatrix3{ testMatrix };
    cout << "tetstMatrix == testMatrix3: " << (testMatrix == testMatrix3) << endl;
    cout << "tetstMatrix3 == testMatrix: " << (testMatrix3 == testMatrix) << endl;


    // ************************************************************************
    // Test matrix addition by scalar.
    cout << endl << "\n**************************\n";
    cout << "Test addition by scalar \n";
    cout << "testMatrix + 2.0 = \n";
    (testMatrix + 2.0).PrintMatrix();
    cout << endl;
    cout << "2.0 + testMatrix = \n";
    (2.0 + testMatrix).PrintMatrix();

    // ************************************************************************
    // Test matrix subtraction by scalar.
    cout << endl << "\n**************************\n";
    cout << "Test subtraction by scalar \n";
    cout << "testMatrix - 2.0 = \n";
    (testMatrix - 2.0).PrintMatrix();
    cout << endl;
    cout << "2.0 - testMatrix = \n";
    (2.0 - testMatrix).PrintMatrix();

    // ************************************************************************
    // Test matrix multiplication by scalar.
    cout << endl << "\n**************************\n";
    cout << "Test multiplication by scalar \n";
    cout << "testMatrix * 2.0 = \n";
    (testMatrix * 2.0).PrintMatrix();
    cout << endl;
    cout << "2.0 * testMatrix = \n";
    (2.0 * testMatrix).PrintMatrix();
}

template <typename T>
void PrintVector(std::vector<T> v)
{
    auto s{ v.size() };
    for (size_t i{ 0 }; i < s; ++i)
    {
        cout << v[i] << " ";
        if ((i+1) % 10 == 0)
            cout << endl;
    }
    cout << endl;
}

int main()
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 15.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    Matrix2<double> m2(m1);
    m1.PrintMatrix();
    if (m1.Inverse())
    {
        cout << "Matrix inversed!\n";
    }
    else
    {
        cout << "Matrix faled to inversed!\n";
    }
    m1.PrintMatrix();

    auto m{ m1 * m2 };

    cout << endl;

    m.PrintMatrix();
        
    //test();
    return 0;
}
