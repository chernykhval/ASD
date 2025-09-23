// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_matrix/matrix.h"


#define EPSILON 0.000001

TEST(TestMatrix, init) {
    ASSERT_NO_THROW(Matrix<int> matrix(2, 3););
}
