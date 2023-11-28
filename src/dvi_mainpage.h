/**
 * @file dvi_mainpage.h
 * @author boostery (boostery@student.21-school.ru)
 * @author butterps (butterps@student.21-school.ru)
 * @author margycle (margycle@student.21-school.ru)
 * @brief Основной файл документации проекта для формирования doxygen отчета
 * @version 0.1
 * @date 2023-05-13
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * @mainpage Краткая документация по проекту 3D_Viewer_v2.0
 * @details Программа разработана на языке С++ стандарта C++17 с использованием
 * компилятора g++. В проекте использованы дополнительные библиотеки и модули QT
 *
 *
 * В данном проекте, на языке программирования С++, в парадигме
 * объектно-ориентированного программирования, \n реализвано приложение для
 * просмотра 3D моделей в каркасном виде, реализующее те же самые функции, что и
 * разработанное \n ранее приложение в проекте 3DViewer v1.0. \n \n
 * Собранное приложения сохраняется в '/home/3d_Viewer_2/'
 *
 * Основные части проекта:
 * - @ref model.h "Модель - Парсинг файла"
 * - @ref athenian.h "Модель - афинные преобразования"
 * - @ref controller.h "Контроллер - Cвязывает Model и View"
 * - @ref mainwindow.h "Вью - View (Весь пользовательский интерфейс)"
 * - @ref myopenglwidget.h "QT виджет - Отвечающий за работу opengl"
 *
 * Основные цели для работы с проетом:
 *
 * - Установка:
 *   - Для установки проекта и сборки тестов используйте цель 'all'
 *   @code {.cc}
 *   make all
 *   @endcode
 *   - Для установки проекта без сборки тестов используте цель 'install'
 *   @code {.cc}
 *   make install
 *   @endcode
 *
 * - Удаление:
 *   - Для удаления программы использйте цель 'uninstall'
 *   @code {.cc}
 *   make uninstall
 *   @endcode
 *
 * - Тесты:
 *   - Для сборки тестов без установки используйте цель 'tests'
 *   @code {.c}
 *   make tests
 *   @endcode
 *
 * - gcovr (Покрытие кода):
 *   - Для просмотра покрытия кода используйте цель 'gcov_report'
 *   @code {.c}
 *   make gcov_report
 *   @endcode
 *   @warning Для работы этой функции требуется утилита 'gcovr'
 *
 * - Архивация:
 *   - Для архивации проекта используйте цель 'dist'
 *   @code {.c}
 *   make dist
 *   @endcode
 *
 * - Проверка на стиль (clang):
 *   - Для проверки кода на стиль, используйте цель 'clang'
 *   @code {.c}
 *   make clang
 *   @endcode
 *   @warning Для работы этой функции требуется утилита 'clang-format'
 *
 * - Проверка на утечки (leaks):
 *   - Для проверки кода на утечки памяти, используйте цель 'leaks'
 *   @code {.c}
 *   make leaks
 *   @endcode
 *   @warning Данная цель использует разные утилиты в зависимости от
 * операционной системы
 *      - Для работы этой функции на 'Linux', требуется утилита - 'valgrind'
 *      - Для работы этой функции на 'Mac OS', требуется утилита - 'leaks'
 *
 * - Очистка временных файлов (clean):
 *   - Для очистка временных файлов, которые появились при сборке, используйте
 * цель 'clean'
 *   @code {.c}
 *   make clean
 *   @endcode
 *
 *
 *
 * @author boostery (boostery@student.21-school.ru)
 * @author butterps (butterps@student.21-school.ru)
 * @author margycle (margycle@student.21-school.ru)
 */
