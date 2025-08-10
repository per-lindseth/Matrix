#pragma once

namespace Math
{
    template <typename T>
    class Matrix2
    {
    public:
        // Define the various constructors
        Matrix2();
        Matrix2(int nRows, int nColumns);
        Matrix2(int nRows, int nColumns, const T* inputData);
        Matrix2(const Matrix2<T>& inputMatrix);

        // And the destructor
        ~Matrix2();

        // Configuration methods
        bool resize(int numRows, int numCols);

        // Element access methods
        T GetElement(int row, int col);
        bool SetElement(int row, int col, T element);
        int GetNumRows();
        int GetNumCols();

        // overload == operator
        bool operator==(const Matrix2<T>& rhs) const;

        // overload +,-,and * (friends)
        template <class U> friend Matrix2<U> operator+ (const Matrix2<U>& lhs, const Matrix2<U>& rhs);
        template <class U> friend Matrix2<U> operator+ (const U& lhs, const Matrix2<U>& rhs);
        template <class U> friend Matrix2<U> operator+ (const Matrix2<U>& lhs, const U& rhs);

        template <class U> friend Matrix2<U> operator- (const Matrix2<U>& lhs, const Matrix2<U>& rhs);
        template <class U> friend Matrix2<U> operator- (const U& lhs, const Matrix2<U>& rhs);
        template <class U> friend Matrix2<U> operator- (const Matrix2<U>& lhs, const U& rhs);

        template <class U> friend Matrix2<U> operator* (const Matrix2<U>& lhs, const Matrix2<U>& rhs);
        template <class U> friend Matrix2<U> operator* (const U& lhs, const Matrix2<U>& rhs);
        template <class U> friend Matrix2<U> operator* (const Matrix2<U>& lhs, const U& rhs);

    private:
        int Sub2Ind(int row, int col);
        T* m_matrixData;
        int m_nRows;
        int m_nCols;
        int m_nElements;
    };

    // Define the various constructors
    template <typename T>
    Matrix2<T>::Matrix2()
    {
        m_nRows = 1;
        m_nCols = 1;
        m_nElements = 1;
        m_matrixData = new T[m_nElements];
        m_matrixData[0] = 0.0;
    }

    template <typename T>
    Matrix2<T>::Matrix2(int nRows, int nColumns)
    {
        m_nRows = nRows;
        m_nCols = nColumns;
        m_nElements = 1;
        m_matrixData = new T[m_nElements];
        m_matrixData[0] = 0.0;
    }

    template <typename T>
    Matrix2<T>::Matrix2(int nRows, int nColumns, const T* inputData)
    {
        m_nRows = nRows;
        m_nCols = nColumns;
        m_nElements = m_nRows * m_nCols;
        m_matrixData = new T[m_nElements];
        for (int i = 0; i < m_nElements; ++i)
        {
            m_matrixData[i] = inputData[i];
        }
    }

    template <typename T>
    Matrix2<T>::Matrix2(const Matrix2<T>& inputMatrix)
    {
        m_nRows = inputMatrix.m_nRows;
        m_nCols = inputMatrix.m_nCols;
        m_nElements = m_nRows * m_nCols;
        m_matrixData = new T[m_nElements];
        for (int i = 0; i < m_nElements; ++i)
        {
            m_matrixData[i] = inputMatrix.m_matrixData[i];
        }
    }

    // And the destructor
    template <typename T>
    Matrix2<T>::~Matrix2()
    {
        delete m_matrixData;
    }

