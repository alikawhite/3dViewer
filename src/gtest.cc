/**
 *
 * @file gtest.cc
 *
 */
#include <gtest/gtest.h>

#include "athenian.h"

TEST(AllTest, Test_1) {
  double EPS_10 = 1e-10;
  double PI = 3.141592653589;
  double res1[25] = {1.500000,  1.500000,  1.500000,  1.500000,  1.500000,
                     -1.500000, 1.500000,  -1.500000, 1.500000,  1.500000,
                     -1.500000, -1.500000, -1.500000, 1.500000,  -1.500000,
                     -1.500000, 1.500000,  1.500000,  -1.500000, -1.500000,
                     -1.500000, -1.500000, -1.500000, 1.500000,  0};

  s21::CoreFunctions &core = s21::CoreFunctions::getInstance();
  s21::Athenian athenian_;
  core.Quantity("tests/box.obj");
  core.Record("tests/box.obj");

  s21::AutoscaleStrategy autoscaleStrategy;
  athenian_.PerformTransformation(&core, &autoscaleStrategy);

  s21::MoveXYZStrategy moveXYZStrategy(1, 1, 1);
  athenian_.PerformTransformation(&core, &moveXYZStrategy);

  s21::RotationXStrategy rotationXStrategy(PI * 2);
  athenian_.PerformTransformation(&core, &rotationXStrategy);

  s21::RotationYStrategy rotationYStrategy(PI * 2);
  athenian_.PerformTransformation(&core, &rotationYStrategy);

  s21::RotationZStrategy rotationZStrategy(PI * 2);
  athenian_.PerformTransformation(&core, &rotationZStrategy);

  for (unsigned int j = 3; j < core.matrix_xyz.rows; j++) {
    EXPECT_NEAR(core.matrix_xyz.matrix[j], res1[j] + 1, EPS_10);
  }
}

TEST(ZerroFileTest, Test_1) {
  s21::CoreFunctions &core = s21::CoreFunctions::getInstance();
  core.Quantity("");
  core.Record("");
  EXPECT_EQ(core.matrix_xyz.rows, 0);
  EXPECT_EQ(core.polygons.count_vertexes, 0);
}

TEST(ErrorTest, Test_1) {
  s21::CoreFunctions &core = s21::CoreFunctions::getInstance();
  core.Quantity("error.obj");
  core.Record("error.obj");
  EXPECT_EQ(core.matrix_xyz.rows, 0);
  EXPECT_EQ(core.polygons.count_vertexes, 0);
}