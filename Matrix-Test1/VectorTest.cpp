#include "pch.h"
#include "../Main/Vector.h"

using namespace Math;

bool CloseEnough(const double f1, const double f2)
{
    return fabs(f1 - f2) < 1e-9;
}

TEST(VectorTest, DefaultConstructor) {
    Vector<double> m;
    EXPECT_EQ(m.GetNumDims(), 0);
}

TEST(VectorTest, DataConstructor) {
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(testData1);
    EXPECT_EQ(testVector1.GetELement(0), 1.0);
    EXPECT_EQ(testVector1.GetELement(1), 2.0);
    EXPECT_EQ(testVector1.GetELement(2), 3.0);
    EXPECT_THROW(testVector1.GetELement(3), std::out_of_range);
}

TEST(VectorTest, Addition) {
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector1(testData1);
    const Vector<double> testVector2(testData2);
    const auto testVector3{ testVector1 + testVector2 };
    EXPECT_EQ(testVector3.GetELement(0), 3.0);
    EXPECT_EQ(testVector3.GetELement(1), 6.0);
    EXPECT_EQ(testVector3.GetELement(2), 9.0);
}

TEST(VectorTest, Subtraction) {
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector1(testData1);
    const Vector<double> testVector2(testData2);
    const auto testVector3{ testVector2 - testVector1 };
    EXPECT_EQ(testVector3.GetELement(0), 1.0);
    EXPECT_EQ(testVector3.GetELement(1), 2.0);
    EXPECT_EQ(testVector3.GetELement(2), 3.0);
}

TEST(VectorTest, Multiplication) {
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(testData1);

    const auto testVector3{ testVector1 * 2.0 };
    EXPECT_EQ(testVector3.GetELement(0), 2.0);
    EXPECT_EQ(testVector3.GetELement(1), 4.0);
    EXPECT_EQ(testVector3.GetELement(2), 6.0);

    const auto testVector4{ 2.0 * testVector1 };
    EXPECT_EQ(testVector4.GetELement(0), 2.0);
    EXPECT_EQ(testVector4.GetELement(1), 4.0);
    EXPECT_EQ(testVector4.GetELement(2), 6.0);
}

TEST(VectorTest, DotProduct) {
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(testData1);

    const std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector2(testData2);
    const auto dot1{ Vector<double>::Dot(testVector1, testVector2) };
    EXPECT_EQ(dot1, 28.0);

    const std::vector<double> testData3{ -1.0, 5.0, -3.2 };
    const Vector<double> testVector3(testData3);
    const auto dot2{ Vector<double>::Dot(testVector1, testVector3) };
    EXPECT_TRUE(CloseEnough(dot2, -0.6));
}

TEST(VectorTest, CrossProduct) {
    const std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector1(testData1);
    const Vector<double> testVector2(testData2);
    const auto testVector3{ Vector<double>::Cross(testVector1, testVector2) };
    EXPECT_EQ(testVector3.GetELement(0), 0.0);
    EXPECT_EQ(testVector3.GetELement(1), -0.0);
    EXPECT_EQ(testVector3.GetELement(2), 0.0);

    const std::vector<double> testData4{ -1.0, 5.0, -3.2 };
    const Vector<double> testVector4(testData4);
    const auto testVector5{ Vector<double>::Cross(testVector1, testVector4) };
    EXPECT_TRUE(CloseEnough(testVector5.GetELement(0), -21.4));
    EXPECT_TRUE(CloseEnough(testVector5.GetELement(1), 0.2));
    EXPECT_TRUE(CloseEnough(testVector5.GetELement(2), 7.0));
}