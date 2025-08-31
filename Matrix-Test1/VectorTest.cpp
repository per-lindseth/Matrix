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

TEST(VectorTest, DataConstructor2) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(std::move(testData1));
    EXPECT_EQ(testData1.size(), 0);
    EXPECT_EQ(testVector1.GetELement(0), 1.0);
    EXPECT_EQ(testVector1.GetELement(1), 2.0);
    EXPECT_EQ(testVector1.GetELement(2), 3.0);
    EXPECT_THROW(testVector1.GetELement(3), std::out_of_range);
}

TEST(VectorTest, SetElement) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    Vector<double> testVector1(std::move(testData1));
    testVector1.SetElement(1, 20.0);
    EXPECT_EQ(testVector1.GetELement(0), 1.0);
    EXPECT_EQ(testVector1.GetELement(1), 20.0);
    EXPECT_EQ(testVector1.GetELement(2), 3.0);
}

TEST(VectorTest, Addition) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    Vector<double> testVector1(std::move(testData1));
    const Vector<double> testVector2(std::move(testData2));
    const auto testVector3{ testVector1 + testVector2 };
    EXPECT_EQ(testVector3.GetELement(0), 3.0);
    EXPECT_EQ(testVector3.GetELement(1), 6.0);
    EXPECT_EQ(testVector3.GetELement(2), 9.0);
    testVector1 += testVector2;
    EXPECT_EQ(testVector1.GetELement(0), 3.0);
    EXPECT_EQ(testVector1.GetELement(1), 6.0);
    EXPECT_EQ(testVector1.GetELement(2), 9.0);
}

TEST(VectorTest, Subtraction) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    Vector<double> testVector1(std::move(testData1));
    const Vector<double> testVector2(std::move(testData2));
    const auto testVector3{ testVector2 - testVector1 };
    EXPECT_EQ(testVector3.GetELement(0), 1.0);
    EXPECT_EQ(testVector3.GetELement(1), 2.0);
    EXPECT_EQ(testVector3.GetELement(2), 3.0);
    testVector1 -= testVector2;
    EXPECT_EQ(testVector3.GetELement(0), 1.0);
    EXPECT_EQ(testVector3.GetELement(1), 2.0);
    EXPECT_EQ(testVector3.GetELement(2), 3.0);
}

TEST(VectorTest, Multiplication) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    Vector<double> testVector1(std::move(testData1));

    const auto testVector3{ testVector1 * 2.0 };
    EXPECT_EQ(testVector3.GetELement(0), 2.0);
    EXPECT_EQ(testVector3.GetELement(1), 4.0);
    EXPECT_EQ(testVector3.GetELement(2), 6.0);

    const auto testVector4{ 2.0 * testVector1 };
    EXPECT_EQ(testVector4.GetELement(0), 2.0);
    EXPECT_EQ(testVector4.GetELement(1), 4.0);
    EXPECT_EQ(testVector4.GetELement(2), 6.0);

    testVector1 *= 2.0;
    EXPECT_EQ(testVector1.GetELement(0), 2.0);
    EXPECT_EQ(testVector1.GetELement(1), 4.0);
    EXPECT_EQ(testVector1.GetELement(2), 6.0);
}

TEST(VectorTest, Division) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    Vector<double> testVector1(std::move(testData1));

    const auto testVector2{ testVector1 / 2.0 };
    EXPECT_EQ(testVector2.GetELement(0), 0.5);
    EXPECT_EQ(testVector2.GetELement(1), 1.0);
    EXPECT_EQ(testVector2.GetELement(2), 1.5);

    const auto testVector3{ 2.0 / testVector1 };
    EXPECT_EQ(testVector3.GetELement(0), 0.5);
    EXPECT_EQ(testVector3.GetELement(1), 1.0);
    EXPECT_EQ(testVector3.GetELement(2), 1.5);

    testVector1 /= 2.0;
    EXPECT_EQ(testVector1.GetELement(0), 0.5);
    EXPECT_EQ(testVector1.GetELement(1), 1.0);
    EXPECT_EQ(testVector1.GetELement(2), 1.5);
}

