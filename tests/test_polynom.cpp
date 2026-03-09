// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <sstream>
#include "libs/lib_polynom/polynom.h"

#define EPSILON 0.000001

TEST(TestMonom, default_init) {
    Monom monom;

    std::ostringstream oss;
    oss << monom;
    EXPECT_EQ(oss.str(), "(0 * x^0 * y^0 * z^0)");

    EXPECT_DOUBLE_EQ(monom.calculate(1.0, 1.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(monom.calculate(5.5, -2.1, 3.14), 0.0);

    int zeros[3] = {0, 0, 0};
    Monom explicit_zero(0.0, zeros);
    EXPECT_TRUE(monom == explicit_zero);
}

TEST(TestMonom, SuccessfulInitAndDeepCopy) {
    int powers[3] = {1, 2, 3};
    Monom monom_1(5, powers);
    Monom monom_2(monom_1);
    Monom monom_3;
    monom_3 = monom_2;

    EXPECT_TRUE(monom_1 == monom_2);

    monom_3 *= 2.0;
    EXPECT_TRUE(monom_3 == monom_2);
    EXPECT_DOUBLE_EQ(monom_3.calculate(1, 1, 1), 10.0);
    EXPECT_DOUBLE_EQ(monom_2.calculate(1, 1, 1), 5.0);

    monom_2 *= monom_1;

    EXPECT_TRUE(monom_3 != monom_2);
    EXPECT_DOUBLE_EQ(monom_2.calculate(1, 1, 1),  25.0);
}

TEST(TestMonom, SelfAssignment) {
    int p[3] = {1, 1, 1};
    Monom m(5.0, p);

    m = m;

    EXPECT_DOUBLE_EQ(m.calculate(1, 1, 1), 5.0);
    EXPECT_TRUE(m == Monom(5.0, p));
}

TEST(TestMonom, SelfAssignmentRobustness) {
    int p[3] = {1, 2, 3};
    Monom m(5.0, p);

    Monom backup(m);

    m = m;

    EXPECT_TRUE(m == backup);
    EXPECT_DOUBLE_EQ(m.calculate(1, 1, 1), 5.0);
}

TEST(TestMonom, InitWithNullptr) {
    Monom m(10.0, nullptr);

    int zeros[3] = {0, 0, 0};
    Monom expected_zero_powers(10.0, zeros);

    EXPECT_TRUE(m == expected_zero_powers);
    EXPECT_DOUBLE_EQ(m.calculate(5, 5, 5), 10.0);
}

TEST(TestMonom, ZeroCoefficient) {
    Monom m(0.0, nullptr);

    EXPECT_DOUBLE_EQ(m.calculate(1, 2, 3), 0.0);
    EXPECT_DOUBLE_EQ(m.calculate(100, 100, 100), 0.0);
}

TEST(TestMonom, ThrowsOnNegativePowersInConstructor) {
    int bad_powers[3] = {1, -1, 2};

    EXPECT_THROW(Monom m(5.0, bad_powers), std::out_of_range);
}

TEST(TestMonom, AddAndSubSimilarMonomes) {
    int p[3] = {2, 1, 0};
    Monom m1(5.0, p);
    Monom m2(3.0, p);

    Monom result_plus = m1 + m2;
    Monom result_minus = m1 - m2;
    m1 += m2;

    EXPECT_DOUBLE_EQ(result_plus.calculate(1, 1, 1), 8.0);
    EXPECT_DOUBLE_EQ(result_minus.calculate(1, 1, 1), 2.0);
    EXPECT_DOUBLE_EQ(m1.calculate(1, 1, 1), 8.0);
    EXPECT_TRUE(result_plus == m1);
    EXPECT_TRUE(result_minus == m1);

    Monom m_assign_plus(5.0, p);
    m_assign_plus += m2;
    EXPECT_DOUBLE_EQ(m_assign_plus.calculate(1, 1, 1), 8.0);

    Monom m_assign_minus(5.0, p);
    m_assign_minus -= m2;
    EXPECT_DOUBLE_EQ(m_assign_minus.calculate(1, 1, 1), 2.0);

    EXPECT_TRUE(m_assign_minus == m1);
    EXPECT_TRUE(m_assign_plus == m1);
}

TEST(TestMonom, SubSimilarMonomesReturnZero) {
    int p[3] = {2, 1, 0};
    Monom m1(5.0, p);
    Monom m2(5.0, p);

    Monom result = m1 - m2;

    EXPECT_DOUBLE_EQ(result.calculate(1, 1, 1), 0.0);
}

TEST(TestMonom, AddAndSubSimilarMonomesWithNegativeCoeffs) {
    int p[3] = {2, 1, 0};
    Monom m1(-2.5, p);
    Monom m2(-1.5, p);

    Monom result_add = m1 + m2;
    Monom result_sub = m1 - m2;

    EXPECT_DOUBLE_EQ(result_add.calculate(1, 1, 1), -4.0);
    EXPECT_DOUBLE_EQ(result_sub.calculate(1, 1, 1), -1.0);

    Monom m_assign_plus = m1;
    m_assign_plus += m2;
    EXPECT_DOUBLE_EQ(m_assign_plus.calculate(1, 1, 1), -4.0);

    Monom m_assign_minus = m1;
    m_assign_minus -= m2;
    EXPECT_DOUBLE_EQ(m_assign_minus.calculate(1, 1, 1), -1.0);
}

TEST(TestMonom, AddAndSubMonomeWithZeroMonom) {
    int p[3] = {2, 1, 0};
    Monom m1(5.0, p);
    Monom m2(0.0, p);

    Monom result_add = m1 + m2;
    Monom result_sub = m1 - m2;

    EXPECT_DOUBLE_EQ(result_add.calculate(1, 1, 1), 5.0);
    EXPECT_DOUBLE_EQ(result_sub.calculate(1, 1, 1), 5.0);

    Monom m_assign_plus = m1;
    m_assign_plus += m2;
    EXPECT_DOUBLE_EQ(m_assign_plus.calculate(1, 1, 1), 5.0);

    Monom m_assign_minus = m1;
    m_assign_minus -= m2;
    EXPECT_DOUBLE_EQ(m_assign_minus.calculate(1, 1, 1), 5.0);
}

TEST(TestMonom, AddAndSubNonSimilarMonomesThrowException) {
    int p1[3] = {2, 1, 0};
    int p2[3] = {2, 3, 0};
    Monom m1(5.0, p1);
    Monom m2(3.0, p2);

    EXPECT_THROW(m1 + m2, std::invalid_argument);
    EXPECT_THROW(m1 - m2, std::invalid_argument);
    EXPECT_THROW(m1 += m2, std::invalid_argument);
    EXPECT_THROW(m1 -= m2, std::invalid_argument);
}

TEST(TestMonom, MultMonomes) {
    int p1[3] = {2, 1, 0};
    int p2[3] = {1, 0, 2};
    Monom m1(2.0, p1);
    Monom m2(3.0, p2);

    Monom mult_result = m1 * m2;

    int p3[3] = {3, 1, 2};

    EXPECT_TRUE(mult_result == Monom(6.0, p3));
    EXPECT_DOUBLE_EQ(mult_result.calculate(1, 1, 1), 6.0);

    Monom assign_mult_result = m1;
    assign_mult_result *= m2;

    EXPECT_TRUE(assign_mult_result == Monom(6.0, p3));
    EXPECT_DOUBLE_EQ(assign_mult_result.calculate(1, 1, 1), 6.0);
}

TEST(TestMonom, DivMonomes) {
    int p1[3] = {3, 2, 1};
    int p2[3] = {1, 1, 1};
    Monom m1(6.0, p1);
    Monom m2(3.0, p2);

    Monom div_result = m1 / m2;

    int p3[3] = {2, 1, 0};

    EXPECT_TRUE(div_result == Monom(2.0, p3));
    EXPECT_DOUBLE_EQ(div_result.calculate(1, 1, 1), 2.0);

    Monom assign_div_result = m1;
    assign_div_result /= m2;

    EXPECT_TRUE(assign_div_result == Monom(2.0, p3));
    EXPECT_DOUBLE_EQ(assign_div_result.calculate(1, 1, 1), 2.0);
}

TEST(TestMonom, MultMonomByZeroCoeffMonom) {
    int p1[3] = {2, 1, 0};
    int p2[3] = {1, 0, 2};
    Monom m1(2.0, p1);
    Monom m2(0.0, p2);

    Monom mult_result = m1 * m2;

    int p3[3] = {3, 1, 2};

    EXPECT_TRUE(mult_result == Monom(0.0, p3));
    EXPECT_DOUBLE_EQ(mult_result.calculate(2, 2, 2), 0.0);

    Monom assign_mult_result = m1;
    assign_mult_result *= m2;

    EXPECT_TRUE(assign_mult_result == Monom(0.0, p3));
    EXPECT_DOUBLE_EQ(assign_mult_result.calculate(2, 2, 2), 0.0);
}

TEST(TestMonom, DivMonomesWithZeroPowersResult) {
    int p1[3] = {3, 2, 1};
    int p2[3] = {3, 2, 1};
    Monom m1(6.0, p1);
    Monom m2(3.0, p2);

    Monom div_result = m1 / m2;

    int p3[3] = {0, 0, 0};

    EXPECT_TRUE(div_result == Monom(2.0, p3));
    EXPECT_DOUBLE_EQ(div_result.calculate(1, 1, 1), 2.0);

    Monom assign_div_result = m1;
    assign_div_result /= m2;

    EXPECT_TRUE(assign_div_result == Monom(2.0, p3));
    EXPECT_DOUBLE_EQ(assign_div_result.calculate(1, 1, 1), 2.0);
}

TEST(TestMonom, MultAndDivMonomBySingleMonom) {
    int p1[3] = {3, 2, 1};
    int p2[3] = {0, 0, 0};
    Monom m1(6.0, p1);
    Monom m2(1.0, p2);

    Monom mult_result = m1 * m2;

    EXPECT_TRUE(mult_result == m1);
    EXPECT_DOUBLE_EQ(mult_result.calculate(1, 1, 1), 6.0);

    Monom assign_mult_result = m1;
    assign_mult_result *= m2;

    EXPECT_TRUE(assign_mult_result == m1);
    EXPECT_DOUBLE_EQ(assign_mult_result.calculate(1, 1, 1), 6.0);

    Monom div_result = m1 / m2;

    EXPECT_TRUE(div_result == m1);
    EXPECT_DOUBLE_EQ(div_result.calculate(1, 1, 1), 6.0);

    Monom assign_div_result = m1;
    assign_div_result /= m2;

    EXPECT_TRUE(assign_div_result == m1);
    EXPECT_DOUBLE_EQ(assign_div_result.calculate(1, 1, 1), 6.0);
}

TEST(TestMonom, DivisionByMonomWithZeroCoef) {
    int p1[3] = {2, 1, 0};
    int p2[3] = {1, 1, 0};
    Monom m1(10.0, p1);
    Monom m2(0.0, p2);

    EXPECT_THROW(m1 / m2, std::invalid_argument);
    EXPECT_THROW(m1 /= m2, std::invalid_argument);
}

TEST(TestMonom, DivisionAtomicityByMonomWithGreatherPowers) {
    int p1[3] = {2, 1, 0};
    int p2[3] = {1, 3, 0};
    Monom m1(10.0, p1);
    Monom m2(2.0, p2);

    EXPECT_THROW(m1 / m2, std::out_of_range);
    EXPECT_THROW(m1 /= m2, std::out_of_range);
    EXPECT_DOUBLE_EQ(m1.calculate(1, 1, 1), 10.0);

    int expected_powers[3] = {2, 1, 0};
    EXPECT_TRUE(m1 == Monom(10.0, expected_powers));
}

TEST(TestMonom, ScalarMultAndDiv) {
    int p1[3] = {2, 1, 0};
    Monom m1(10.0, p1);

    Monom mult_result = m1 * 2.0;
    Monom div_result = m1 / 2.0;

    EXPECT_DOUBLE_EQ(mult_result.calculate(1, 1, 1), 20.0);
    EXPECT_DOUBLE_EQ(div_result.calculate(1, 1, 1), 5.0);

    Monom assign_mult_result = m1;
    assign_mult_result *= 2.0;
    Monom assign_div_result = m1;
    assign_div_result /= 2.0;

    EXPECT_DOUBLE_EQ(assign_mult_result.calculate(1, 1, 1), 20.0);
    EXPECT_DOUBLE_EQ(assign_div_result.calculate(1, 1, 1), 5.0);
    EXPECT_TRUE(mult_result == m1);
    EXPECT_TRUE(div_result == m1);
}

TEST(TestMonom, ScalarMultByZero) {
    int p1[3] = {2, 1, 0};
    Monom m1(10.0, p1);

    Monom mult_result = m1 * 0.0;
    EXPECT_DOUBLE_EQ(mult_result.calculate(2, 2, 2), 0.0);

    Monom assign_mult_result = m1;
    assign_mult_result *= 0.0;

    EXPECT_DOUBLE_EQ(assign_mult_result.calculate(2, 2, 2), 0.0);
    EXPECT_TRUE(mult_result == m1);
}

TEST(TestMonom, ScalarDivByZeroThrows) {
    int p1[3] = {2, 1, 0};
    Monom m1(10.0, p1);

    EXPECT_THROW(m1 / 0.0, std::invalid_argument);
    EXPECT_THROW(m1 /= 0.0, std::invalid_argument);
}

TEST(TestMonom, MonomCompareWithOtherByX) {
    int p1[3] = {2, 0, 0};
    int p2[3] = {1, 10, 10};
    Monom m1(0.1, p1);
    Monom m2(1000.0, p2);

    EXPECT_TRUE(m1 > m2);
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 < m2);
    EXPECT_FALSE(m1 == m2);
}

TEST(TestMonom, MonomCompareWithOtherByY) {
    int p1[3] = {10, 5, 0};
    int p2[3] = {10, 2, 10};
    Monom m1(0.1, p1);
    Monom m2(1000.0, p2);

    EXPECT_TRUE(m1 > m2);
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 < m2);
    EXPECT_FALSE(m1 == m2);
}

