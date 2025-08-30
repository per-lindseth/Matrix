#include "pch.h"
#include "../Main/Matrix.h"

using namespace Math;

TEST(MatrixTest, DefaultConstructor)
{
    Matrix2<double> m;
    EXPECT_EQ(m.GetNumRows(), 1);
    EXPECT_EQ(m.GetNumCols(), 1);
    EXPECT_EQ(m.At(0, 0), 0.0);
}

TEST(MatrixTest, ZeroConstructor)
{
    Matrix2<double> m(2, 3);
    EXPECT_EQ(m.GetNumRows(), 2);
    EXPECT_EQ(m.GetNumCols(), 3);
    EXPECT_EQ(m.At(0, 0), 0.0);
    EXPECT_EQ(m.At(1, 0), 0.0);
    EXPECT_EQ(m.At(0, 1), 0.0);
    EXPECT_EQ(m.At(1, 1), 0.0);
    EXPECT_EQ(m.At(0, 2), 0.0);
    EXPECT_EQ(m.At(1, 2), 0.0);
}

TEST(MatrixTest, DataConstructor)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m(3, 4, move(d));

    EXPECT_EQ(m.GetNumRows(), 3);
    EXPECT_EQ(m.GetNumCols(), 4);
    EXPECT_EQ(m.At(0, 0), 1.0);
    EXPECT_EQ(m.At(1, 0), 5.0);
    EXPECT_EQ(m.At(2, 0), 9.0);
    EXPECT_EQ(m.At(0, 1), 2.0);
    EXPECT_EQ(m.At(1, 1), 6.0);
    EXPECT_EQ(m.At(2, 1), 10.0);
    EXPECT_EQ(m.At(0, 2), 3.0);
    EXPECT_EQ(m.At(1, 2), 7.0);
    EXPECT_EQ(m.At(2, 2), 11.0);
    EXPECT_EQ(m.At(0, 3), 4.0);
    EXPECT_EQ(m.At(1, 3), 8.0);
    EXPECT_EQ(m.At(2, 3), 12.0);
    EXPECT_THROW(m.At(5, 5), std::exception);
}

TEST(MatrixTest, OutOfBounds)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m(3, 4, move(d));

    EXPECT_THROW(m.At(5, 0), std::exception);
    EXPECT_THROW(m.At(0, 5), std::exception);
    EXPECT_THROW(m.At(5, 5), std::exception);
}

TEST(MatrixTest, CopyConstructor)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d));
    Matrix2<double> m2(m1);

    EXPECT_EQ(m1.GetNumRows(), 3);
    EXPECT_EQ(m1.GetNumCols(), 4);
    EXPECT_EQ(m1.At(0, 0), 1.0);
    EXPECT_EQ(m1.At(1, 0), 5.0);
    EXPECT_EQ(m1.At(2, 0), 9.0);
    EXPECT_EQ(m1.At(0, 1), 2.0);
    EXPECT_EQ(m1.At(1, 1), 6.0);
    EXPECT_EQ(m1.At(2, 1), 10.0);
    EXPECT_EQ(m1.At(0, 2), 3.0);
    EXPECT_EQ(m1.At(1, 2), 7.0);
    EXPECT_EQ(m1.At(2, 2), 11.0);
    EXPECT_EQ(m1.At(0, 3), 4.0);
    EXPECT_EQ(m1.At(1, 3), 8.0);
    EXPECT_EQ(m1.At(2, 3), 12.0);

    EXPECT_EQ(m2.GetNumRows(), 3);
    EXPECT_EQ(m2.GetNumCols(), 4);
    EXPECT_EQ(m2.At(0, 0), 1.0);
    EXPECT_EQ(m2.At(1, 0), 5.0);
    EXPECT_EQ(m2.At(2, 0), 9.0);
    EXPECT_EQ(m2.At(0, 1), 2.0);
    EXPECT_EQ(m2.At(1, 1), 6.0);
    EXPECT_EQ(m2.At(2, 1), 10.0);
    EXPECT_EQ(m2.At(0, 2), 3.0);
    EXPECT_EQ(m2.At(1, 2), 7.0);
    EXPECT_EQ(m2.At(2, 2), 11.0);
    EXPECT_EQ(m2.At(0, 3), 4.0);
    EXPECT_EQ(m2.At(1, 3), 8.0);
    EXPECT_EQ(m2.At(2, 3), 12.0);
}


