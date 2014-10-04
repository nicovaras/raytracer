#include "gtest/gtest.h"
#include "../Vec3.hpp"

class Vec3Test : public ::testing::Test {
protected:
    Vec3Test() : vec1_(Vec3(0, 0, 0)), vec2_(Vec3(0, 0, 0)) {
    };

    virtual void SetUp() {
        vec1_ = Vec3(1.0, 2.0, 3.0);
        vec2_ = Vec3(1.0, 2.0, 3.0);
    }

    // virtual void TearDown() {}

    Vec3 vec1_;
    Vec3 vec2_;

};

TEST_F(Vec3Test, operatorPlus) {
    Vec3 res = Vec3(2.0, 4.0, 6.0);
    ASSERT_EQ(vec1_ + vec2_, res);
    ASSERT_EQ(vec2_ + vec1_, res);
}

TEST_F(Vec3Test, operatorScalarProduct) {
    Vec3 res = Vec3(2.0, 4.0, 6.0);
    ASSERT_EQ(2 * vec1_, res);
    ASSERT_EQ(vec1_ * 2, res);
    ASSERT_EQ(0 * vec1_, Vec3(0.0, 0.0, 0.0));
}

TEST_F(Vec3Test, operatorDotProduct) {
    ASSERT_EQ(vec1_ * vec2_, 14);
    ASSERT_EQ(vec2_ * vec1_, 14);
}