    // Configuration methods
    template <typename T>
    bool Matrix2<T>::resize(int numRows, int numCols)
    {
        m_nRows = numRows;
        m_nCols = numCols;
        m_nElements = m_nRows * m_nCols;
        delete[]m_matrixData;
        m_matrixData = new T[m_nElements];
        if (m_matrixData != nullptr)
        {
            for (int i = 0; i < m_nElements; ++i)
            {
                m_matrixData[i] = 0.0;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    // Element access methods
    template <typename T>
    T Matrix2<T>::GetElement(int row, int col)
    {
        int linearIndex = Sub2Ind(row, col);
        if (linearIndex >= 0)
        {
            return m_matrixData[linearIndex];
        }
        else
        {
            return 0.0;
        }
    }

    template <typename T>
    bool Matrix2<T>::SetElement(int row, int col, T elementValue)
    {
        int linearIndex = Sub2Ind(row, col);
        if (linearIndex >= 0)
        {
            m_matrixData[linearIndex] = elementValue;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    int Matrix2<T>::GetNumRows()
    {
        return m_nRows;
    }

    template <typename T>
    int Matrix2<T>::GetNumCols()
    {

        return m_nCols;
    }

    // overload == operator
    template <typename T>
    bool Matrix2<T>::operator==(const Matrix2<T>& rhs)const 
    {
        const auto& lhs{ *this };
        // check if the matricies are teh same size, if not return false.
        if ((lhs.m_nRows != rhs.m_nRows) || (lhs.m_nCols != rhs.m_nCols))
        {
            return false;
        }

        // Check if the elements are equal
        for (int i = 0; i < lhs.m_nElements; ++i)
        {
            if (lhs.m_matrixData[i] != rhs.m_matrixData[i])
            {
                return false;
            }
        }
        return true;
    }

    // overload +,-,and * (friends)
    template <class U> Matrix2<U> operator+ (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        int numRows = lhs.m_nRows;
        int numCols = lhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator+ (const U& lhs, const Matrix2<U>& rhs)
    {
        int numRows = rhs.m_nRows;
        int numCols = rhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs + rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator+ (const Matrix2<U>& lhs, const U& rhs)
    {
        int numRows = lhs.m_nRows;
        int numCols = lhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] + rhs;
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator- (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        int numRows = lhs.m_nRows;
        int numCols = lhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator- (const U& lhs, const Matrix2<U>& rhs)
    {
        int numRows = rhs.m_nRows;
        int numCols = rhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs - rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator- (const Matrix2<U>& lhs, const U& rhs)
    {
        int numRows = lhs.m_nRows;
        int numCols = lhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] - rhs;
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator* (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        int r_numRows = rhs.m_nRows;
        int r_numCols = rhs.m_nCols;
        int l_numRows = lhs.m_nRows;
        int l_numCols = lhs.m_nCols;

        if (l_numCols == r_numRows)
        {
            // This is the standard matrix multiplication condition
            // The output will be the same size as the RHS
            U* tempResult = new U[l_numRows * r_numCols];

            // Loop through each row of the LHS
            for (int lhsRow = 0; lhsRow < l_numRows; ++lhsRow)
            {
                // Loop through each column of the RHS
                for (int rhsCol = 0; rhsCol < r_numCols; ++rhsCol)
                {
                    U elementResult = 0.0;

                    // Loop through each element of this LHS row
                    for (int lhsCol = 0; lhsCol < l_numCols; ++lhsCol)
                    {
                        // Compute the LHS linear index.
                        int lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;

                        // compute the RHS liear index (based on LHS col)
                        // rhs row number equal to lhs column number.
                        int rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;

                        // Perform the calculation on these elements.
                        elementResult += lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex];
                    }

                    // Store the result.
                    int resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
                    tempResult[resultLinearIndex] = elementResult;
                }
            }
            Matrix2<U> result(l_numRows, r_numCols, tempResult);
            delete[]tempResult;
            return result;
        }
        else
        {
            Matrix2<U> result(1, 1);
            return result;
        }
    }

    template <class U> Matrix2<U> operator* (const U& lhs, const Matrix2<U>& rhs)
    {
        int numRows = rhs.m_nRows;
        int numCols = rhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs * rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator* (const Matrix2<U>& lhs, const U& rhs)
    {
        int numRows = lhs.m_nRows;
        int numCols = lhs.m_nCols;
        int numElements = numRows * numCols;
        U* tempResult = new U[numElements];
        for (int i = 0; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] * rhs;
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <typename T>
    int Matrix2<T>::Sub2Ind(int row, int col)
    {
        if (((row < m_nRows) && (row >= 0) && (col < m_nCols) && (col >= 0)))
        {
            return (row * m_nCols) + col;
        }
        else
        {
            return -1;
        }
    }

}