#pragma once

#include <algorithm>
#include <format>
#include <functional>
#include <exception>
#include <ranges>
#include <vector>

namespace Math
{

    void pause()
    {
        std::cout << "Enter any to continue: ";
        char dmy;
        std::cin >> dmy;
    }

    template <typename Range>
    auto to_vector(Range&& r) {
#if __cpp_lib_ranges_to_container >= 202202L // C++23 check
        return std::ranges::to<std::vector>(std::forward<Range>(r));
#else
        using T = std::ranges::range_value_t<Range>;
        return std::vector<T>(std::ranges::begin(r), std::ranges::end(r));
#endif
    }

    template <typename T>
    std::vector<T> zip(const std::vector<T>& lhs, const std::vector<T>& rhs, const std::function<T(T, T)>& func)
    {
        return to_vector(
            std::views::iota(size_t{ 0 }, lhs.size())
            | std::views::transform([&](size_t i) {
                return func(lhs[i], rhs[i]);
                }
            ));
    }

    template <typename T>
    std::vector<T> zip(const T& lhs, const std::vector<T>& rhs, const std::function<T(T, T)>& func)
    {
        return to_vector(
            std::views::iota(size_t{ 0 }, rhs.size())
            | std::views::transform([&](size_t i) {
                return func(lhs, rhs[i]);
                }
            ));
    }

    template <typename T>
    std::vector<T> zip(const std::vector<T>& lhs, T rhs, const std::function<T(T, T)>& func)
    {
        return to_vector(
            std::views::iota(size_t{ 0 }, lhs.size())
            | std::views::transform([&](size_t i) {
                return func(lhs[i], rhs);
                }
            ));
    }

    template <typename T>
    class Matrix2
    {
    public:
        // Define the various constructors
        Matrix2();
        Matrix2(size_t nRows, size_t nColumns);
        Matrix2(size_t nRows, size_t nColumns, const std::vector<T>& inputData);
        Matrix2(size_t nRows, size_t nColumns, std::vector<T>&& inputData);
        Matrix2(const Matrix2<T>& inputMatrix) = default;
        Matrix2(Matrix2<T>&& inputMatrix) noexcept = default;

        // And the destructor
        ~Matrix2() = default;

        // Configuration methods
        void Resize(size_t numRows, size_t numCols);
        void SetToIdentity();

        // Element access methods
        T& operator()(size_t row, size_t column);
        const T& operator()(size_t row, size_t column) const;
        T& At(size_t row, size_t column);
        const T& At(size_t row, size_t column) const;
        size_t GetNumRows() const;
        size_t GetNumCols() const;

        // Traversal routines
        void ForEachElementRowFirst(const std::function<bool(size_t row, size_t column, T& element)>& func);
        void ForEachElementRowFirst(const std::function<bool(size_t row, size_t column, const T& element)>& func) const;
        void ForEachElementInRow(size_t row, const std::function<bool(size_t column, T& element)>& func, size_t startColumn = 0);
        void ForEachElementInColumn(size_t column, const std::function<bool(size_t row, T& element)>& func, size_t startRow = 0);

        void ForEachElementInBothRowFirst(Matrix2<T>& matrix1, Matrix2<T>& matrix2, const std::function<bool(size_t row, size_t column, T& element1, T& element2)>& func);
        void ForEachElementInBothRowFirst(const Matrix2<T>& matrix1, const Matrix2<T>& matrix2, const std::function<bool(size_t row, size_t column, const T& element1, const T& element2)>& func) const;
        void ForEachPairOfElementsInTwoRows(size_t row1, size_t row2, const std::function<bool(size_t column, T& element1, T& element2)>& func);
        void ForEachPairOfElementsInTwoRows(size_t row1, size_t row2, const std::function<bool(size_t column, const T& element1, const T& element2)>& func) const;

        // Manipulation methods
        bool Inverse();

        // overload = operator
        Matrix2<T>& operator=(const Matrix2<T>& rhs) = default;
        Matrix2<T>& operator=(Matrix2<T>&& rhs)noexcept = default;

        // overload == operator
        bool operator==(const Matrix2<T>& rhs) const;
        bool operator!=(const Matrix2<T>& rhs) const;
        bool Compare(const Matrix2<T>& matrix, double tolerance) const;

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

