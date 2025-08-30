#pragma once

#include <format>
#include <vector>

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

        // Overloaded operators
        Vector<T> operator+(const Vector<T>& rhs) const;
        Vector<T> operator-(const Vector<T>& rhs) const;
        Vector<T> operator*(const T& factor) const;

        // Static functions
        static T Dot(const Vector<T>& a, const Vector<T>& b);
        static Vector<T> Cross(const Vector<T>& a, const Vector<T>& b);

        // Print
        void PrintVector() const;

    private:
        size_t m_nDims{};
        std::vector<T> m_Vector;
    };

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
    Vector<T> Vector<T>::operator+(const Vector<T>& rhs) const
    {
        if (m_nDims != rhs.m_nDims)
        {
            throw std::invalid_argument("Vector dimensions do not match.");
        }
        Vector<T> result;
        result.m_nDims = m_nDims;
        result.m_Vector.resize(m_nDims);

        std::ranges::transform(m_Vector, rhs.m_Vector, result.m_Vector.begin(),
            [](T x, T y) { return x + y; } 
        );

        return result;
    }

    template <typename T>
    Vector<T> Vector<T>::operator-(const Vector<T>& rhs) const
    {
        if (m_nDims != rhs.m_nDims)
        {
            throw std::invalid_argument("Vector dimensions do not match.");
        }
        Vector<T> result;
        result.m_nDims = m_nDims;
        result.m_Vector.resize(m_nDims);

        std::ranges::transform(m_Vector, rhs.m_Vector, result.m_Vector.begin(),
            [](T x, T y) { return x - y; }
        );

        return result;
    }

    template <typename T>
    Vector<T> Vector<T>::operator*(const T& factor) const
    {
        Vector<T> result;
        result.m_nDims = m_nDims;
        result.m_Vector.resize(m_nDims);

        std::ranges::transform(m_Vector, result.m_Vector.begin(),
            [factor](int x) { return x * factor; } 
        );

        return result;
    }

    template <typename U>
    Vector<U> operator*(const U& lhs, const Vector<U>& rhs)
    {
        return rhs * lhs;
    }

    template <typename T>
    T Vector<T>::Dot(const Vector<T>& a, const Vector<T>& b)
    {
        if (a.m_nDims != b.m_nDims)
        {
            throw std::invalid_argument("Vector dimensions must match for the do-product to be computet.");
        }

        T cumulativeSum{};
        for (size_t i{ 0 }; i < a.m_nDims; ++i)
        {
            cumulativeSum += a.m_Vector.at(i) * b.m_Vector.at(i);
        }

        return cumulativeSum;
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
        resultData.push_back((a.m_Vector.at(1)*b.m_Vector.at(2)) - (a.m_Vector.at(2) * b.m_Vector.at(1)));
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

}