TEST(VectorTest, DotProduct) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(std::move(testData1));

    std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector2(std::move(testData2));
    const auto dot1{ Vector<double>::Dot(testVector1, testVector2) };
    EXPECT_EQ(dot1, 28.0);

    std::vector<double> testData3{ -1.0, 5.0, -3.2 };
    const Vector<double> testVector3(std::move(testData3));
    const auto dot2{ Vector<double>::Dot(testVector1, testVector3) };
    EXPECT_TRUE(CloseEnough(dot2, -0.6));
}

TEST(VectorTest, CrossProduct) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    const Vector<double> testVector1(std::move(testData1));
    const Vector<double> testVector2(std::move(testData2));
    const auto testVector3{ Vector<double>::Cross(testVector1, testVector2) };
    EXPECT_EQ(testVector3.GetELement(0), 0.0);
    EXPECT_EQ(testVector3.GetELement(1), -0.0);
    EXPECT_EQ(testVector3.GetELement(2), 0.0);

    std::vector<double> testData4{ -1.0, 5.0, -3.2 };
    const Vector<double> testVector4(std::move(testData4));
    const auto testVector5{ Vector<double>::Cross(testVector1, testVector4) };
    EXPECT_TRUE(CloseEnough(testVector5.GetELement(0), -21.4));
    EXPECT_TRUE(CloseEnough(testVector5.GetELement(1), 0.2));
    EXPECT_TRUE(CloseEnough(testVector5.GetELement(2), 7.0));
}

TEST(VectorTest, Norm) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    const Vector<double> testVector1(std::move(testData1));
    EXPECT_TRUE(CloseEnough(testVector1.Norm(), sqrt(14.0)));
}

TEST(VectorTest, Normalize) {
    std::vector<double> testData1{ 1.0, 2.0, 3.0 };
    std::vector<double> testData2{ 2.0, 4.0, 6.0 };
    std::vector<double> testData3{ -1.0, 5.0, -3.2 };
    const Vector<double> testVector1(std::move(testData1));
    const Vector<double> testVector2(std::move(testData2));
    const Vector<double> testVector3(std::move(testData3));
    EXPECT_TRUE(CloseEnough(testVector1.Norm(), 3.7416573867739413));
    EXPECT_TRUE(CloseEnough(testVector2.Norm(), 7.4833147735478827));
    EXPECT_TRUE(CloseEnough(testVector3.Norm(), 6.0199667773169647));

    const Vector<double> normalizedVector1{ testVector1.Normalized() };
    const Vector<double> normalizedVector2{ testVector2.Normalized() };
    const Vector<double> normalizedVector3{ testVector3.Normalized() };

    EXPECT_TRUE(CloseEnough(normalizedVector1.GetELement(0), 0.26726124191242440));
    EXPECT_TRUE(CloseEnough(normalizedVector1.GetELement(1), 0.53452248382484879));
    EXPECT_TRUE(CloseEnough(normalizedVector1.GetELement(2), 0.80178372573727319));

    EXPECT_TRUE(CloseEnough(normalizedVector2.GetELement(0), 0.26726124191242440));
    EXPECT_TRUE(CloseEnough(normalizedVector2.GetELement(1), 0.53452248382484879));
    EXPECT_TRUE(CloseEnough(normalizedVector2.GetELement(2), 0.80178372573727319));

    EXPECT_TRUE(CloseEnough(normalizedVector3.GetELement(0), -0.16611387354627385));
    EXPECT_TRUE(CloseEnough(normalizedVector3.GetELement(1), 0.83056936773136925));
    EXPECT_TRUE(CloseEnough(normalizedVector3.GetELement(2), -0.53156439534807631));
}