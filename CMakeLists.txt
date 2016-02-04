cmake_minimum_required(VERSION 2.8.4)
project(raytracer)
find_package( OpenCV REQUIRED )
add_subdirectory(gtest-1.7.0)
add_subdirectory(test)
enable_testing()

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES raytracer.cc ray.cpp Vec3.cpp scene.cc light.cc sphere.cc)
add_executable(raytracer main.cpp ${SOURCE_FILES})
target_link_libraries( raytracer ${OpenCV_LIBS} )

add_executable(runTests test/test.cc test/testVec3.cc test/testRay.cc test/testScene.cc ${SOURCE_FILES})
target_link_libraries(runTests gtest gtest_main ${OpenCV_LIBS} pthread)
configure_file(resources/lightbulb.png ${CMAKE_CURRENT_BINARY_DIR}/resources/lightbulb.png COPYONLY)