TEST(TestMonom, MonomCompareWithOtherByZ) {
    int p1[3] = {10, 5, 20};
    int p2[3] = {10, 5, 10};
    Monom m1(0.1, p1);
    Monom m2(1000.0, p2);

    EXPECT_TRUE(m1 > m2);
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 < m2);
    EXPECT_FALSE(m1 == m2);
}

TEST(TestMonom, MonomEqualCompareWithOther) {
    int p1[3] = {2, 5, 0};
    int p2[3] = {10, 2, 10};
    Monom m1(0.1, p1);
    Monom m2(1000.0, p1);

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);

    Monom m3(0.1, p1);
    Monom m4(1000.0, p2);

    EXPECT_TRUE(m3 != m4);
    EXPECT_FALSE(m3 == m4);
}

TEST(TestMonom, OutputFormatIsCorrect) {
    int p[3] = {2, 1, 0};
    Monom m(5.5, p);

    std::ostringstream oss;
    oss << m;

    EXPECT_EQ(oss.str(), "(5.5 * x^2 * y^1 * z^0)");
}

TEST(TestMonom, InputFormatIsCorrect) {
    Monom m;
    std::istringstream iss("5.5 2 1 0");

    iss >> m;

    int expected_p[3] = {2, 1, 0};
    EXPECT_TRUE(m == Monom(5.5, expected_p));
    EXPECT_DOUBLE_EQ(m.calculate(1, 1, 1), 5.5);
}

