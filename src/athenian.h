/*!
  \file athenian.h
*/
#ifndef ATHENIAN_H_
#define ATHENIAN_H_

#include <cmath>

#include "model.h"

namespace s21 {

class TransformationStrategy {
 public:
  virtual void Transform(s21::CoreFunctions* a) = 0;
};

/*!
  \brief Класс, использующий стратегии для выполнения операций над матрицей
*/
class MoveXYZStrategy : public TransformationStrategy {
 public:
  MoveXYZStrategy(double x, double y, double z) : x_(x), y_(y), z_(z) {}

  void Transform(s21::CoreFunctions* a) override {
    if (x_)
      for (unsigned int i = 0; i < a->matrix_xyz.rows; i += 3)
        a->matrix_xyz.matrix[i] += x_;
    if (y_)
      for (unsigned int i = 1; i < a->matrix_xyz.rows; i += 3)
        a->matrix_xyz.matrix[i] += y_;
    if (z_)
      for (unsigned int i = 2; i < a->matrix_xyz.rows; i += 3)
        a->matrix_xyz.matrix[i] += z_;
  }

 private:
  double x_, y_, z_;
};
/*!
  \brief Конкретная стратегия для операции "Масштабирование"
*/
class ScalingStrategy : public TransformationStrategy {
 public:
  ScalingStrategy(double tmp) : tmp_(tmp) {}
  void Transform(s21::CoreFunctions* a) override {
    for (unsigned int i = 0; i < a->matrix_xyz.rows; i++)
      a->matrix_xyz.matrix[i] *= tmp_;
  }

 private:
  double tmp_;
};

class RotationXStrategy : public TransformationStrategy {
 public:
  RotationXStrategy(double x) : x_(x) {}
  void Transform(s21::CoreFunctions* a) override {
    double c = cos(x_), s = sin(x_);
    for (unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
      double temp_y = a->matrix_xyz.matrix[i + 1];
      double temp_z = a->matrix_xyz.matrix[i + 2];
      a->matrix_xyz.matrix[i + 1] = c * temp_y - s * temp_z;
      a->matrix_xyz.matrix[i + 2] = s * temp_y + c * temp_z;
    }
  }

 private:
  double x_;
};

class RotationYStrategy : public TransformationStrategy {
 public:
  RotationYStrategy(double y) : y_(y) {}
  void Transform(s21::CoreFunctions* a) override {
    double c = cos(y_), s = sin(y_);
    for (unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
      double temp_x = a->matrix_xyz.matrix[i];
      double temp_z = a->matrix_xyz.matrix[i + 2];
      a->matrix_xyz.matrix[i] = c * temp_x - s * temp_z;
      a->matrix_xyz.matrix[i + 2] = temp_x * s + c * temp_z;
    }
  }

 private:
  double y_;
};

class RotationZStrategy : public TransformationStrategy {
 public:
  RotationZStrategy(double z) : z_(z) {}
  void Transform(s21::CoreFunctions* a) override {
    double c = cos(z_), s = sin(z_);
    for (unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
      double temp_x = a->matrix_xyz.matrix[i];
      double temp_y = a->matrix_xyz.matrix[i + 1];
      a->matrix_xyz.matrix[i] = c * temp_x - s * temp_y;
      a->matrix_xyz.matrix[i + 1] = c * temp_y + temp_x * s;
    }
  }

 private:
  double z_;
};

class Athenian {
 public:
  void PerformTransformation(s21::CoreFunctions* a,
                             TransformationStrategy* strategy) {
    strategy->Transform(a);
  }
};

class AutoscaleStrategy : public TransformationStrategy {
 public:
  void Transform(s21::CoreFunctions* a) override {
    double max_x = 0, min_x = 0, max_y = 0, min_y = 0, max_z = 0, min_z = 0,
           max = 0;
    for (unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
      if (max_x < a->matrix_xyz.matrix[i]) max_x = a->matrix_xyz.matrix[i];
      if (min_x > a->matrix_xyz.matrix[i]) min_x = a->matrix_xyz.matrix[i];
      if (max_y < a->matrix_xyz.matrix[i + 1])
        max_y = a->matrix_xyz.matrix[i + 1];
      if (min_y > a->matrix_xyz.matrix[i + 1])
        min_y = a->matrix_xyz.matrix[i + 1];
      if (max_z < a->matrix_xyz.matrix[i + 2])
        max_z = a->matrix_xyz.matrix[i + 2];
      if (min_z > a->matrix_xyz.matrix[i + 2])
        min_z = a->matrix_xyz.matrix[i + 2];
    }
    int x = (max_x + min_x) / 2;
    int y = (max_y + min_y) / 2;
    int z = (max_z + min_z) / 2;
    Athenian athenian;

    MoveXYZStrategy moveXYZStrategy(-x, -y, -z);
    athenian.PerformTransformation(a, &moveXYZStrategy);

    for (unsigned int i = 0; i < a->matrix_xyz.rows; i++)
      if (max < fabs(a->matrix_xyz.matrix[i]))
        max = fabs(a->matrix_xyz.matrix[i]);

    ScalingStrategy scalingStrategy(1.5 / max);
    athenian.PerformTransformation(a, &scalingStrategy);
  }
};

}  // namespace s21

#endif  // ATHENIAN_H_
