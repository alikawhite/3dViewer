/**
 *
 * @file myopenglwidget.h
 *
 */
#ifndef MYOPENGLWIDGET_H_
#define MYOPENGLWIDGET_H_

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
// #include <GL/gl.h>
// #include <GL/glut.h>
#endif

#include <unistd.h>

#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <iostream>

#include "controller.h"

#define RGB_MIN 1
#define RGB_MAX 255

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  QLabel *lbl, *lbl_36;

  QString filename;
  s21::Controller core;

  bool FOpen = 0;
  int autorotate = 0;
  int xyz = 0;

  int r = 0, g = 0, b = 0, a = normalize_0_1(RGB_MAX);

  double x = 0.0, y = 0.0, z = 0.0;  // кординаты смещения по осям
  double def_x = 0.0, def_y = 0.0, def_z = 0.0;

  double Rx = 0.0, Ry = 0.0, Rz = 0.0;  // кординаты вращения по осям
  double defRx = 0.0, defRy = 0.0, defRz = 0.0;

  int LineR = 0, LineG = 0, LineB = 2147483647, LineSize = 5;
  int PointR = 2147483647, PointG = 0, PointB = 0, PointSize = 20,
      PointType = 1;
  bool ProjectionType = 1;
  int LineStipple = 1;
  double scale = 1;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void graficarLineas();
  void NullCord();

 private:
  double normalize_0_1(double val) const;
  QTimer timer;

  float xRot, yRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // MYOPENGLWIDGET_H_