TEST(MatrixTest, MoveConstructor)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, d);
    Matrix2<double> m2(std::move(m1));

    EXPECT_EQ(m1.GetNumRows(), 3);
    EXPECT_EQ(m1.GetNumCols(), 4);

    EXPECT_EQ(m2.GetNumRows(), 3);
    EXPECT_EQ(m2.GetNumCols(), 4);
    EXPECT_EQ(m2.At(0, 0), 1.0);
    EXPECT_EQ(m2.At(1, 0), 5.0);
    EXPECT_EQ(m2.At(2, 0), 9.0);
    EXPECT_EQ(m2.At(0, 1), 2.0);
    EXPECT_EQ(m2.At(1, 1), 6.0);
    EXPECT_EQ(m2.At(2, 1), 10.0);
    EXPECT_EQ(m2.At(0, 2), 3.0);
    EXPECT_EQ(m2.At(1, 2), 7.0);
    EXPECT_EQ(m2.At(2, 2), 11.0);
    EXPECT_EQ(m2.At(0, 3), 4.0);
    EXPECT_EQ(m2.At(1, 3), 8.0);
    EXPECT_EQ(m2.At(2, 3), 12.0);
}

TEST(MatrixTest, CopyAssignment)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d1));
    std::vector<double> d2{ 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> m2(4, 3, move(d2));

    m1 = m2;

    EXPECT_EQ(m1, m2);
}

TEST(MatrixTest, MoveAssignment)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> m1(4, 3, move(d1));
    {
        std::vector<double> d2{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
        Matrix2<double> m2(3, 4, move(d2));

        m1 = std::move(m2);
    }

    EXPECT_EQ(m1.GetNumRows(), 3);
    EXPECT_EQ(m1.GetNumCols(), 4);
    EXPECT_EQ(m1.At(0, 0), 1.0);
    EXPECT_EQ(m1.At(0, 1), 2.0);
    EXPECT_EQ(m1.At(0, 2), 3.0);
    EXPECT_EQ(m1.At(0, 3), 4.0);
    EXPECT_EQ(m1.At(1, 0), 5.0);
    EXPECT_EQ(m1.At(1, 1), 6.0);
    EXPECT_EQ(m1.At(1, 2), 7.0);
    EXPECT_EQ(m1.At(1, 3), 8.0);
    EXPECT_EQ(m1.At(2, 0), 9.0);
    EXPECT_EQ(m1.At(2, 1), 10.0);
    EXPECT_EQ(m1.At(2, 2), 11.0);
    EXPECT_EQ(m1.At(2, 3), 12.0);
}

TEST(MatrixTest, Equality)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d1));
    std::vector<double> d2{ 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> m2(4, 3, move(d2));
    Matrix2<double> m3(m1);

    EXPECT_NE(m1, m2);
    EXPECT_NE(m2, m1);
    EXPECT_EQ(m1, m3);
    EXPECT_EQ(m3, m1);
}

TEST(MatrixTest, Multiplication)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d1));
    std::vector<double> d2{ 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> m2(4, 3, move(d2));
    std::vector<double> d3{ 10.0,  20.0,  30.0, 26.0, 52.0, 78.0, 42.0, 84.0, 126.0 };
    Matrix2<double> m3(3, 3, move(d3));
    std::vector<double> d4{ 38.0,  44.0,  50.0, 56.0, 38.0,  44.0,  50.0, 56.0, 38.0, 44.0,  50.0, 56.0, 38.0,  44.0,  50.0, 56.0, };
    Matrix2<double> m4(4, 4, move(d4));

    EXPECT_EQ(m3, m1 * m2);
    EXPECT_EQ(m4, m2 * m1);

    std::vector<double> columnData{ 1.5, 2.5, 3.5 };
    std::vector<double> squareData{ 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
    Matrix2<double> testColumn(3, 1, move(columnData));
    Matrix2<double> squareMatrix(3, 3, move(squareData));

    std::vector<double> d5{ 0.0 };
    Matrix2<double> m5(1, 1, move(d5));
    EXPECT_EQ(m5, testColumn * squareMatrix);
    EXPECT_EQ(testColumn, squareMatrix * testColumn);

    std::vector<double> d6{ 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0 };
    Matrix2<double> m6(3, 3, move(d6));
    EXPECT_EQ(m6, squareMatrix + 1.0);

    std::vector<double> d7{ 9.0, 10.0, 11.0 };
    Matrix2<double> m7(3, 1, move(d7));
    EXPECT_EQ(m7, m6 * testColumn);
}

TEST(MatrixTest, AdditionByScalar)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d1));
    std::vector<double> d2{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0 };
    Matrix2<double> m2(3, 4, move(d2));
    EXPECT_EQ(m2, m1 + 2.0);
    EXPECT_EQ(m2, 2.0 + m1);
}

