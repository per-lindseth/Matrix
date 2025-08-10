#pragma once

#include <algorithm>
#include <exception>

namespace Math
{
    template <typename T>
    class Matrix2
    {
    public:
        // Define the various constructors
        Matrix2();
        Matrix2(size_t nRows, size_t nColumns);
        Matrix2(size_t nRows, size_t nColumns, const T* inputData);
        Matrix2(const Matrix2<T>& inputMatrix);
        Matrix2(Matrix2<T>&& inputMatrix) noexcept;

        // And the destructor
        ~Matrix2();

        // Configuration methods
        void Resize(size_t numRows, size_t numCols);

        // Element access methods
        T GetElement(size_t row, size_t col) const;
        void SetElement(size_t row, size_t col, T element);
        size_t GetNumRows() const;
        size_t GetNumCols() const;

        // overload = operator
        Matrix2<T>& operator=(const Matrix2<T>& rhs);
        Matrix2<T>& operator=(Matrix2<T>&& rhs)noexcept;

        // overload == operator
        bool operator==(const Matrix2<T>& rhs) const;
        bool operator!=(const Matrix2<T>& rhs) const;

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
        size_t Sub2Ind(size_t row, size_t col) const;
        T* m_matrixData{};
        size_t m_nRows{ 1 };
        size_t m_nCols{ 1 };
        size_t m_nElements{ 1 };
    };

    // Define the various constructors
    template <typename T>
    Matrix2<T>::Matrix2()
    {
        m_matrixData = new T[m_nElements];
        m_matrixData[0] = {};
    }

    template <typename T>
    Matrix2<T>::Matrix2(const size_t nRows, const size_t nColumns)
        : m_nRows(nRows)
        , m_nCols(nColumns)
        , m_nElements(nRows* nColumns)
    {
        m_matrixData = new T[m_nElements];
        for (size_t i{ 0 }; i < m_nElements; ++i)
        {
            m_matrixData[i] = {};
        }
    }

    template <typename T>
    Matrix2<T>::Matrix2(const size_t nRows, const size_t nColumns, const T* inputData)
        : m_nRows(nRows)
        , m_nCols(nColumns)
        , m_nElements(nRows* nColumns)
    {
        m_matrixData = new T[m_nElements];
        for (size_t i{ 0 }; i < m_nElements; ++i)
        {
            m_matrixData[i] = inputData[i];
        }
    }

    template <typename T>
    Matrix2<T>::Matrix2(const Matrix2<T>& inputMatrix)
        : m_nRows(inputMatrix.m_nRows)
        , m_nCols(inputMatrix.m_nCols)
        , m_nElements(inputMatrix.m_nElements)
    {
        m_matrixData = new T[m_nElements];
        for (size_t i{ 0 }; i < m_nElements; ++i)
        {
            m_matrixData[i] = inputMatrix.m_matrixData[i];
        }
    }

    template <typename T>
    Matrix2<T>::Matrix2(Matrix2<T>&& inputMatrix) noexcept
    {
        std::swap(m_nRows, inputMatrix.m_nRows);
        std::swap(m_nCols, inputMatrix.m_nCols);
        std::swap(m_nElements, inputMatrix.m_nElements);
        std::swap(m_matrixData, inputMatrix.m_matrixData);
    }

    // And the destructor
    template <typename T>
    Matrix2<T>::~Matrix2()
    {
        delete m_matrixData;
    }

    // Configuration methods
    template <typename T>
    void Matrix2<T>::Resize(const size_t numRows, const size_t numCols)
    {
        *this = Matrix2<2>(numRows, numCols);
    }

    // Element access methods
    template <typename T>
    T Matrix2<T>::GetElement(const size_t row, const size_t col) const
    {
        size_t linearIndex{ Sub2Ind(row, col) };
        return m_matrixData[linearIndex];
    }

    template <typename T>
    void Matrix2<T>::SetElement(const size_t row, const size_t col, const T elementValue)
    {
        size_t linearIndex{ Sub2Ind(row, col) };
        m_matrixData[linearIndex] = elementValue;
    }

    template <typename T>
    size_t Matrix2<T>::GetNumRows() const
    {
        return m_nRows;
    }

    template <typename T>
    size_t Matrix2<T>::GetNumCols() const
    {
        return m_nCols;
    }