// TODO(chernykh): Add unary minus test and exception test
//  to input/output operator for Monom class

TEST(TestPolynom, DefaultConstructorCreatesEmptyPolynom) {
    Polynom p;

    EXPECT_EQ(p.size(), 0);
    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 0.0);
    EXPECT_EQ(p.name(), "");
}

TEST(TestPolynom, CopyConstructorCreatesExactCopy) {
    Polynom p1;
    Polynom p2(p1);

    EXPECT_EQ(p2.size(), 0);
    EXPECT_DOUBLE_EQ(p2.calculate(1, 1, 1), 0.0);
    EXPECT_EQ(p2.name(), "");
}

TEST(TestPolynom, AddFirstMonom) {
    Polynom p;
    int powers[3] = {1, 2, 3};
    Monom m(3.0, powers);

    p += m;
    EXPECT_EQ(p.size(), 1);
    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 3.0);
}

TEST(TestPolynom, test_1) {
    Polynom p;
    int pow[3] = {1, 2, 3};
    Monom m1(3.0, pow);
    Monom m2(4.0, pow);

    p += m1;
    p += m2;
    EXPECT_EQ(p.size(), 1);
    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 7.0);
}

TEST(TestPolynom, test_2) {
    Polynom p;
    int pow1[3] = {1, 2, 3};
    int pow2[3] = {2, 2, 3};
    Monom m1(3.0, pow1);
    Monom m2(4.0, pow2);

    p += m1;
    p += m2;
    EXPECT_EQ(p.size(), 2);
    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 7.0);
}

