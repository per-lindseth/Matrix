#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>
#include <fstream>
#include "../Main/Matrix.h"

using namespace std;

int main()
{
    // Define the filename of the file containing the ground truth data.
    string fileName = "C:\\Repos\\Matrix\\PythonCode\\test.csv";

    // Open the file
    ifstream input(fileName);

    // If the file opened successfully the do stuff.
    if (input.is_open())
    {
        // The file has one header line, contaiong the number of rows and columns of each matrix
        string currentLine;
        getline(input, currentLine);

        // This line is in the format "# n", where n is the number we want, so we need to split the
        // string around the position of the space.
        size_t delimiterPosition{ currentLine.find(" ") };
        string nRowString = currentLine.substr(delimiterPosition, currentLine.length());

        // Once we have the part of the string we are interested in, we convert it to an integer
        // and use that value as the number of rows and columns.
        size_t nRows(atoi(nRowString.c_str()));

        // Read the rest of the file and parse each line as we go.
        stringstream ss;
        double currentNumber{};

        // currentRow will hold all the elements that make up the row we have just read,
        // which will correspond to a single line from the CSV file.
        vector<double> currentRow{};

        // currentMatrixData will hold all of the data from nRows lines extracted from
        // the file.
        vector<double> currentMatrixData;

        // Create a vector Matrix2 som that we can hold the matrices that result
        // in any failed tests.
        vector<Math::Matrix2<double>> failedTests;

        size_t totalRows{ 0 };
        size_t rowCount{ 0 };
        size_t numSuccess{ 0 };
        size_t numFail{ 0 };

        // Loop until we reach the end of the file
        while (!input.eof())
        {
            // Get the current line from the CSV file.
            getline(input, currentLine);

            // Convert to a string stream object
            ss << currentLine;

            // Loop through the string stream and extract the number around the commas.
            while (ss >> currentNumber)
            {
                currentRow.push_back(currentNumber);
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }

            // Clear the string stream ready for the next loop, since we don't need it any more.
            // /currentRwo now contains all the numbers we need).
            ss.clear();

            // Concatenate the contents of the currentRow into currentMatrixData, which will be one
            // large, single-dimension array.
            currentMatrixData.insert(currentMatrixData.end(), currentRow.begin(), currentRow.end());

            // Clear currentRow ready for the next loop.
            currentRow.clear();

            // Increment the rowCount.
            rowCount++;

            // If we have read 5 rows, then we stop and form this data into a Matrix2 object with
            // dimension of 5 rows and 10 columns.
            if (rowCount > 4)
            {
                // Restet the row count
                rowCount = 0;

                // Create the Matrix2 object and store the matrix data
                Math::Matrix2<double> newMatrix(5, 10, move(currentMatrixData));

                // Prepare two matrices to contain the left and right halves of this matrix.
                // (Each of these will be square, with dimensions of 5x5).
                Math::Matrix2<double> leftMatrix;
                Math::Matrix2<double> rightMatrix;

                // Separate the matrix
                newMatrix.Separate(leftMatrix, rightMatrix, 5);

                // The right hand side now contains the ground-truth inverse loaded from the
                // CVS file, whilst the left hand side is the origibal matrix. Therfore, we
                // want to invert the left hand side ourselves and then compare the result
                // with the right hand side. 
                leftMatrix.Inverse();

                // Note the use of 'Compare' function with a specified tolerance of 1e-9.
                if (leftMatrix.Compare(rightMatrix, 1.e-8))
                {
                    cout << "Invert test suceeded." << endl;
                }
                else
                {
                    cout << "Invert test failed." << endl;
                    ++numFail;

                    // In the event that the test fails, we store a copy of the matrix
                    // that caused the problem, so we can investigate further.
                    failedTests.emplace_back(newMatrix);
                }
            }
            ++totalRows;
        }
        cout << "Num sucess: " << numSuccess << endl;
        cout << "Num failed: " << numFail << endl;

        // Print out any matrices that caused test to fail.
        for (const auto& currentMatrix : failedTests)
        {
            currentMatrix.PrintMatrix();
            cout << endl;
        }
    }

    // Close the file.
    input.close();
}