TEST(MatrixTest, SubtractionByScalar)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d1));
    std::vector<double> d2{ -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    Matrix2<double> m2(3, 4, move(d2));
    std::vector<double> d3{ 1.0, 0.0, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0 };
    Matrix2<double> m3(3, 4, move(d3));
    EXPECT_EQ(m2, m1 - 2.0);
    EXPECT_EQ(m3, 2.0 - m1);
}

TEST(MatrixTest, MultiplicationByScalar)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d1));
    std::vector<double> d2{ 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0 };
    Matrix2<double> m2(3, 4, move(d2));
    EXPECT_EQ(m2, m1 * 2.0);
    EXPECT_EQ(m2, 2.0 * m1);
}

TEST(MatrixTest, Identity)
{
    Matrix2<double> m1(3, 3);
    m1.SetToIdentity();
    EXPECT_EQ(m1.At(0, 0), 1.0);
    EXPECT_EQ(m1.At(1, 0), 0.0);
    EXPECT_EQ(m1.At(2, 0), 0.0);
    EXPECT_EQ(m1.At(0, 1), 0.0);
    EXPECT_EQ(m1.At(1, 1), 1.0);
    EXPECT_EQ(m1.At(2, 1), 0.0);
    EXPECT_EQ(m1.At(0, 2), 0.0);
    EXPECT_EQ(m1.At(1, 2), 0.0);
    EXPECT_EQ(m1.At(2, 2), 1.0);

    Matrix2<double> m2(3, 4);
    EXPECT_THROW(m2.SetToIdentity(), std::invalid_argument);

    Matrix2<double> m3(4, 3);
    EXPECT_THROW(m3.SetToIdentity(), std::invalid_argument);
}

TEST(MatrixTest, Compare)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::vector<double> d2{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::vector<double> d3{ 1.0, 2.0, 3.0, 4.0, 1.0, 6.0, 7.0, 8.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    Matrix2<double> m2(3, 3, move(d2));
    Matrix2<double> m3(3, 3, move(d3));

    EXPECT_TRUE(m1.Compare(m2, 0.001));
    EXPECT_FALSE(m1.Compare(m3, 0.001));

    // TBD
}

TEST(MatrixTest, Separate)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 8.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    Matrix2<double> m2;
    Matrix2<double> m3;
    m1.Separate(m2, m3, 2);
    EXPECT_EQ(m2.At(0, 0), 1.0);
    EXPECT_EQ(m2.At(1, 0), 4.0);
    EXPECT_EQ(m2.At(2, 0), 7.0);
    EXPECT_EQ(m2.At(0, 1), 2.0);
    EXPECT_EQ(m2.At(1, 1), 5.0);
    EXPECT_EQ(m2.At(2, 1), 8.0);
    EXPECT_EQ(m3.At(0, 0), 3.0);
    EXPECT_EQ(m3.At(1, 0), 6.0);
    EXPECT_EQ(m3.At(2, 0), 9.0);
    EXPECT_THROW(m1.Separate(m2, m3, 4), std::invalid_argument);
}

TEST(MatrixTest, Join)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 8.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    Matrix2<double> m2;
    Matrix2<double> m3;
    m1.Separate(m2, m3, 2);

    m2.Join(m3);

    EXPECT_EQ(m1, m2);
}

TEST(MatrixTest, SwapRows)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 8.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    m1.Swap(0, 2);

    EXPECT_EQ(m1.At(0, 0), 7.0);
    EXPECT_EQ(m1.At(0, 1), 8.0);
    EXPECT_EQ(m1.At(0, 2), 9.0);
    EXPECT_EQ(m1.At(1, 0), 4.0);
    EXPECT_EQ(m1.At(1, 1), 5.0);
    EXPECT_EQ(m1.At(1, 2), 6.0);
    EXPECT_EQ(m1.At(2, 0), 1.0);
    EXPECT_EQ(m1.At(2, 1), 2.0);
    EXPECT_EQ(m1.At(2, 2), 3.0);
}