TEST(TestPolynom, test_3) {
    Polynom p;
    int pow1[3] = {1, 2, 3};
    int pow2[3] = {2, 2, 3};
    Monom m1(3.0, pow1);
    Monom m2(4.0, pow2);

    p += m1;
    p += m2;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m2 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, InsertInMiddle) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    int pow2[3] = {2, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m1(1.0, pow1);
    Monom m2(1.0, pow2);

    p += m5; p += m3; p += m1; p += m2;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3 << " + " << m2 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, InsertAtFront) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    int pow6[3] = {6, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m1(1.0, pow1);
    Monom m6(1.0, pow6);

    p += m5; p += m3; p += m1; p += m6;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m6 << " + " << m5 << " + " << m3 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, InsertAtBack) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    int pow0[3] = {0, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m1(1.0, pow1);
    Monom m0(1.0, pow0);

    p += m5; p += m3; p += m1; p += m0;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3 << " + " << m1 << " + " << m0;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SortByY) {
    Polynom p;
    int pow1[3] = {2, 1, 0};
    int pow2[3] = {2, 3, 0};
    int pow3[3] = {2, 2, 0};
    Monom m1(1.0, pow1);
    Monom m2(1.0, pow2);
    Monom m3(1.0, pow3);

    p += m1; p += m2; p += m3;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m2 << " + " << m3 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SortByZ) {
    Polynom p;
    int pow1[3] = {2, 2, 1};
    int pow2[3] = {2, 2, 3};
    int pow3[3] = {2, 2, 2};
    Monom m1(1.0, pow1);
    Monom m2(1.0, pow2);
    Monom m3(1.0, pow3);

    p += m1; p += m2; p += m3;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m2 << " + " << m3 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, MergeEqualMonomials) {
    Polynom p;
    int pow1[3] = {2, 2, 3};
    Monom m1(3.0, pow1);
    Monom m2(4.0, pow1);
    Monom expected(7.0, pow1);

    p += m1; p += m2;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, MergeToZeroRemoves) {
    Polynom p;
    int pow1[3] = {2, 2, 3};
    Monom m1(3.0, pow1);
    Monom m2(-3.0, pow1);

    p += m1; p += m2;

    std::ostringstream oss_polynom;
    oss_polynom << p;

    EXPECT_EQ(oss_polynom.str(), "");
}