        void Separate(Matrix2<T>& lhs, Matrix2<T>& rhs, size_t colNum);

    private:
        std::vector<T> m_matrixData{ 1 };
        size_t m_nRows{ 1 };
        size_t m_nCols{ 1 };

    public:
        bool IsSquare() const;
        bool CloseEnough(T f1, T f2) const;
        void Swap(size_t row1, size_t row2);
        void MultAdd(size_t toRow, size_t fromRow, T multFactor);
        void MultRow(size_t toRow, T multFactor);
        void Join(const Matrix2<T>& other);
        size_t FindRowWithMaxElement(size_t colNumber, size_t startingRow);
        void PrintMatrix() const;
    };

    // Define the various constructors
    template <typename T>
    Matrix2<T>::Matrix2()
    {
        m_matrixData[0] = {};
    }

    template <typename T>
    Matrix2<T>::Matrix2(const size_t nRows, const size_t nColumns)
        : m_nRows(nRows)
        , m_nCols(nColumns)
        , m_matrixData(nRows* nColumns)
    {
    }

    template <typename T>
    Matrix2<T>::Matrix2(const size_t nRows, const size_t nColumns, const std::vector<T>& inputData)
        : m_nRows(nRows)
        , m_nCols(nColumns)
        , m_matrixData(inputData)
    {
    }

    template <typename T>
    Matrix2<T>::Matrix2(const size_t nRows, const size_t nColumns, std::vector<T>&& inputData)
        : m_nRows(nRows)
        , m_nCols(nColumns)
        , m_matrixData(std::move(inputData))
    {
    }

    // Configuration methods
    template <typename T>
    void Matrix2<T>::Resize(const size_t numRows, const size_t numCols)
    {
        *this = Matrix2<T>(numRows, numCols);
    }
    template <typename T>
    void Matrix2<T>::SetToIdentity()
    {
        if (!IsSquare())
        {
            throw std::invalid_argument("Cannot form an identity matrix that is not square.");
        }

        ForEachElementRowFirst([](size_t row, size_t column, T& element)->bool
            {
                element = (row == column) ? 1.0 : 0.0;
                return false; // continue
            }
        );

    }

    // Element access methods
    template <typename T>
    T& Matrix2<T>::operator()(const size_t row, const size_t column)
    {
        return m_matrixData[(row * m_nCols) + column];
    }

    template <typename T>
    const T& Matrix2<T>::operator()(const size_t row, const size_t column) const
    {
        return m_matrixData[(row * m_nCols) + column];
    }

    template <typename T>
    T& Matrix2<T>::At(const size_t row, const size_t column)
    {
        if (row < m_nRows && column < m_nCols)
        {
            return m_matrixData[(row * m_nCols) + column];
        }

        throw std::out_of_range("Illegal indicies");
    }

