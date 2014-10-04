#include "gtest/gtest.h"
#include "../ray.h"

class RayTest : public ::testing::Test {
protected:
    RayTest() : ray1_(Vec3(0, 0, 0), Vec3(0, 0, 0)) {
    };

    virtual void SetUp() {
        ray1_ = Ray(Vec3(1.0, 2.0, 3.0), Vec3(1.0, 1.0, 1.0));
    }

    Ray ray1_;
};

TEST_F(RayTest, point_on) {
    ASSERT_EQ(ray1_.point_on(1), Vec3(2.0, 3.0, 4.0));
    ASSERT_EQ(ray1_.point_on(0), Vec3(1.0, 2.0, 3.0));
    ASSERT_EQ(ray1_.point_on(-1), Vec3(0.0, 1.0, 2.0));
    ASSERT_EQ(ray1_.point_on(-0.5), Vec3(0.5, 1.5, 2.5));
}