TEST(MatrixTest, MultAdd)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 8.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    m1.MultAdd(2, 0, -7);

    EXPECT_EQ(m1.At(0, 0), 1.0);
    EXPECT_EQ(m1.At(0, 1), 2.0);
    EXPECT_EQ(m1.At(0, 2), 3.0);
    EXPECT_EQ(m1.At(1, 0), 4.0);
    EXPECT_EQ(m1.At(1, 1), 5.0);
    EXPECT_EQ(m1.At(1, 2), 6.0);
    EXPECT_EQ(m1.At(2, 0), 0.0);
    EXPECT_EQ(m1.At(2, 1), -6.0);
    EXPECT_EQ(m1.At(2, 2), -12.0);
    EXPECT_THROW(m1.MultAdd(3, 0, -7), std::invalid_argument);
    EXPECT_THROW(m1.MultAdd(9, 0, -7), std::invalid_argument);
    EXPECT_THROW(m1.MultAdd(2, 3, -7), std::invalid_argument);
    EXPECT_THROW(m1.MultAdd(2, 9, -7), std::invalid_argument);
}

TEST(MatrixTest, MultRow)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 8.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    m1.MultRow(2, 3);

    EXPECT_EQ(m1.At(0, 0), 1.0);
    EXPECT_EQ(m1.At(0, 1), 2.0);
    EXPECT_EQ(m1.At(0, 2), 3.0);
    EXPECT_EQ(m1.At(1, 0), 4.0);
    EXPECT_EQ(m1.At(1, 1), 5.0);
    EXPECT_EQ(m1.At(1, 2), 6.0);
    EXPECT_EQ(m1.At(2, 0), 21.0);
    EXPECT_EQ(m1.At(2, 1), 24.0);
    EXPECT_EQ(m1.At(2, 2), 27.0);
    EXPECT_THROW(m1.MultRow(3, 3), std::out_of_range);
    EXPECT_THROW(m1.MultRow(9, 3), std::out_of_range);
}

TEST(MatrixTest, FindRowWithMaxElement)
{
    std::vector<double> d1{ 1.0, 8.0, 3.0,
                            4.0, 5.0, 9.0,
                            7.0, 2.0, 6.0 };
    Matrix2<double> m1(3, 3, move(d1));

    EXPECT_EQ(m1.FindRowWithMaxElement(0, 0), 2);
    EXPECT_EQ(m1.FindRowWithMaxElement(1, 1), 1);
    EXPECT_EQ(m1.FindRowWithMaxElement(2, 2), 2);
    EXPECT_THROW(m1.FindRowWithMaxElement(3, 1), std::out_of_range);
    EXPECT_THROW(m1.FindRowWithMaxElement(9, 1), std::out_of_range);
    EXPECT_THROW(m1.FindRowWithMaxElement(2, 3), std::out_of_range);
    EXPECT_THROW(m1.FindRowWithMaxElement(2, 9), std::out_of_range);
}

TEST(MatrixTest, Inverse)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 15.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    Matrix2<double> m2(m1);
    Matrix2<double> identityMatrix(3, 3);
    identityMatrix.SetToIdentity();

    m1.Inverse();
    auto m{ m1 * m2 };
    EXPECT_EQ(m, identityMatrix);
}

