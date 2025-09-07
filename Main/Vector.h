#pragma once

#include <format>
#include <functional>
#include <vector>

#include "Matrix.h"

namespace Math
{

    template <typename T>
    class Vector
    {
    public:
        // Define the various constructors
        Vector() = default;
        Vector(const std::vector<T>& inputData);
        Vector(std::vector<T>&& inputData);
        Vector(const Vector<T>& other) = default;
        Vector(Vector<T>&& other) noexcept = default;

        // The destructor
        ~Vector() = default;

        // Overload = operator
        Vector<T>& operator=(const Vector<T>& rhs) = default;
        Vector<T>& operator=(Vector<T>&& rhs) noexcept = default;

        // Functions to return parameter of the vector
        size_t GetNumDims() const;

        // Functions to handle elements of the vector
        T GetELement(size_t index) const;
        void SetElement(size_t index, T value);

        // Functions to perform computations on the vector.
        // Return the length of the vector
        T Norm() const;

        // Return a normalized copy of the vector
        Vector<T> Normalized() const;

        // Normalize the vector in place
        void Normalize();

        // Overloaded operators
        Vector<T> operator+(const Vector<T>& rhs) const;
        Vector<T>& operator+=(const Vector<T>& rhs);
        Vector<T> operator-(const Vector<T>& rhs) const;
        Vector<T>& operator-=(const Vector<T>& rhs);
        Vector<T> operator*(const T& factor) const;
        Vector<T>& operator*=(const T& factor);
        Vector<T> operator/(const T& denominator) const;
        Vector<T>& operator/=(const T& denominator);

        // Conversion rutines
        Matrix2<T> AsMatrix2WithSingleColumn() const;
        Matrix2<T> AsMatrix2WithSingleRow() const;

        // Static functions
        static T Dot(const Vector<T>& a, const Vector<T>& b);
        static Vector<T> Cross(const Vector<T>& a, const Vector<T>& b);

        // Print
        void PrintVector() const;

    private:
        size_t m_nDims{};
        std::vector<T> m_Vector;

        void Transform(const Vector<T>& rhs, const std::function<T(T, T)>& func);
        void Transform(const std::function<T(T)>& func);
        T Sum(const Vector<T>& rhs, const std::function<T(T, T)>& func) const;
        T Sum(const std::function<T(T)>& func) const;
    };

    template <typename U> Vector<U> operator*(const U& factor, const Vector<U>& rhs);
    template <typename U> Vector<U> operator/(const U& factor, const Vector<U>& rhs);

    template <typename U> Vector<U> operator*(const Matrix2<U>& matrix, const Vector<U>& rhs);
    template <typename U> Vector<U> linear_solve(const Matrix2<U>& matrix, const Vector<U>& rhs);

    template <typename T>
    Vector<T>::Vector(const std::vector<T>& inputData)
        : m_nDims(inputData.size())
        , m_Vector(inputData)
    {
    }

    template <typename T>
    Vector<T>::Vector(std::vector<T>&& inputData)
        : m_nDims(inputData.size())
        , m_Vector(std::move(inputData))
    {
    }

    template <typename T>
    size_t Vector<T>::GetNumDims() const
    {
        return m_nDims;
    }

    template <typename T>
    T Vector<T>::GetELement(size_t index) const
    {
        if (index >= m_Vector.size())
        {
            throw std::out_of_range("Illegal indicies");
        }
        return m_Vector[index];
    }

    template <typename T>
    void Vector<T>::SetElement(size_t index, T value)
    {
        if (index >= m_Vector.size())
        {
            throw std::out_of_range("Illegal indicies");
        }
        m_Vector[index] = value;
    }

    template <typename T>
    T Vector<T>::Norm() const
    {
        const auto sqr{ [](T x) -> T { return x * x; } };
        return sqrt(Sum(sqr));
    }

    template <typename T>
    Vector<T> Vector<T>::Normalized() const
    {
        // Copy *this
        Vector<T> result(*this);

        // Normalize the copy
        result.Normalize();

        // Return result
        return result;
    }