TEST(TestPolynom, AddZeroMonomDoesNothing) {
    Polynom p;
    int pow0[3] = {5, 0, 0};
    Monom m_zero(0.0, pow0);

    p += m_zero;

    EXPECT_EQ(p.size(), 0);
    EXPECT_DOUBLE_EQ(p.calculate(2, 2, 2), 0.0);
}

TEST(TestPolynom, UnaryMinus) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);
    Monom m1(4.0, pow1);

    p += m5; p += m3; p += m1;

    Polynom neg_p = -p;

    Monom m5_neg(-2.0, pow5);
    Monom m3_neg(-3.0, pow3);
    Monom m1_neg(-4.0, pow1);

    std::ostringstream oss_polynom;
    oss_polynom << neg_p;

    std::ostringstream oss_monom;
    oss_monom << m5_neg << " + " << m3_neg << " + " << m1_neg;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, UnaryMinusDoesNotModifyOriginal) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p += m5;
    Polynom neg_p = -p;

    std::ostringstream oss_original;
    oss_original << p;

    std::ostringstream oss_monom;
    oss_monom << m5;

    EXPECT_EQ(oss_original.str(), oss_monom.str());
}

TEST(TestPolynom, MultiplyByScalar) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5; p += m3;

    Polynom result = p * 2.0;

    Monom m5_expected(4.0, pow5);
    Monom m3_expected(6.0, pow3);

    std::ostringstream oss_polynom;
    oss_polynom << result;

    std::ostringstream oss_monom;
    oss_monom << m5_expected << " + " << m3_expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, MultiplyByScalarDoesNotModifyOriginal) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p += m5;
    Polynom result = p * 2.0;

    std::ostringstream oss_original;
    oss_original << p;

    std::ostringstream oss_monom;
    oss_monom << m5;

    EXPECT_EQ(oss_original.str(), oss_monom.str());
}

TEST(TestPolynom, MultiplyByZero) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5; p += m3;
    Polynom result = p * 0.0;

    EXPECT_EQ(result.size(), 0);
    EXPECT_DOUBLE_EQ(result.calculate(2, 2, 2), 0.0);
}

TEST(TestPolynom, MultiplyAssignByZero) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p += m5;
    p *= 0.0;

    EXPECT_EQ(p.size(), 0);
    EXPECT_DOUBLE_EQ(p.calculate(2, 2, 2), 0.0);
}

TEST(TestPolynom, MultiplyAssignByScalarAllMonoms) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);
    Monom m1(4.0, pow1);

    p += m5; p += m3; p += m1;
    p *= 2.0;

    Monom m5_expected(4.0, pow5);
    Monom m3_expected(6.0, pow3);
    Monom m1_expected(8.0, pow1);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5_expected << " + " << m3_expected << " + " << m1_expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, DivideAssignByScalar) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(6.0, pow5);
    Monom m3(9.0, pow3);
    Monom m1(3.0, pow1);

    p += m5; p += m3; p += m1;
    p /= 3.0;

    Monom m5_expected(2.0, pow5);
    Monom m3_expected(3.0, pow3);
    Monom m1_expected(1.0, pow1);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5_expected << " + " << m3_expected << " + " << m1_expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, DivideByScalar) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(4.0, pow5);
    Monom m3(8.0, pow3);

    p += m5; p += m3;

    Polynom result = p / 2.0;

    Monom m5_expected(2.0, pow5);
    Monom m3_expected(4.0, pow3);

    std::ostringstream oss_polynom;
    oss_polynom << result;

    std::ostringstream oss_monom;
    oss_monom << m5_expected << " + " << m3_expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, DivideByScalarDoesNotModifyOriginal) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(4.0, pow5);

    p += m5;
    Polynom result = p / 2.0;

    std::ostringstream oss_original;
    oss_original << p;

    std::ostringstream oss_monom;
    oss_monom << m5;

    EXPECT_EQ(oss_original.str(), oss_monom.str());
}

TEST(TestPolynom, DivideAssignByZeroThrows) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p += m5;

    EXPECT_THROW(p /= 0.0, std::invalid_argument);
}

TEST(TestPolynom, DivideByZeroThrows) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p += m5;

    EXPECT_THROW(p / 0.0, std::invalid_argument);
}

TEST(TestPolynom, DivideByScalarCalculate) {
    Polynom p;
    int pow1[3] = {1, 0, 0};
    Monom m(6.0, pow1);

    p += m;
    Polynom result = p / 3.0;

    EXPECT_DOUBLE_EQ(result.calculate(2, 0, 0), 4.0);
    EXPECT_DOUBLE_EQ(result.calculate(3, 0, 0), 6.0);
}