    // overload = operator
    template <typename T>
    Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        m_nRows = rhs.m_nRows;
        m_nCols = rhs.m_nCols;
        m_nElements = rhs.m_nElements;
        delete[]m_matrixData;

        m_matrixData = new T[m_nElements];
        for (size_t i{ 0 }; i < m_nElements; ++i)
        {
            m_matrixData[i] = rhs.m_matrixData[i];
        }

        return *this;
    }

    template <typename T>
    Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>&& rhs) noexcept
    {
        std::swap(m_nRows, rhs.m_nRows);
        std::swap(m_nCols, rhs.m_nCols);
        std::swap(m_nElements, rhs.m_nElements);
        std::swap(m_matrixData, rhs.m_matrixData);

        return *this;
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
        for (size_t i{ 0 }; i < lhs.m_nElements; ++i)
        {
            if (lhs.m_matrixData[i] != rhs.m_matrixData[i])
            {
                return false;
            }
        }
        return true;
    }

    // overload != operator
    template <typename T>
    bool Matrix2<T>::operator!=(const Matrix2<T>& rhs)const
    {
        return !(*this == rhs);
    }

    // overload +,-,and * (friends)
    template <class U> Matrix2<U> operator+ (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        size_t numRows{ lhs.m_nRows };
        size_t numCols{ lhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator+ (const U& lhs, const Matrix2<U>& rhs)
    {
        size_t numRows{ rhs.m_nRows };
        size_t numCols{ rhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs + rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator+ (const Matrix2<U>& lhs, const U& rhs)
    {
        size_t numRows{ lhs.m_nRows };
        size_t numCols{ lhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] + rhs;
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator- (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        size_t numRows{ lhs.m_nRows };
        size_t numCols{ lhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator- (const U& lhs, const Matrix2<U>& rhs)
    {
        size_t numRows{ rhs.m_nRows };
        size_t numCols{ rhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs - rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator- (const Matrix2<U>& lhs, const U& rhs)
    {
        size_t numRows{ lhs.m_nRows };
        size_t numCols{ lhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] - rhs;
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator* (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        size_t r_numRows{ rhs.m_nRows };
        size_t r_numCols{ rhs.m_nCols };
        size_t l_numRows{ lhs.m_nRows };
        size_t l_numCols{ lhs.m_nCols };

        if (l_numCols == r_numRows)
        {
            // This is the standard matrix multiplication condition
            // The output will be the same size as the RHS
            U* tempResult{ new U[l_numRows * r_numCols] };

            // Loop through each row of the LHS
            for (size_t lhsRow{ 0 }; lhsRow < l_numRows; ++lhsRow)
            {
                // Loop through each column of the RHS
                for (size_t rhsCol{ 0 }; rhsCol < r_numCols; ++rhsCol)
                {
                    U elementResult{ U{} };

                    // Loop through each element of this LHS row
                    for (size_t lhsCol{ 0 }; lhsCol < l_numCols; ++lhsCol)
                    {
                        // Compute the LHS linear index.
                        size_t lhsLinearIndex{ (lhsRow * l_numCols) + lhsCol };

                        // compute the RHS liear index (based on LHS col)
                        // rhs row number equal to lhs column number.
                        size_t rhsLinearIndex{ (lhsCol * r_numCols) + rhsCol };

                        // Perform the calculation on these elements.
                        elementResult += lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex];
                    }

                    // Store the result.
                    size_t resultLinearIndex{ (lhsRow * r_numCols) + rhsCol };
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
        size_t numRows{ rhs.m_nRows };
        size_t numCols{ rhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs * rhs.m_matrixData[i];
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <class U> Matrix2<U> operator* (const Matrix2<U>& lhs, const U& rhs)
    {
        size_t numRows{ lhs.m_nRows };
        size_t numCols{ lhs.m_nCols };
        size_t numElements{ numRows * numCols };
        U* tempResult{ new U[numElements] };
        for (size_t i{ 0 }; i < numElements; ++i)
        {
            tempResult[i] = lhs.m_matrixData[i] * rhs;
        }
        Matrix2<U> result(numRows, numCols, tempResult);
        delete[]tempResult;
        return result;
    }

    template <typename T>
    size_t Matrix2<T>::Sub2Ind(const size_t row, const size_t col) const
    {
        if (row < m_nRows && col < m_nCols)
        {
            return (row * m_nCols) + col;
        }

        throw std::exception("Illegal indicies");
    }

}