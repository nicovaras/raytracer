#include "../Vec3.hpp"
#include "../scene.h"
#include "../sphere.h"
#include "gtest/gtest.h"

TEST(Sphere, sphereIntersection) {
    Sphere s1 = Sphere(150.0, Vec3(600, 200, 100));

    Ray r1 = Ray(Vec3(653, 174, -100), Vec3(0, 0, 1));
    ASSERT_TRUE(s1.intersectScalar(r1) > 0.0);

    r1 = Ray(Vec3(749, 212, -100), Vec3(0, 0, 1));
    ASSERT_TRUE(s1.intersectScalar(r1) > 0.0);

    r1 = Ray(Vec3(293, 349, -100), Vec3(0, 0, 1));
    ASSERT_TRUE(s1.intersectScalar(r1) < 0.0);

    r1 = Ray(Vec3(294, 227, -100), Vec3(0, 0, 1));
    ASSERT_TRUE(s1.intersectScalar(r1) < 0.0);


}