TEST(TestPolynom, EqualPolynoms) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5; p1 += m3;
    p2 += m5; p2 += m3;

    EXPECT_TRUE(p1 == p2);
}

TEST(TestPolynom, NotEqualByCoeff) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5_2(2.0, pow5);
    Monom m5_3(3.0, pow5);

    p1 += m5_2;
    p2 += m5_3;

    EXPECT_TRUE(p1 != p2);
}

TEST(TestPolynom, NotEqualByDegree) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(2.0, pow3);

    p1 += m5;
    p2 += m3;

    EXPECT_TRUE(p1 != p2);
}

TEST(TestPolynom, NotEqualBySize) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5; p1 += m3;
    p2 += m5;

    EXPECT_TRUE(p1 != p2);
}

TEST(TestPolynom, EqualEmptyPolynoms) {
    Polynom p1, p2;

    EXPECT_TRUE(p1 == p2);
}

TEST(TestPolynom, EqualAfterOperations) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(6.0, pow5);
    Monom m3(3.0, pow3);
    Monom m5_base(2.0, pow5);
    Monom m3_base(1.0, pow3);

    p1 += m5; p1 += m3;
    p2 += m5_base; p2 += m3_base;
    p2 *= 3.0;

    EXPECT_TRUE(p1 == p2);
}

TEST(TestPolynom, AssignCopiesMonoms) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5; p1 += m3;
    p2 = p1;

    EXPECT_TRUE(p1 == p2);
}

TEST(TestPolynom, AssignCopiesName) {
    Polynom p1("myPoly"), p2;

    p2 = p1;

    EXPECT_EQ(p1.name(), p2.name());
}

TEST(TestPolynom, AssignDoesNotModifyOriginal) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5; p1 += m3;
    p2 = p1;

    int pow1[3] = {1, 0, 0};
    Monom m1(4.0, pow1);
    p2 += m1;

    EXPECT_FALSE(p1 == p2);
    EXPECT_EQ(p1.size(), 2);
}

TEST(TestPolynom, AssignToSelf) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p += m5;
    p = p;

    std::ostringstream oss;
    oss << p;

    std::ostringstream oss_monom;
    oss_monom << m5;

    EXPECT_EQ(oss.str(), oss_monom.str());
}

TEST(TestPolynom, AssignEmptyPolynom) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p1 += m5;
    p1 = p2;

    EXPECT_EQ(p1.size(), 0);
    EXPECT_TRUE(p1 == p2);
}

TEST(TestPolynom, SubtractFromMiddle) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m1(1.0, pow1);

    p += m5; p += m3; p += m1;
    EXPECT_EQ(p.size(), 3);
    p -= m3;
    EXPECT_EQ(p.size(), 2);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SubtractFromFront) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m1(1.0, pow1);

    p += m5; p += m3; p += m1;
    EXPECT_EQ(p.size(), 3);
    p -= m5;
    EXPECT_EQ(p.size(), 2);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m3 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SubtractFromBack) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m1(1.0, pow1);

    p += m5; p += m3; p += m1;
    EXPECT_EQ(p.size(), 3);
    p -= m1;
    EXPECT_EQ(p.size(), 2);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SubtractReducesCoeff) {
    Polynom p;
    int pow1[3] = {2, 2, 3};
    Monom m1(5.0, pow1);
    Monom m2(3.0, pow1);
    Monom expected(2.0, pow1);

    p += m1;
    EXPECT_EQ(p.size(), 1);
    p -= m2;
    EXPECT_EQ(p.size(), 1);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SubtractToZeroRemoves) {
    Polynom p;
    int pow1[3] = {2, 2, 3};
    Monom m1(3.0, pow1);

    p += m1;
    EXPECT_EQ(p.size(), 1);
    p -= m1;

    EXPECT_EQ(p.size(), 0);
    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 0.0);
}

TEST(TestPolynom, SubtractNonExistentAddsNegative) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(1.0, pow5);
    Monom m3(1.0, pow3);
    Monom m3_neg(-1.0, pow3);

    p += m5;
    EXPECT_EQ(p.size(), 1);
    p -= m3;
    EXPECT_EQ(p.size(), 2);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3_neg;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SubtractZeroMonomDoesNothing) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);
    Monom m_zero(0.0, pow5);

    p += m5;
    EXPECT_EQ(p.size(), 1);
    p -= m_zero;
    EXPECT_EQ(p.size(), 1);

    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 2.0);
}

