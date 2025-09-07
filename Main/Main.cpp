// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <array>
#include <iostream>
#include <list>
#include <random>
#include <ranges>
#include <vector>


#include "Matrix.h"
#include "Vector.h"

using namespace std;
using namespace Math;

void test()
{
    cout << "Code to test Matrix2\n";

    // ************************************************************************
    // Create an instance of the Matrix2 class.
    // This will contain a simple 2D 3x3 matrix.
    std::vector<double> simpleData{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
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
        if ((i + 1) % 10 == 0)
            cout << endl;
    }
    cout << endl;
}
void print(auto const rem, auto const& r)
{
    std::cout << rem << '{';
    for (char o[]{ 0,' ',0 }; auto const& e : r)
        std::cout << o << e, * o = ',';
    std::cout << "}\n";
}

void test2()
{
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(testData1);
    std::cout << "testVector 1: ";
    testVector1.PrintVector();

    const std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector2(testData2);
    std::cout << "testVector 2: ";
    testVector2.PrintVector();

    const auto testVector3{ testVector1 + testVector2 };
    std::cout << "testVector 3: ";
    testVector3.PrintVector();

    const auto testVector4{ testVector2 - testVector1 };
    std::cout << "testVector 4: ";
    testVector4.PrintVector();

    const auto testVector5{ testVector1 * 2.0 };
    std::cout << "testVector 5: ";
    testVector5.PrintVector();

    const auto testVector6{ 2.0 * testVector1 };
    std::cout << "testVector 6: ";
    testVector6.PrintVector();

    const auto dot1{ Vector<double>::Dot(testVector1, testVector2) };
    std::cout << "dot 1       : ";
    std::cout << dot1 << std::endl;

    const auto testVector7{ Vector<double>::Cross(testVector1, testVector2) };
    std::cout << "testVector 7: ";
    testVector7.PrintVector();

    const std::vector<double> testData8{ -1.0, 5.0, -3.2 };
    const Vector<double> testVector8(testData8);
    std::cout << "testVector 8: ";
    testVector8.PrintVector();

    const auto testVector9{ Vector<double>::Cross(testVector1, testVector8) };
    std::cout << "testVector 9: ";
    testVector9.PrintVector();

    const auto dot2{ Vector<double>::Dot(testVector1, testVector8) };
    std::cout << "dot 2       : ";
    std::cout << dot2 << std::endl;

    std::cout << "testVector 1 length: " << testVector1.Norm() << std::endl;
    std::cout << "testVector 2 length: " << testVector2.Norm() << std::endl;
    std::cout << "testVector 8 length: " << testVector8.Norm() << std::endl;

    const Vector<double> normalizedVector1{ testVector1.Normalized() };
    std::cout << "normalizedVector 1: ";
    normalizedVector1.PrintVector();
    const Vector<double> normalizedVector2{ testVector2.Normalized() };
    std::cout << "normalizedVector 2: ";
    normalizedVector2.PrintVector();
    const Vector<double> normalizedVector8{ testVector8.Normalized() };
    std::cout << "normalizedVector 8: ";
    normalizedVector8.PrintVector();

    Vector<double> testVector1Copy{ testVector1 };
    testVector1Copy.Normalize();
    std::cout << "normalizedVector 1 in place: ";
    testVector1Copy.PrintVector();

    std::vector<double> testDataM{ 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
    Matrix2<double> testMatrix(3, 3, std::move(testDataM));
    std::cout << "testMatrix: \n";
    testMatrix.PrintMatrix();

    Vector<double> matrixMult1{ testMatrix * testVector1Copy };
    std::cout << "matrixMult1: ";
    matrixMult1.PrintVector();
}

void test3()
{
    std::vector<double> simpleData1{ 1.0, 2.0, 3.0,
                                     1.0, 2.0, 3.0,
                                     1.0, 2.0, 3.0 };
    Matrix2<double> testMatrix1(3, 3, simpleData1);
    std::cout << "testMatrix 1: \n";
    testMatrix1.PrintMatrix();
    std::cout << std::format("testMatrix 1 is{} in row echelon form\n", (testMatrix1.IsRowEchelon() ? "" : " not"));
    std::cout << std::endl;

    std::vector<double> simpleData2{ 1.0, 2.0, 3.0,
                                     0.0, 2.0, 3.0,
                                     0.0, 0.0, 3.0 };
    Matrix2<double> testMatrix2(3, 3, simpleData2);
    std::cout << "testMatrix 2: \n";
    testMatrix2.PrintMatrix();
    std::cout << std::format("testMatrix 2 is{} in row echelon form\n", (testMatrix2.IsRowEchelon() ? "" : " not"));
    std::cout << std::endl;

    std::vector<double> simpleData3{ 1.0, 1.0, 2.0, 9.0,
                                     2.0, 4.0, -3.0, 1.0,
                                     3.0, 6.0, -5.0, 0.0 };
    Matrix2<double> testMatrix3(3, 4, simpleData3);
    std::cout << "testMatrix 3: \n";
    testMatrix3.PrintMatrix();
    std::cout << std::endl;

    Matrix2<double> testMatrix4{ testMatrix3.RowEchelon() };
    std::cout << "testMatrix 4: \n";
    testMatrix4.PrintMatrix();
    std::cout << std::endl;

    std::vector<double> simpleData5{ 0.0, 1.0, 2.0, 9.0,
                                     2.0, 0.0, -3.0, 1.0,
                                     3.0, 6.0, -5.0, 0.0 };
    Matrix2<double> testMatrix5(3, 4, simpleData5);
    std::cout << "testMatrix 5: \n";
    testMatrix5.PrintMatrix();
    std::cout << std::endl;

    Matrix2<double> testMatrix6{ testMatrix5.RowEchelon() };
    std::cout << "testMatrix 6: \n";
    testMatrix6.PrintMatrix();
    std::cout << std::endl;
    {
        std::vector<double> simpleData7{ 1, 3, -1, 13,
                                         4, -1, 1, 9,
                                         2, 4, 3, -6 };
        Matrix2<double> testMatrix8(3, 4, simpleData7);
        std::cout << "testMatrix 8: \n";
        testMatrix8.PrintMatrix();
        std::cout << std::endl;

        Matrix2<double> testMatrix9{ testMatrix8.RowEchelon() };
        std::cout << "testMatrix 9: \n";
        testMatrix9.PrintMatrix();
        std::cout << std::endl;

        Matrix2<double> testMatrix10; // 3x3 matrix
        Matrix2<double> testMatrix11; // 3x1 matrix
        testMatrix8.Separate(testMatrix10, testMatrix11, 3);
        std::cout << "testMatrix 10: \n";
        testMatrix10.PrintMatrix();
        std::cout << std::endl;
        std::cout << "testMatrix 11: \n";
        testMatrix11.PrintMatrix();
        std::cout << std::endl;
        Vector<double> testVector{ testMatrix11.AsVector() };
        std::cout << "testVector: \n";
        testVector.PrintVector();
        std::cout << std::endl;

        auto result{ linear_solve(testMatrix10, testVector) };

        std::cout << "result Vector: \n";
        result.PrintVector();
        std::cout << std::endl;

        std::cout << std::endl;
    }
    {
        std::vector<double> simpleData7{ 2, -1, 7, 2,
                                         4, 2, 2, 5,
                                         3, 1, 3, 1 };
        Matrix2<double> testMatrix8(3, 4, simpleData7);
        std::cout << "testMatrix 8: \n";
        testMatrix8.PrintMatrix();
        std::cout << std::endl;

        Matrix2<double> testMatrix9{ testMatrix8.RowEchelon() };
        std::cout << "testMatrix 9: \n";
        testMatrix9.PrintMatrix();
        std::cout << std::endl;

        Matrix2<double> testMatrix10; // 3x3 matrix
        Matrix2<double> testMatrix11; // 3x1 matrix
        testMatrix8.Separate(testMatrix10, testMatrix11, 3);
        std::cout << "testMatrix 10: \n";
        testMatrix10.PrintMatrix();
        std::cout << std::endl;
        std::cout << "testMatrix 11: \n";
        testMatrix11.PrintMatrix();
        std::cout << std::endl;
        Vector<double> testVector{ testMatrix11.AsVector() };
        std::cout << "testVector: \n";
        testVector.PrintVector();
        std::cout << std::endl;

        auto result{ linear_solve(testMatrix10, testVector) };

        std::cout << "result Vector: \n";
        result.PrintVector();
        std::cout << std::endl;

        std::cout << std::endl;
    }
    {
        std::vector<double> testData{ 1.0, 3.0, -1.0, 13.0,
                                        4.0, -1.0, 1.0, 9.0,
                                        2.0, 4.0, 3.0, -6.0 };
        Matrix2<double> testMatrix(3, 4, testData);

        std::vector<double> expectedData{ 1.0, 3.0, -1.0, 13.0,
                                          0.0, -13.0, 5.0, -43.0,
                                          0.0, 0.0, 4.231, -25.385 };
        Matrix2<double> expectedMatrix(3, 4, expectedData);

        Matrix2<double> rowEchelonMatrix{ testMatrix.RowEchelon() };
        rowEchelonMatrix.PrintMatrix();

    }
}

#include <string>
using namespace std;


void permute(vector<size_t>& arr, size_t l, size_t r) {
    if (l == r) {
        for (size_t c : arr) {
            cout << c << " ";
        }
        cout << endl;
    }
    else {
        for (size_t i = l; i <= r; i++) {
            swap(arr[l], arr[i]);          // swap current element
            permute(arr, l + 1, r);        // recurse
            swap(arr[l], arr[i]);          // backtrack
        }
    }
}
void test4()
{
    vector<size_t> elements = { 0, 1, 2, 3 };
    permute(elements, 0, elements.size() - 1);

}
void test5()
{
    std::random_device myRandomDevice;
    std::mt19937 myRandomGenerator(myRandomDevice());
    std::uniform_real_distribution<double> myDistribution(-25.0, 25.0);

    size_t numUnknowns{ 10 };

    std::vector<double> coefficientData;
    std::vector<double> unknownData;

    // Populate the coefficientData
    for (size_t i{ 0 }; i < (numUnknowns * numUnknowns); ++i)
    {
        double randomNumber{ myDistribution(myRandomGenerator) };
        coefficientData.push_back(randomNumber);
    }
    //cout << "A random coefficient matrix = \n";
    Matrix2<double> coefficientMatrix(numUnknowns, numUnknowns, coefficientData);
    //coefficientMatrix.PrintMatrix();
    //cout << endl;

    // And the random unknown values

    //cout << "And the random unknown values\n";
    for (size_t i{ 0 }; i < numUnknowns; ++i)
    {
        double randomNumber{ myDistribution(myRandomGenerator) };
        unknownData.push_back(randomNumber);
    }
    Vector<double> unknownVector(unknownData);
    //unknownVector.PrintVector();
    //cout << endl;

    //cout << "Compute the equation result =\n";
    Vector<double> systemResult{ coefficientMatrix * unknownVector };
    //systemResult.PrintVector();
    //cout << endl;

    //cout << "Attemt to solved the linear system...\n";
    Vector<double> compSolution{ linear_solve(coefficientMatrix, systemResult) };
    //systemResult.PrintVector();
    //cout << endl;

    //cout << "And compare the actual result with the computed solution...\n";
    Vector<double> errorVector{ unknownVector - compSolution };
    errorVector.PrintVector();
    cout << endl;


}

int main()
{
    //test();
    //test2();
    test3();
    //test4();
    //test5();
    return 0;
}