TEST(MatrixTest, FindSubMatrix)
{
    std::vector<double> d1{ 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0,
                            7.0, 15.0, 9.0 };
    Matrix2<double> m1(3, 3, move(d1));
    {
        Matrix2<double> m2{ m1.FindSubMatrix(0, 0) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 5);
        EXPECT_EQ(m2(0, 1), 6);
        EXPECT_EQ(m2(1, 0), 15);
        EXPECT_EQ(m2(1, 1), 9);
    }
    {
        Matrix2<double> m2{ m1.FindSubMatrix(0, 1) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 4);
        EXPECT_EQ(m2(0, 1), 6);
        EXPECT_EQ(m2(1, 0), 7);
        EXPECT_EQ(m2(1, 1), 9);
    }
    {
        Matrix2<double> m2{ m1.FindSubMatrix(0, 2) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 4);
        EXPECT_EQ(m2(0, 1), 5);
        EXPECT_EQ(m2(1, 0), 7);
        EXPECT_EQ(m2(1, 1), 15);
    }

    {
        Matrix2<double> m2{ m1.FindSubMatrix(1, 0) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 2);
        EXPECT_EQ(m2(0, 1), 3);
        EXPECT_EQ(m2(1, 0), 15);
        EXPECT_EQ(m2(1, 1), 9);
    }
    {
        Matrix2<double> m2{ m1.FindSubMatrix(1, 1) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 1);
        EXPECT_EQ(m2(0, 1), 3);
        EXPECT_EQ(m2(1, 0), 7);
        EXPECT_EQ(m2(1, 1), 9);
    }
    {
        Matrix2<double> m2{ m1.FindSubMatrix(1, 2) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 1);
        EXPECT_EQ(m2(0, 1), 2);
        EXPECT_EQ(m2(1, 0), 7);
        EXPECT_EQ(m2(1, 1), 15);
    }

    {
        Matrix2<double> m2{ m1.FindSubMatrix(2, 0) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 2);
        EXPECT_EQ(m2(0, 1), 3);
        EXPECT_EQ(m2(1, 0), 5);
        EXPECT_EQ(m2(1, 1), 6);
    }
    {
        Matrix2<double> m2{ m1.FindSubMatrix(2, 1) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 1);
        EXPECT_EQ(m2(0, 1), 3);
        EXPECT_EQ(m2(1, 0), 4);
        EXPECT_EQ(m2(1, 1), 6);
    }
    {
        Matrix2<double> m2{ m1.FindSubMatrix(2, 2) };

        EXPECT_EQ(m2.GetNumRows(), 2);
        EXPECT_EQ(m2.GetNumCols(), 2);
        EXPECT_EQ(m2(0, 0), 1);
        EXPECT_EQ(m2(0, 1), 2);
        EXPECT_EQ(m2(1, 0), 4);
        EXPECT_EQ(m2(1, 1), 5);
    }
}


TEST(MatrixTest, Determinat)
{
    {
        std::vector<double> d3{ 2.0, 1.0, 1.0,
                                1.0, 0.0, 1.0,
                                0.0, 3.0, 1.0 };
        Matrix2<double> m3(3, 3, move(d3));
        {
            Matrix2<double> m2{ m3.FindSubMatrix(0, 0) };
            EXPECT_EQ(m2.Determinant(), 0 * 1 - 1 * 3);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(0, 1) };
            EXPECT_EQ(m2.Determinant(), 1 * 1 - 1 * 0);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(0, 2) };
            EXPECT_EQ(m2.Determinant(), 1 * 3 - 0 * 0);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(1, 0) };
            EXPECT_EQ(m2.Determinant(), 1 * 1 - 1 * 3);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(1, 1) };
            EXPECT_EQ(m2.Determinant(), 2 * 1 - 1 * 0);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(1, 2) };
            EXPECT_EQ(m2.Determinant(), 2 * 3 - 1 * 0);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(2, 0) };
            EXPECT_EQ(m2.Determinant(), 1 * 1 - 1 * 0);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(2, 1) };
            EXPECT_EQ(m2.Determinant(), 2 * 1 - 1 * 1);
        }
        {
            Matrix2<double> m2{ m3.FindSubMatrix(2, 2) };
        }
        EXPECT_EQ(m3.Determinant(), -4);
    }
    {
        std::vector<double> d5{ 2.0, 3.0, 4.0, 5.0, 6.0,
                                1.0, 2.0, 3.0, 4.0, 5.0,
                                9.0, 5.0, 3.0, 2.0, 6.0,
                                2.0, 4.0, 6.0, 5.0, 1.0,
                                1.0, 7.0, 5.0, 2.0, 3.0 };
        Matrix2<double> m5(5, 5, move(d5));
        EXPECT_EQ(m5.Determinant(), -126);
    }
    {
        // Singular matrix
        std::vector<double> d3{ 1.0, 1.0, 1.0,
                                0.0, 1.0, 0.0,
                                1.0, 0.0, 1.0 };
        Matrix2<double> m3(3, 3, move(d3));
        EXPECT_EQ(m3.Determinant(), 0);
    }


}