TEST(TestPolynom, MultiplyByMonomBasic) {
    Polynom p, expected;
    int pow2[3] = {2, 0, 0};
    int pow1[3] = {1, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m2(2.0, pow2);
    Monom m1(3.0, pow1);
    Monom mult(1.0, pow1);

    p += m2; p += m1;
    p *= mult;

    Monom e1(2.0, pow3);
    Monom e2(3.0, pow2);
    expected += e1; expected += e2;

    EXPECT_TRUE(p == expected);
}

TEST(TestPolynom, MultiplyByZeroMonom) {
    Polynom p;
    int pow2[3] = {2, 0, 0};
    int pow0[3] = {0, 0, 0};
    Monom m(2.0, pow2);
    Monom zero(0.0, pow0);

    p += m;
    p *= zero;

    EXPECT_EQ(p.size(), 0);
    EXPECT_DOUBLE_EQ(p.calculate(1, 1, 1), 0.0);
}

TEST(TestPolynom, MultiplyByMonomCalculate) {
    Polynom p;
    int pow2[3] = {2, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m(2.0, pow2);
    Monom mult(3.0, pow1);

    p += m;
    p *= mult;

    EXPECT_DOUBLE_EQ(p.calculate(2, 1, 1), 48.0);
    EXPECT_EQ(p.size(), 1);
}

TEST(TestPolynom, AddMonomDoesNotModifyOriginal) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5;
    Polynom result = p + m3;

    EXPECT_EQ(p.size(), 1);
    EXPECT_EQ(result.size(), 2);
}

TEST(TestPolynom, SubtractMonomDoesNotModifyOriginal) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5; p += m3;
    Polynom result = p - m3;

    EXPECT_EQ(p.size(), 2);
    EXPECT_EQ(result.size(), 1);
}

TEST(TestPolynom, MultiplyMonomDoesNotModifyOriginal) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(2.0, pow5);
    Monom m1(3.0, pow1);

    p += m5;
    Polynom result = p * m1;

    EXPECT_EQ(p.size(), 1);
    EXPECT_DOUBLE_EQ(p.calculate(2, 1, 1), 64.0);
}

TEST(TestPolynom, AddMonomReturnsCorrectResult) {
    Polynom p, expected;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5;
    Polynom result = p + m3;

    expected += m5; expected += m3;
    EXPECT_TRUE(result == expected);
}

TEST(TestPolynom, SubtractMonomReturnsCorrectResult) {
    Polynom p, expected;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5; p += m3;
    Polynom result = p - m3;

    expected += m5;
    EXPECT_TRUE(result == expected);
}

TEST(TestPolynom, MultiplyMonomReturnsCorrectResult) {
    Polynom p, expected;
    int pow5[3] = {5, 0, 0};
    int pow1[3] = {1, 0, 0};
    int pow6[3] = {6, 0, 0};
    Monom m5(2.0, pow5);
    Monom m1(3.0, pow1);
    Monom m6_expected(6.0, pow6);

    p += m5;
    Polynom result = p * m1;

    expected += m6_expected;
    EXPECT_TRUE(result == expected);
}

TEST(TestPolynom, AddPolynomMergeEqualMonoms) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5_2(2.0, pow5);
    Monom m5_3(3.0, pow5);
    Monom m5_5(5.0, pow5);

    p1 += m5_2;
    p2 += m5_3;
    p1 += p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5_5;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 1);
}

TEST(TestPolynom, AddPolynomMergeToZeroRemoves) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5_pos(3.0, pow5);
    Monom m5_neg(-3.0, pow5);

    p1 += m5_pos;
    p2 += m5_neg;
    p1 += p2;

    EXPECT_EQ(p1.size(), 0);
    EXPECT_DOUBLE_EQ(p1.calculate(1, 1, 1), 0.0);
}

TEST(TestPolynom, AddPolynomOtherTailLonger) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);
    Monom m1(4.0, pow1);

    p1 += m5; p1 += m3;
    p2 += m1;
    p1 += p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, AddPolynomOtherHeadLarger) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);
    Monom m1(4.0, pow1);

    p1 += m3; p1 += m1;
    p2 += m5;
    p1 += p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, AddEmptyPolynom) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p1 += m5;
    p1 += p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 1);
}

TEST(TestPolynom, AddPolynomDoesNotModifyOther) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5;
    p2 += m3;
    p1 += p2;

    std::ostringstream oss_other;
    oss_other << p2;

    std::ostringstream oss_monom;
    oss_monom << m3;

    EXPECT_EQ(oss_other.str(), oss_monom.str());
    EXPECT_EQ(p2.size(), 1);
}

