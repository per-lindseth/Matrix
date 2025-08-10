#include "pch.h"
#include "../Main/Matrix.h"

using namespace Math;

TEST(MatrixTest, GetElement)
{
    double d[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m(3, 4, d);

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

TEST(MatrixTest, Equality)
{
    double d1[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, d1);
    double d2[12] = { 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> m2(4, 3, d2);
    Matrix2<double> m3(m1);

    EXPECT_NE(m1, m2);
    EXPECT_NE(m2, m1);
    EXPECT_EQ(m1, m3);
    EXPECT_EQ(m3, m1);
}

TEST(MatrixTest, Multiplication)
{
    double d1[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, d1);
    double d2[12] = { 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0 };
    Matrix2<double> m2(4, 3, d2);
    double d3[9] = { 10.0,  20.0,  30.0, 26.0, 52.0, 78.0, 42.0, 84.0, 126.0 };
    Matrix2<double> m3(3, 3, d3);
    double d4[16] = { 38.0,  44.0,  50.0, 56.0, 38.0,  44.0,  50.0, 56.0, 38.0, 44.0,  50.0, 56.0, 38.0,  44.0,  50.0, 56.0, };
    Matrix2<double> m4(4, 4, d4);

    EXPECT_EQ(m3, m1 * m2);
    EXPECT_EQ(m4, m2 * m1);

    double columnData[3] = { 1.5, 2.5, 3.5 };
    double squareData[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
    Matrix2<double> testColumn(3, 1, columnData);
    Matrix2<double> squareMatrix(3, 3, squareData);

    double d5[3] = { 0.0 };
    Matrix2<double> m5(1, 1, d5);
    EXPECT_EQ(m5, testColumn * squareMatrix);
    EXPECT_EQ(testColumn, squareMatrix * testColumn);

    double d6[9] = { 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0 };
    Matrix2<double> m6(3, 3, d6);
    EXPECT_EQ(m6, squareMatrix + 1.0);

    double d7[3] = { 9.0, 10.0, 11.0 };
    Matrix2<double> m7(3, 1, d7);
    EXPECT_EQ(m7, m6 * testColumn);
}

TEST(MatrixTest, AdditionByScalar)
{
    double d1[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, d1);
    double d2[12] = { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0 };
    Matrix2<double> m2(3, 4, d2);
    EXPECT_EQ(m2, m1 + 2.0);
    EXPECT_EQ(m2, 2.0 + m1);
}

TEST(MatrixTest, SubtractionByScalar)
{
    double d1[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, d1);
    double d2[12] = { -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    Matrix2<double> m2(3, 4, d2);
    double d3[12] = { 1.0, 0.0, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0 };
    Matrix2<double> m3(3, 4, d3);
    EXPECT_EQ(m2, m1 - 2.0);
    EXPECT_EQ(m3, 2.0 - m1);
}

TEST(MatrixTest, MultiplicationByScalar)
{
    double d1[12] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
    Matrix2<double> m1(3, 4, d1);
    double d2[12] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0 };
    Matrix2<double> m2(3, 4, d2);
    EXPECT_EQ(m2, m1 * 2.0);
    EXPECT_EQ(m2, 2.0 * m1);
}