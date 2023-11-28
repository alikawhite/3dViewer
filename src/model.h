
/*!
  \file model.h
*/
#ifndef MODEL_H_
#define MODEL_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

namespace s21 {
/*!
 \brief Структура хранящая в себе количество полигонов и сами полигоны
 */
struct Polygon {
  int *vertexes = 0;
  unsigned int count_vertexes = 0;
};
/*!
 \brief Структура хранящая в себе количество вершин и сами вершины
 */
struct Matrix {
  double *matrix = 0;
  unsigned int rows = 0;
};
/*!
 \brief Класс содержащий в себе основные методы для открытия модели

 Класс реализован через паттерн проектирования "Одиночка" (Singleton)
 */
class CoreFunctions {
 public:
  static CoreFunctions &getInstance() {
    static CoreFunctions instance;  // Единственный экземпляр класса
    return instance;
  }

  CoreFunctions(const CoreFunctions &) = delete;
  CoreFunctions &operator=(const CoreFunctions &) = delete;
  ~CoreFunctions() { Deallocation(); }

  Matrix matrix_xyz;
  Polygon polygons;
  /*!
   \brief Метод подсчитывающий количество вершин и полигонов в модели
   \param filename Путь до файла
   */
  void Quantity(char *filename) {
    Deallocation();
    if (filename[0]) {
      matrix_xyz.rows = 0;
      polygons.count_vertexes = 0;
      FILE *f1 = fopen(filename, "r");
      if (f1 != NULL)
        while (!feof(f1)) {
          char str[512] = {0};
          if (!fgets(str, 511, f1)) continue;
          int t = 0, x = 0;
          if (str[0] == 'v' && str[1] == ' ')
            matrix_xyz.rows++;
          else if (str[0] == 'f' && str[1] == ' ')
            while (str[t] != '\n')
              if ((str[t++] == ' ') && (sscanf(str + t, "%d", &x)))
                polygons.count_vertexes++;
        }
      else
        perror("Error occured while opening file");
      fclose(f1);
    } else {
      matrix_xyz.rows = 0;
      polygons.count_vertexes = 0;
    }
    Allocation();
  }
  /*!
   \brief Метод для отчистки памяти

    Метод удаляет данных после завршения работы с моделью
   */
  void Deallocation() {
    if (alloc_ == 1) {
      if (matrix_xyz.matrix) delete[] matrix_xyz.matrix;
      if (polygons.vertexes) delete[] polygons.vertexes;
      matrix_xyz = {0, 0};
      polygons = {0, 0};
      alloc_ = 0;
    } else {
    }
  }
  /*!
    \brief Метод для выделения памяти

    Метод выделяет память для работы с моделью
    */
  void Allocation() {
    if ((polygons.count_vertexes == 0) && (matrix_xyz.rows == 0)) {
    } else {
      polygons.vertexes = new int[(polygons.count_vertexes *= 2) + 6];
      matrix_xyz.matrix = new double[(matrix_xyz.rows = matrix_xyz.rows * 3)];
      alloc_ = 1;
    }
  }
  /*!
   \brief Метод для записи количества вершин и рёбер
   \param filename Путь до файла
   */
  void Record(char *filename) {
    FILE *f1 = fopen(filename, "r");
    int n = 0, n2 = 0, tmp = 0, t = 1, x = 0, xc = 0;
    char s[256] = {0};
    if (f1 != NULL) {
      while (!feof(f1)) {
        fgets(s, 255, f1);
        if ((s[0] == 'f') & (!(xc = 0)) & (t = 1)) {
          while (s[t] != '\n') {
            if (sscanf(s + (t++), " %d", &x)) {
              polygons.vertexes[n++] = x - 1;
              if (xc != 0)
                polygons.vertexes[n++] = x - 1;
              else
                tmp = x - (xc = 1);
              while ((s[t] != ' ') && (s[t] != '\n')) t++;
            }
          }
          polygons.vertexes[n++] = tmp;
        } else if (s[0] == 'v' && s[1] == ' ')
          if (sscanf(s, "v %lf %lf %lf", matrix_xyz.matrix + n2,
                     matrix_xyz.matrix + n2 + 1,
                     matrix_xyz.matrix + n2 + 2) == 3)
            n2 += 3;
      }
    } else
      perror("Error occured while opening file");
    fclose(f1);
  }

 private:
  CoreFunctions() {}  // Приватный конструктор
  bool alloc_ = 0;
};

}  // namespace s21

#endif  // MODEL_H_