    // Normalize the vector in place
    template <typename T>
    void Vector<T>::Normalize()
    {
        // Compute the vector norm
        const T vectNorm{ Norm() };

        // Function to normalize an element
        const auto normalizeElement{ [vectNorm](T x) -> T { return x / vectNorm; } };

        // Perfor the normalizeElement transformation on each element
        Transform(normalizeElement);
    }

    template <typename T>
    Vector<T> Vector<T>::operator+(const Vector<T>& rhs) const
    {
        const auto add{ [](T x, T y) -> T { return x + y; } };

        Vector<T> result(*this);
        result.Transform(rhs, add);
        return result;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
    {
        const auto add{ [](T x, T y) -> T { return x + y; } };

        Transform(rhs, add);
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator-(const Vector<T>& rhs) const
    {
        const auto subtract{ [](T x, T y) -> T { return x - y; } };

        Vector<T> result(*this);
        result.Transform(rhs, subtract);
        return result;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs)
    {
        const auto subtract{ [](T x, T y) -> T { return x - y; } };

        Transform(rhs, subtract);
        return *this;
    }

    template <typename T>
    Vector<T> Vector<T>::operator*(const T& factor) const
    {
        const auto multiply{ [factor](T x) -> T { return x * factor; } };

        Vector<T> result(*this);
        result.Transform(multiply);
        return result;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator*=(const T& factor)
    {
        const auto multiply{ [factor](T x) -> T { return x * factor; } };

        Transform(multiply);
        return *this;
    }

    template <typename U>
    Vector<U> operator*(const U& factor, const Vector<U>& rhs)
    {
        return rhs * factor;
    }

    template <typename T>
    Vector<T> Vector<T>::operator/(const T& denominator) const
    {
        const auto divide{ [denominator](T x) -> T { return x / denominator; } };

        Vector<T> result(*this);
        result.Transform(divide);
        return result;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator/=(const T& denominator)
    {
        const auto divide{ [denominator](T x) -> T { return x / denominator; } };

        Transform(divide);
        return *this;
    }

    template <typename U>
    Vector<U> operator/(const U& factor, const Vector<U>& rhs)
    {
        return rhs / factor;
    }

    template <typename T>
    Matrix2<T> Vector<T>::AsMatrix2WithSingleColumn() const
    {
        Matrix2<T> result(m_nDims, 1, m_Vector);

        return result;
    }

    template <typename T>
    Matrix2<T> Vector<T>::AsMatrix2WithSingleRow() const
    {
        Matrix2<T> result(1, m_nDims, m_Vector);

        return result;
    }

    template <typename T>
    T Vector<T>::Dot(const Vector<T>& a, const Vector<T>& b)
    {
        const auto multiply{ [](T x, T y) -> T { return x * y; } };

        return a.Sum(b, multiply);
    }

    template <typename T>
    Vector<T> Vector<T>::Cross(const Vector<T>& a, const Vector<T>& b)
    {
        if (a.m_nDims != b.m_nDims)
        {
            throw std::invalid_argument("Vector dimensions must match for the cross-product to be computet.");
        }

        // Check that the number of dimension is 3.
        // Although the cross product is also defined for 7 dimensions, we are 
        // not going to consider that case at this time.

        if (a.m_nDims != 3)
        {
            throw std::invalid_argument("The cross-product can only be computed for 3 dimensions.");
        }

        std::vector<T> resultData;
        resultData.push_back((a.m_Vector.at(1) * b.m_Vector.at(2)) - (a.m_Vector.at(2) * b.m_Vector.at(1)));
        resultData.push_back(-((a.m_Vector.at(0) * b.m_Vector.at(2)) - (a.m_Vector.at(2) * b.m_Vector.at(0))));
        resultData.push_back((a.m_Vector.at(0) * b.m_Vector.at(1)) - (a.m_Vector.at(1) * b.m_Vector.at(0)));

        Vector<T> result(std::move(resultData));
        return result;
    }

    template <typename T>
    void Vector<T>::PrintVector() const
    {
        for (size_t i{ 0 }; i < m_Vector.size(); ++i)
        {
            std::cout << std::format("{:.3f} ", m_Vector.at(i));
        }
        std::cout << std::endl;
    }

    template <typename T>
    void Vector<T>::Transform(const Vector<T>& rhs, const std::function<T(T, T)>& func)
    {
        if (m_nDims != rhs.m_nDims)
        {
            throw std::invalid_argument("Vector dimensions do not match.");
        }

        std::ranges::transform(m_Vector, rhs.m_Vector, m_Vector.begin(), func);
    }

    template <typename T>
    void Vector<T>::Transform(const std::function<T(T)>& func)
    {
        std::ranges::transform(m_Vector, m_Vector.begin(), func);
    }

    template <typename T>
    T Vector<T>::Sum(const Vector<T>& rhs, const std::function<T(T, T)>& func) const
    {
        if (m_nDims != rhs.m_nDims)
        {
            throw std::invalid_argument("Vector dimensions do not match.");
        }

        T cumulativeSum{};
        for (size_t i{ 0 }; i < m_nDims; ++i)
        {
            cumulativeSum += func(m_Vector.at(i), rhs.m_Vector.at(i));
        }

        return cumulativeSum;
    }

    template <typename T>
    T Vector<T>::Sum(const std::function<T(T)>& func) const
    {
        T cumulativeSum{};
        for (size_t i{ 0 }; i < m_nDims; ++i)
        {
            cumulativeSum += func(m_Vector.at(i));
        }

        return cumulativeSum;
    }

    template <typename U> Vector<U> operator*(const Matrix2<U>& lhs, const Vector<U>& vec)
    {
        // Verify the dimensions of the input
        if (lhs.GetNumCols() != vec.GetNumDims())
        {
            throw std::invalid_argument("Number of columns in matrix must equal number of rows in vector.");
        }

        const Matrix2<U> rhs{ vec.AsMatrix2WithSingleColumn() };

        const Matrix2<U> resultMatrix{ lhs * rhs };

        Vector<U> resultVector{ resultMatrix.AsVector() };

        return resultVector;
    }

    template <typename U> Vector<U> linear_solve(const Matrix2<U>& matrix, const Vector<U>& vec)
    {
        // Verify the dimensions of the input
        if (matrix.GetNumRows() != vec.GetNumDims())
        {
            throw std::invalid_argument("Number of rows in matrix must equal number of rows in vector.");
        }

        // Convert inpyt vector to a n x 1 matrix
        auto vecAsMatrix{ vec.AsMatrix2WithSingleColumn() };

        // Create an augmented matrix
        Matrix2<U> augmentedMatrix(matrix);
        augmentedMatrix.Join(vecAsMatrix);
        // Transform the augemented matrix into row echelon form
        Matrix2<U> rowEchelonMatrix{ augmentedMatrix.RowEchelon() };

        Vector<U> output{ vec };

        size_t numRows{ rowEchelonMatrix.GetNumRows() };
        size_t numCols{ rowEchelonMatrix.GetNumCols() };
        size_t startRow{ numRows - 1 };

        // Loop over the rows in reverse order
        for (int ii{ static_cast<int>(startRow) }; ii >= 0; --ii)
        {
            size_t i{static_cast<size_t>(ii)};

            // Extract the current result for this row
            U currentResult{ rowEchelonMatrix(i, numCols - 1) };

            // Compute the cumulative sum.
            U cumulativSum{};
            for (size_t j{ i + 1 }; j < numRows; ++j)
            {
                cumulativSum += rowEchelonMatrix(i, j) * output.GetELement(j);
            }

            // Cumpute the answer.
            U finalAnswer{ (currentResult - cumulativSum) / rowEchelonMatrix(i, i) };

            // And store.
            output.SetElement(i, finalAnswer);
        }

        return output;
    }

}