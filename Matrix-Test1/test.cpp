#include "pch.h"
#include "../Main/Matrix.h"

using namespace Math;

TEST(MatrixTest, DefaultConstructor)
{
    Matrix2<double> m;
    EXPECT_EQ(m.GetNumRows(), 1);
    EXPECT_EQ(m.GetNumCols(), 1);
    EXPECT_EQ(m.GetElement(0, 0), 0.0);
}

TEST(MatrixTest, ZeroConstructor)
{
    Matrix2<double> m(2, 3);
    EXPECT_EQ(m.GetNumRows(), 2);
    EXPECT_EQ(m.GetNumCols(), 3);
    EXPECT_EQ(m.GetElement(0, 0), 0.0);
    EXPECT_EQ(m.GetElement(1, 0), 0.0);
    EXPECT_EQ(m.GetElement(0, 1), 0.0);
    EXPECT_EQ(m.GetElement(1, 1), 0.0);
    EXPECT_EQ(m.GetElement(0, 2), 0.0);
    EXPECT_EQ(m.GetElement(1, 2), 0.0);
}

TEST(MatrixTest, DataConstructor)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m(3, 4, move(d));

    EXPECT_EQ(m.GetNumRows(), 3);
    EXPECT_EQ(m.GetNumCols(), 4);
    EXPECT_EQ(m.GetElement(0, 0), 1.0);
    EXPECT_EQ(m.GetElement(1, 0), 5.0);
    EXPECT_EQ(m.GetElement(2, 0), 9.0);
    EXPECT_EQ(m.GetElement(0, 1), 2.0);
    EXPECT_EQ(m.GetElement(1, 1), 6.0);
    EXPECT_EQ(m.GetElement(2, 1), 10.0);
    EXPECT_EQ(m.GetElement(0, 2), 3.0);
    EXPECT_EQ(m.GetElement(1, 2), 7.0);
    EXPECT_EQ(m.GetElement(2, 2), 11.0);
    EXPECT_EQ(m.GetElement(0, 3), 4.0);
    EXPECT_EQ(m.GetElement(1, 3), 8.0);
    EXPECT_EQ(m.GetElement(2, 3), 12.0);
    EXPECT_THROW(m.GetElement(5, 5), std::exception);
}

TEST(MatrixTest, OutOfBounds)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m(3, 4, move(d));

    EXPECT_THROW(m.GetElement(5, 0), std::exception);
    EXPECT_THROW(m.GetElement(0, 5), std::exception);
    EXPECT_THROW(m.GetElement(5, 5), std::exception);
}

TEST(MatrixTest, CopyConstructor)
{
    std::vector<double> d{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, move(d));
    Matrix2<double> m2(m1);

    EXPECT_EQ(m1.GetNumRows(), 3);
    EXPECT_EQ(m1.GetNumCols(), 4);
    EXPECT_EQ(m1.GetElement(0, 0), 1.0);
    EXPECT_EQ(m1.GetElement(1, 0), 5.0);
    EXPECT_EQ(m1.GetElement(2, 0), 9.0);
    EXPECT_EQ(m1.GetElement(0, 1), 2.0);
    EXPECT_EQ(m1.GetElement(1, 1), 6.0);
    EXPECT_EQ(m1.GetElement(2, 1), 10.0);
    EXPECT_EQ(m1.GetElement(0, 2), 3.0);
    EXPECT_EQ(m1.GetElement(1, 2), 7.0);
    EXPECT_EQ(m1.GetElement(2, 2), 11.0);
    EXPECT_EQ(m1.GetElement(0, 3), 4.0);
    EXPECT_EQ(m1.GetElement(1, 3), 8.0);
    EXPECT_EQ(m1.GetElement(2, 3), 12.0);

    EXPECT_EQ(m2.GetNumRows(), 3);
    EXPECT_EQ(m2.GetNumCols(), 4);
    EXPECT_EQ(m2.GetElement(0, 0), 1.0);
    EXPECT_EQ(m2.GetElement(1, 0), 5.0);
    EXPECT_EQ(m2.GetElement(2, 0), 9.0);
    EXPECT_EQ(m2.GetElement(0, 1), 2.0);
    EXPECT_EQ(m2.GetElement(1, 1), 6.0);
    EXPECT_EQ(m2.GetElement(2, 1), 10.0);
    EXPECT_EQ(m2.GetElement(0, 2), 3.0);
    EXPECT_EQ(m2.GetElement(1, 2), 7.0);
    EXPECT_EQ(m2.GetElement(2, 2), 11.0);
    EXPECT_EQ(m2.GetElement(0, 3), 4.0);
    EXPECT_EQ(m2.GetElement(1, 3), 8.0);
    EXPECT_EQ(m2.GetElement(2, 3), 12.0);
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
    EXPECT_EQ(m2.GetElement(0, 0), 1.0);
    EXPECT_EQ(m2.GetElement(1, 0), 5.0);
    EXPECT_EQ(m2.GetElement(2, 0), 9.0);
    EXPECT_EQ(m2.GetElement(0, 1), 2.0);
    EXPECT_EQ(m2.GetElement(1, 1), 6.0);
    EXPECT_EQ(m2.GetElement(2, 1), 10.0);
    EXPECT_EQ(m2.GetElement(0, 2), 3.0);
    EXPECT_EQ(m2.GetElement(1, 2), 7.0);
    EXPECT_EQ(m2.GetElement(2, 2), 11.0);
    EXPECT_EQ(m2.GetElement(0, 3), 4.0);
    EXPECT_EQ(m2.GetElement(1, 3), 8.0);
    EXPECT_EQ(m2.GetElement(2, 3), 12.0);
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
    EXPECT_EQ(m1.GetElement(0, 0), 1.0);
    EXPECT_EQ(m1.GetElement(0, 1), 2.0);
    EXPECT_EQ(m1.GetElement(0, 2), 3.0);
    EXPECT_EQ(m1.GetElement(0, 3), 4.0);
    EXPECT_EQ(m1.GetElement(1, 0), 5.0);
    EXPECT_EQ(m1.GetElement(1, 1), 6.0);
    EXPECT_EQ(m1.GetElement(1, 2), 7.0);
    EXPECT_EQ(m1.GetElement(1, 3), 8.0);
    EXPECT_EQ(m1.GetElement(2, 0), 9.0);
    EXPECT_EQ(m1.GetElement(2, 1), 10.0);
    EXPECT_EQ(m1.GetElement(2, 2), 11.0);
    EXPECT_EQ(m1.GetElement(2, 3), 12.0);
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