    template <typename T>
    const T& Matrix2<T>::At(const size_t row, const size_t column) const
    {
        if (row < m_nRows && column < m_nCols)
        {
            return m_matrixData[(row * m_nCols) + column];
        }

        throw std::out_of_range("Illegal indicies");
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

    template <typename T>
    void Matrix2<T>::ForEachElementRowFirst(const std::function<bool(size_t row, size_t column, T& element)>& func)
    {
        for (size_t row{ 0 }; row < m_nRows; ++row)
        {
            for (size_t column{ 0 }; column < m_nCols; ++column)
            {
                if (func(row, column, (*this)(row, column))) return;
            }
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachElementRowFirst(const std::function<bool(size_t row, size_t column, const T& element)>& func) const
    {
        for (size_t row{ 0 }; row < m_nRows; ++row)
        {
            for (size_t column{ 0 }; column < m_nCols; ++column)
            {
                if (func(row, column, (*this)(row, column))) return;
            }
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachElementInRow(const size_t row, const std::function<bool(size_t column, T& element)>& func, const size_t startColumn)
    {
        if (m_nRows <= row || m_nCols <= startColumn)
        {
            throw std::out_of_range("Illegal indicies");
        }

        auto& self(*this);
        for (size_t column{ startColumn }; column < m_nCols; ++column)
        {
            if (func(column, self(row, column))) return;
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachElementInColumn(const size_t column, const std::function<bool(size_t row, T& element)>& func, const size_t startRow)
    {
        if (m_nRows <= startRow || m_nCols <= column)
        {
            throw std::out_of_range("Illegal indicies");
        }

        auto& self(*this);
        for (size_t row{ startRow }; row < m_nRows; ++row)
        {
            if (func(row, self(row, column))) return;
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachElementInBothRowFirst(Matrix2<T>& matrix1, Matrix2<T>& matrix2, const std::function<bool(size_t row, size_t column, T& element1, T& element2)>& func)
    {
        if (matrix1.GetNumRows() != matrix2.GetNumRows() || matrix1.GetNumCols() != matrix2.GetNumCols())
        {
            throw std::exception("Incompatible indicies");
        }

        for (size_t row{ 0 }; row < m_nRows; ++row)
        {
            for (size_t column{ 0 }; column < m_nCols; ++column)
            {
                if (func(row, column, matrix1(row, column), matrix2(row, column))) return;
            }
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachElementInBothRowFirst(const Matrix2<T>& matrix1, const Matrix2<T>& matrix2, const std::function<bool(size_t row, size_t column, const T& element1, const T& element2)>& func) const
    {
        if (matrix1.GetNumRows() != matrix2.GetNumRows() || matrix1.GetNumCols() != matrix2.GetNumCols())
        {
            throw std::exception("Incompatible indicies");
        }

        for (size_t row{ 0 }; row < m_nRows; ++row)
        {
            for (size_t column{ 0 }; column < m_nCols; ++column)
            {
                if (func(row, column, matrix1(row, column), matrix2(row, column))) return;
            }
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachPairOfElementsInTwoRows(const size_t row1, const size_t row2, const std::function<bool(size_t column, T& element1, T& element2)>& func)
    {
        if (m_nRows <= row1 || m_nRows <= row2)
        {
            throw std::invalid_argument("Illegal row number.");
        }

        auto& self{ *this };

        for (size_t column{ 0 }; column < m_nCols; ++column)
        {
            if (func(column, self(row1, column), self(row2, column))) return;
        }
    }

    template <typename T>
    void Matrix2<T>::ForEachPairOfElementsInTwoRows(const size_t row1, const size_t row2, const std::function<bool(size_t column, const T& element1, const T& element2)>& func) const
    {
        if (m_nRows < row1 || m_nRows < row2)
        {
            throw std::invalid_argument("Illegal row number.");
        }

        auto& self{ *this };

        for (size_t column{ 0 }; column < m_nCols; ++column)
        {
            if (func(column, self(row1, column), self(row2, column))) return;
        }
    }


    // Manipulation methods
    template <typename T>
    bool Matrix2<T>::Inverse()
    {
        auto& self{ *this };

        // Form an identity matrix with the same dimensions as the matrix we wish to inverse
        // Throws if not Square
        Matrix2<T> identityMatrix(m_nRows, m_nCols);
        identityMatrix.SetToIdentity();

        // Join the identity matrix with this one
        const size_t originalColumns{ m_nCols };
        Join(identityMatrix);

        // Begin the main part of the process
        size_t cRow{ 0 };
        size_t cCol{ 0 };
        const size_t maxCount{ 100 };
        size_t count{ 0 };
        bool completeFlag{ false };

        for (size_t diagIndex{ 0 }; diagIndex < m_nRows; ++diagIndex)
        {
            //Loop over the diagonal of the matrix and ensure all diagonal elements are equal to one.
            cRow = diagIndex;
            cCol = diagIndex;

            // Find the index of the maximum element in the current column
            // If this isn't the current row, then swap
            if (size_t maxIndex{ FindRowWithMaxElement(cCol, cRow) }; maxIndex != cRow)
            {
                Swap(cRow, maxIndex);
            }

            // Make sure the value at [cRow, cCol] == 1
            if (const auto elementValue =self(cRow, cCol); elementValue != 1.0)
            {
                if (CloseEnough(elementValue, 0.0))
                {
                    return false;
                }
                T multFactor{ 1.0 / elementValue };
                MultRow(cRow, multFactor);
            }

            // Make sure that al elements in the column cCol is zero, exept for row cRow which is 1.0
            for (size_t rowIndex{ 0 }; rowIndex < m_nRows; ++rowIndex)
            {
                if (rowIndex == cRow) continue;

                MultAdd(rowIndex, cRow, -self(rowIndex, cCol));
            }
        }

        Matrix2<T> leftHalf;
        Matrix2<T> rightHalf;
        Separate(leftHalf, rightHalf, originalColumns);
        if (leftHalf == identityMatrix)
        {
            self = rightHalf;
            return true;
        }
        return false;
    }

    // overload == operator
    template <typename T>
    bool Matrix2<T>::operator==(const Matrix2<T>& rhs) const
    {
        const auto& lhs{ *this };
        bool result{ true };
        try
        {
            ForEachElementInBothRowFirst(lhs, rhs, [&](size_t row, size_t column, const T& element1, const T& element2)->bool
                {
                    if (!CloseEnough(element1, element2))
                    {
                        result = false;
                        return true; // Break
                    }
                    return false;
                }
            );
        }
        catch (const std::exception&)
        {
            return false;
        }

        return result;
    }

    // overload != operator
    template <typename T>
    bool Matrix2<T>::operator!=(const Matrix2<T>& rhs)const
    {
        return !(*this == rhs);
    }

    template <typename T>
    bool Matrix2<T>::Compare(const Matrix2<T>& matrix, double tolerance) const
    {
        const auto numRows{ GetNumRows() };
        const auto numCols{ GetNumCols() };
        if (numRows != matrix.GetNumRows() || numCols != matrix.GetNumCols())
        {
            return false;
        }

        double cumulativeSum{};
        ForEachElementInBothRowFirst(*this, matrix, [&](size_t row, size_t column, const T& element1, const T& element2)
            {
                cumulativeSum += (element1 - element2) * (element1 - element2);
                return false; // continue
            }
        );
        double finalValue{ sqrt(cumulativeSum / ((numRows * numCols) - 1)) };

        return (finalValue < tolerance) ? true : false;
    }

    // overload +,-,and * (friends)
    template <class U> Matrix2<U> operator+ (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        Matrix2<U> result(lhs.m_nRows, lhs.m_nCols, zip<U>(lhs.m_matrixData, rhs.m_matrixData, [](U a, U b) { return a + b; }));
        return result;
    }

    template <class U> Matrix2<U> operator+ (const U& lhs, const Matrix2<U>& rhs)
    {
        Matrix2<U> result(rhs.m_nRows, rhs.m_nCols, zip<U>(lhs, rhs.m_matrixData, [](U a, U b) { return a + b; }));
        return result;
    }

    template <class U> Matrix2<U> operator+ (const Matrix2<U>& lhs, const U& rhs)
    {
        Matrix2<U> result(lhs.m_nRows, lhs.m_nCols, zip<U>(lhs.m_matrixData, rhs, [](U a, U b) { return a + b; }));
        return result;
    }

    template <class U> Matrix2<U> operator- (const Matrix2<U>& lhs, const Matrix2<U>& rhs)
    {
        Matrix2<U> result(lhs.m_nRows, lhs.m_nCols, zip<U>(lhs.m_matrixData, rhs.m_matrixData, [](U a, U b) { return a - b; }));
        return result;
    }

    template <class U> Matrix2<U> operator- (const U& lhs, const Matrix2<U>& rhs)
    {
        Matrix2<U> result(rhs.m_nRows, rhs.m_nCols, zip<U>(lhs, rhs.m_matrixData, [](U a, U b) { return a - b; }));
        return result;
    }

    template <class U> Matrix2<U> operator- (const Matrix2<U>& lhs, const U& rhs)
    {
        Matrix2<U> result(lhs.m_nRows, lhs.m_nCols, zip<U>(lhs.m_matrixData, rhs, [](U a, U b) { return a - b; }));
        return result;
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
            Matrix2<U> result(l_numRows, r_numCols);

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
                        // Perform the calculation on these elements.
                        elementResult += lhs(lhsRow, lhsCol) * rhs(lhsCol, rhsCol);
                    }

                    // Store the result.
                    result(lhsRow, rhsCol) = elementResult;
                }
            }
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
        Matrix2<U> result(rhs.m_nRows, rhs.m_nCols, zip<U>(lhs, rhs.m_matrixData, [](U a, U b) { return a * b; }));

        return result;
    }

    template <class U> Matrix2<U> operator* (const Matrix2<U>& lhs, const U& rhs)
    {
        Matrix2<U> result(lhs.m_nRows, lhs.m_nCols, zip<U>(lhs.m_matrixData, rhs, [](U a, U b) { return a * b; }));

        return result;
    }

    template <class T>
    void Matrix2<T>::Separate(Matrix2<T>& matrix1, Matrix2<T>& matrix2, const size_t colNum)
    {
        if (m_nCols <= colNum)
        {
            throw std::invalid_argument("Illegal row number.");
        }

        matrix1.Resize(m_nRows, colNum);
        matrix2.Resize(m_nRows, m_nCols - colNum);
        ForEachElementRowFirst([&](const size_t row, const size_t column, const T& element) -> bool
            {
                if (column < colNum)
                {
                    matrix1(row, column) = element;
                }
                else
                {
                    matrix2(row, column - colNum) = element;
                }
                return false; // Continue
            }
        );
    }

    template <class T>
    bool Matrix2<T>::IsSquare() const
    {
        return m_nRows == m_nCols;
    }

    template <class T>
    bool Matrix2<T>::CloseEnough(const T f1, const T f2) const
    {
        return fabs(f1 - f2) < 1e-9;
    }

    template <class T>
    void Matrix2<T>::Swap(const size_t row1, const size_t row2)
    {
        ForEachPairOfElementsInTwoRows(row1, row2, [](size_t column, T& element1, T& element2)->bool
            {
                std::swap(element1, element2);
                return false; // continue
            }
        );
    }

    template <class T>
    void Matrix2<T>::MultAdd(const size_t toRow, const size_t fromRow, const T multFactor)
    {
        ForEachPairOfElementsInTwoRows(toRow, fromRow, [multFactor](size_t _, T& element1, T& element2)->bool
            {
                element1 += element2 * multFactor;
                return false; // continue
            }
        );
    }

    template <class T>
    void Matrix2<T>::MultRow(const size_t toRow, const T multFactor)
    {
        ForEachElementInRow(toRow, [multFactor](size_t _, T& element)->bool
            {
                element *= multFactor;
                return false; // continue
            }
        );
    }

    template <class T>
    void Matrix2<T>::Join(const Matrix2<T>& other)
    {
        if (m_nRows != other.m_nRows)
        {
            throw std::invalid_argument("A Join requires the same number of rows in both matrices.");
        }
        Matrix2<T> result(m_nRows, m_nCols + other.m_nCols);
        Matrix2<T>& self(*this);

        result.ForEachElementRowFirst([&](const size_t row, const size_t column, const T& _) -> bool
            {
                if (column < self.m_nCols)
                {
                    result(row, column) = self(row, column);
                }
                else
                {
                    result(row, column) = other(row, column - self.m_nCols);
                }

                return false; // constinue
            }
        );

        self = result;
    }

    template <class T>
    size_t Matrix2<T>::FindRowWithMaxElement(size_t colNumber, size_t startingRow)
    {
        if (m_nRows <= startingRow || m_nCols <= colNumber)
        {
            throw std::out_of_range("Illegal indicies");
        }
        auto& self(*this);

        size_t rowIndex{ startingRow };
        T tempValue{ self(colNumber, startingRow) };
        const auto func{ [&rowIndex, &tempValue](const size_t row, T& element)->bool
            {
                if (fabs(element) > fabs(tempValue))
                {
                    tempValue = element;
                    rowIndex = row;
                }
                return false; // continue
            }
        };
        if (startingRow + 1 < m_nRows)
        {
            ForEachElementInColumn(colNumber, func, startingRow + 1);
        }

        return rowIndex;
        // TBD;
    }

    template <class T>
    void Matrix2<T>::PrintMatrix() const
    {
        size_t count{ 0 };
        for (T element : m_matrixData)
        {
            if (count == m_nCols)
            {
                count = 0;
                std::cout << std::endl;
            }
            std::cout << std::format("{:3f} ", element);
            ++count;
        }
        std::cout << std::endl;
    }
}