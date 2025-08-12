#pragma once

#include <algorithm>
#include <functional>
#include <exception>
#include <ranges>
#include <vector>

namespace Math
{

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
    class MyVec
    {
    public:
        MyVec(size_t rows, size_t columns, std::vector<T>& matrixData)
            : m_nRows(rows)
            , m_nCols(columns)
            , m_matrixData(matrixData)
        {}
        
        T& operator()(size_t row, size_t column)
        {
            return m_matrixData[Sub2Ind(row, column)];
        }

        const T& operator()(size_t row, size_t column) const
        {
            return m_matrixData[Sub2Ind(row, column)];
        }

    private:
        size_t m_nRows;
        size_t m_nCols;
        std::vector<T>& m_matrixData;

        size_t Sub2Ind(const size_t row, const size_t col) const
        {
            if (row < m_nRows && col < m_nCols)
            {
                return (row * m_nCols) + col;
            }

            throw std::exception("Illegal indicies");
        }
    };
    template <typename T>
    class MyVecConst
    {
    public:
        MyVecConst(size_t rows, size_t columns, const std::vector<T>& matrixData)
            : m_MyVec(rows, columns, const_cast<std::vector<T>&>(matrixData))
        {
        }

        T operator()(size_t row, size_t column) const
        {
            return m_MyVec(row, column);
        }

    private:
        const MyVec<T> m_MyVec;
    };

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

        // Element access methods
        T GetElement(size_t row, size_t col) const;
        void SetElement(size_t row, size_t col, T element);
        size_t GetNumRows() const;
        size_t GetNumCols() const;

        // overload = operator
        Matrix2<T>& operator=(const Matrix2<T>& rhs) = default;
        Matrix2<T>& operator=(Matrix2<T>&& rhs)noexcept = default;

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
        std::vector<T> m_matrixData{ 1 };
        size_t m_nRows{ 1 };
        size_t m_nCols{ 1 };
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

    // Element access methods
    template <typename T>
    T Matrix2<T>::GetElement(const size_t row, const size_t col) const
    {
        MyVecConst<T> myVec(m_nRows, m_nCols, m_matrixData);
        return myVec(row, col);
    }

    template <typename T>
    void Matrix2<T>::SetElement(const size_t row, const size_t col, const T elementValue)
    {
        MyVec<T> myVec(m_nRows, m_nCols, m_matrixData);
        myVec(row, col) = elementValue;
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

    // overload == operator
    template <typename T>
    bool Matrix2<T>::operator==(const Matrix2<T>& rhs)const
    {
        const auto& lhs{ *this };

        if (lhs.m_nRows != rhs.m_nRows) return false;
        if (lhs.m_nCols != rhs.m_nCols) return false;
        if (lhs.m_matrixData != rhs.m_matrixData) return false;

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
            // This is the standard matrix multiplication condition
            // The output will be the same size as the RHS
            std::vector<U> tempResult(l_numRows * r_numCols);

            MyVecConst<U> l_matrix(l_numRows, l_numCols, lhs.m_matrixData);
            MyVecConst<U> r_matrix(r_numRows, r_numCols, rhs.m_matrixData);
            MyVec<U> t_matrix(l_numRows, r_numCols, tempResult);

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
                        elementResult += l_matrix(lhsRow, lhsCol) * r_matrix(lhsCol, rhsCol);
                    }

                    // Store the result.
                    t_matrix(lhsRow, rhsCol) = elementResult;
                }
            }
            Matrix2<U> result(l_numRows, r_numCols, std::move(tempResult));
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

}