TEST(TestPolynom, AddPolynomSelfAssign) {
    Polynom p;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p += m5; p += m3;
    p += p;

    Monom m5_expected(4.0, pow5);
    Monom m3_expected(6.0, pow3);

    std::ostringstream oss_polynom;
    oss_polynom << p;

    std::ostringstream oss_monom;
    oss_monom << m5_expected << " + " << m3_expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, AddPolynomInterleaved) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow4[3] = {4, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow2[3] = {2, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(1.0, pow5);
    Monom m4(1.0, pow4);
    Monom m3(1.0, pow3);
    Monom m2(1.0, pow2);
    Monom m1(1.0, pow1);

    p1 += m5; p1 += m3; p1 += m1;
    p2 += m4; p2 += m2;
    p1 += p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m4 << " + " << m3 << " + " << m2 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
}

TEST(TestPolynom, SubtractPolynomBasic) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);
    Monom m1(4.0, pow1);

    p1 += m5; p1 += m3; p1 += m1;
    p2 += m3;
    p1 -= p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m1;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 2);
}

TEST(TestPolynom, SubtractPolynomToZero) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5; p1 += m3;
    p2 += m5; p2 += m3;
    p1 -= p2;

    EXPECT_EQ(p1.size(), 0);
    EXPECT_DOUBLE_EQ(p1.calculate(1, 1, 1), 0.0);
}

TEST(TestPolynom, SubtractPolynomDoesNotModifyOther) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);

    p1 += m5; p1 += m3;
    p2 += m3;
    p1 -= p2;

    std::ostringstream oss_other;
    oss_other << p2;

    std::ostringstream oss_monom;
    oss_monom << m3;

    EXPECT_EQ(oss_other.str(), oss_monom.str());
    EXPECT_EQ(p2.size(), 1);
}

TEST(TestPolynom, SubtractEmptyPolynom) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p1 += m5;
    p1 -= p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 1);
}

TEST(TestPolynom, SubtractPolynomNonExistentAddsNegative) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m5(2.0, pow5);
    Monom m3(3.0, pow3);
    Monom m3_neg(-3.0, pow3);

    p1 += m5;
    p2 += m3;
    p1 -= p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m5 << " + " << m3_neg;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 2);
}

TEST(TestPolynom, MultiplyPolynomBasic) {
    Polynom p1, p2;
    int pow2[3] = {2, 0, 0};
    int pow1[3] = {1, 0, 0};
    int pow3[3] = {3, 0, 0};
    Monom m2(2.0, pow2);
    Monom m1(3.0, pow1);
    Monom mult(1.0, pow1);

    p1 += m2; p1 += m1;
    p2 += mult;

    p1 *= p2;

    Monom m3_expected(2.0, pow3);
    Monom m2_expected(3.0, pow2);

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << m3_expected << " + " << m2_expected;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 2);
}

TEST(TestPolynom, MultiplyPolynomMergesEqualMonoms) {
    Polynom p1, p2;
    int pow1[3] = {1, 0, 0};
    int pow0[3] = {0, 0, 0};
    int pow2[3] = {2, 0, 0};
    Monom mx(1.0, pow1);
    Monom m1(1.0, pow0);
    Monom m1_neg(-1.0, pow0);
    Monom mx2(1.0, pow2);

    p1 += mx; p1 += m1;
    p2 += mx; p2 += m1_neg;
    p1 *= p2;

    std::ostringstream oss_polynom;
    oss_polynom << p1;

    std::ostringstream oss_monom;
    oss_monom << mx2 << " + " << m1_neg;

    EXPECT_EQ(oss_polynom.str(), oss_monom.str());
    EXPECT_EQ(p1.size(), 2);
}

TEST(TestPolynom, MultiplyPolynomByZeroPolynom) {
    Polynom p1, p2;
    int pow5[3] = {5, 0, 0};
    Monom m5(2.0, pow5);

    p1 += m5;
    p1 *= p2;

    EXPECT_EQ(p1.size(), 0);
    EXPECT_DOUBLE_EQ(p1.calculate(1, 1, 1), 0.0);
}

TEST(TestPolynom, MultiplyPolynomDoesNotModifyOther) {
    Polynom p1, p2;
    int pow2[3] = {2, 0, 0};
    int pow1[3] = {1, 0, 0};
    Monom m2(2.0, pow2);
    Monom m1(3.0, pow1);

    p1 += m2;
    p2 += m1;
    p1 *= p2;

    std::ostringstream oss_other;
    oss_other << p2;

    std::ostringstream oss_monom;
    oss_monom << m1;

    EXPECT_EQ(oss_other.str(), oss_monom.str());
    EXPECT_EQ(p2.size(), 1);
}

TEST(TestPolynom, MultiplyPolynomCalculate) {
    Polynom p1, p2;
    int pow1[3] = {1, 0, 0};
    int pow0[3] = {0, 0, 0};
    Monom m2x(2.0, pow1);
    Monom m3(3.0, pow0);
    Monom mx(1.0, pow1);
    Monom m1(1.0, pow0);

    p1 += m2x; p1 += m3;
    p2 += mx;  p2 += m1;
    p1 *= p2;

    EXPECT_DOUBLE_EQ(p1.calculate(2, 1, 1), 21.0);
    EXPECT_EQ(p1.size(), 3);
}
