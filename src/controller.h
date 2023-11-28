/*!
  \file controller.h
*/
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "athenian.h"

namespace s21 {
/*!
\brief Данный класс служит контроллером для работы с Моделью и Вью

Класс реализован через паттерн проектирования "Фасад"

Подробное описание всех функций находится в файлах "athenian.h" и "model.h"
*/
class Controller {
 public:
  Controller() : coreFunctions_(CoreFunctions::getInstance()), athenian_() {}
  /*!
  \brief Метод для автоматической настройки размера, под размер экрана
  */
  void Autoscale() {
    AutoscaleStrategy autoscaleStrategy;
    athenian_.PerformTransformation(&coreFunctions_, &autoscaleStrategy);
  }
  /*!
  \brief Метод для вращения модели по всем осям X Y Z
  */
  void MoveXYZ(double x, double y, double z) {
    MoveXYZStrategy moveXYZStrategy(x, y, z);
    athenian_.PerformTransformation(&coreFunctions_, &moveXYZStrategy);
  }
  /*!
  \brief Метод для изменения размера модели
  */
  void Scaling(double tmp) {
    ScalingStrategy scalingStrategy(tmp);
    athenian_.PerformTransformation(&coreFunctions_, &scalingStrategy);
  }
  /*!
  \brief Метод вращения по оси X
  */
  void RotationX(double tmp) {
    RotationXStrategy rotationXStrategy(tmp);
    athenian_.PerformTransformation(&coreFunctions_, &rotationXStrategy);
  }
  /*!
  \brief Метод вращения по оси Y
  */
  void RotationY(double tmp) {
    RotationYStrategy rotationYStrategy(tmp);
    athenian_.PerformTransformation(&coreFunctions_, &rotationYStrategy);
  }
  /*!
  \brief Метод вращения по оси Z
  */
  void RotationZ(double tmp) {
    RotationZStrategy rotationZStrategy(tmp);
    athenian_.PerformTransformation(&coreFunctions_, &rotationZStrategy);
  }

  /*!
  \brief Метод Открытия файла

  Сначала метод подсчитывает количество рёбер и вершин

  После метод записывает все рёбра и вершины в соответсвующие массивы
  */
  void OpenFile(const std::string& filename) {
    coreFunctions_.Quantity(const_cast<char*>(filename.c_str()));
    coreFunctions_.Record(const_cast<char*>(filename.c_str()));
  }
  /*!
  \brief Метод для получения количество вершин

  \return Количество вершин
  */
  int GetCountVertexes() { return coreFunctions_.polygons.count_vertexes; }
  /*!
  \brief Метод для получения количество рёбер

  \return Количество рёбер
  */
  int GetRows() { return coreFunctions_.matrix_xyz.rows; }
  /*!
  \brief Метод для получения массива вершин

  \return Массив Вершин
  */
  int* GetVertexes() { return coreFunctions_.polygons.vertexes; }
  /*!
  \brief Метод для получения массива рёьер

  \return Массив ребер
  */
  double* GetMatrix() { return coreFunctions_.matrix_xyz.matrix; }

 private:
  CoreFunctions& coreFunctions_;
  Athenian athenian_;
};
}  // namespace s21

#endif  // CONTROLLER_H_
