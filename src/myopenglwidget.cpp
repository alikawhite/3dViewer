/**
 *
 * @file myopenglwidget.cpp
 *
 */
#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    :QOpenGLWidget { parent }
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update())); // таймер для обновления
    timer->start(1); // скорость обновления
}
  /*!
  \brief Необходимо использовать для глобальных настрое построения изображения, которые нет необходимости указывать при построении кадра.
  */
void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnableClientState(GL_VERTEX_ARRAY); // нужно для функции "glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);"
    glEnable(GL_POINT_SMOOTH); // нужно для "glDrawArrays(GL_POINTS, 0, 99);" Отрисовки рёбер
}
  /*!
  \brief этот метод будет выстраивать каждый наш кадр для отображения.
  */
void MyOpenGLWidget::paintGL()
{
    glClearColor(normalize_0_1(r), normalize_0_1(g), normalize_0_1(b), a); // цвет фона

    // Включение и выключение пунктирных линий
    if(LineStipple == 0)
        glEnable(GL_LINE_STIPPLE);
    else if(LineStipple == 1)
        glDisable(GL_LINE_STIPPLE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // -------------- Настройка типа проекции --------------
    glLoadIdentity();
    if(ProjectionType == 1)
        glOrtho(-2,2, -2,2, -5,100); // Прямая (Орографическая) проекция
    else if(ProjectionType == 0)
        glFrustum(-2,2, -2,2, -5,100); // Центральная (перспективная) проекция

    // -------------- Вращение мышкой --------------
    glRotated(xRot, 1, 0, 0);
    glRotated(yRot, 0, 1, 0);

    // -------------- Сдвиг по осям кординат --------------
    if ((x!=def_x)||(y!=def_y)||(z!=def_z)) {
        core.MoveXYZ(x-def_x, y-def_y , z-def_z);
        def_x=x;
        def_y=y;
        def_z=z;
    } // сдвиг по осям наш

    // -------------- Вращение по осям кординат --------------
    if (Rx != defRx) {
        core.RotationX(((Rx-defRx) * 2 * M_PI)/ 360);
        defRx=Rx;
    }
    if (Ry != defRy) {
        core.RotationY(((Ry-defRy) * 2 * M_PI)/ 360);
        defRy=Ry;
    }
    if (Rz != defRz) {
        core.RotationZ(((Rz-defRz) * 2 * M_PI)/ 360);
        defRz=Rz;
    }
    if(autorotate != 0) core.RotationY(0.05);

    // -------------- Настройка отрисовки линий --------------
    glLineStipple(1, 1); // пунктирные линии
    glColor3i(LineR, LineG, LineB); // цвет линиий (255, 255, 255) - белый
    glLineWidth(LineSize); // толщина линий

    // Получение названя открываемого файла

    // --------------------------- Парсер и заполнение массивов ---------------------------
    if(FOpen == 1) { // получение данных из файла
        core.OpenFile(filename.toStdString()); // открытие файла, заполнение масиивов данных
        core.Autoscale(); // авто выравнивание модели по размерам экрана

        // -------- Вывод данных о количестве рёбер и вершин --------
        lbl_36->setText(QString::number(core.GetCountVertexes() / 2));
        lbl->setText(QString::number(core.GetRows() / 3));

        // -------- Обнуление данных --------
        NullCord();
    }
    // --------------------------- Отрисовка линий и вершин ---------------------------

    glVertexPointer(3, GL_DOUBLE, 0, core.GetMatrix()); //принимает вершины, нужно для следующей функции
    if (LineStipple != 2)
        glDrawElements(GL_LINES,  core.GetCountVertexes(), GL_UNSIGNED_INT, core.GetVertexes()); // принимает индексы полигонов и отрисовывает линии по вершинам из функции выше

    // --------------------------- Отрисовка точек ---------------------------
    if(PointType != 0) { // настройки отрисовки точек
        if(PointType == 2)
            glDisable(GL_POINT_SMOOTH);// при отключение точки будут квадратные
        else
            glEnable(GL_POINT_SMOOTH);
        glColor3i(PointR, PointG, PointB); // цвет точек (255, 255, 255) - белый
        glPointSize(PointSize); // толщена точек
        glDrawArrays(GL_POINTS, 0, core.GetRows()/3); // отрисовка точек
    }

    // --------------------------- Отрисовка линий X, Y, Z ---------------------------
    if(xyz != 0) graficarLineas(); // вызов функции для отрисовки линий X, Y, Z
}

  /*!
  \brief Служит для построения размера окна. Если в ходе работы изменится размер окна, но не изменить область просмотра, то при увеличении размера можно наблюдать непредсказуемые явления.
  */
void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
  /*!
  \brief Метод служит для отрисовки осей X Y Z 
  */
void MyOpenGLWidget::graficarLineas(){ // функция для отрисовки линий X, Y, Z
    // X
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(20,0,0);
    // Y
    glBegin(GL_LINES);
    glColor3f(1,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,20,0);
    // Z
    glBegin(GL_LINES);
    glColor3f(0,1,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,20);
    glEnd();
}
  /*!
  \brief Метод служит нормализации палитры цветов RGB
  */
double MyOpenGLWidget::normalize_0_1(double val) const { return (val - 1) / (255 - 1); }
  /*!
  \brief Метод служит управления событиями нажатия мыши
  */
void MyOpenGLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }
  /*!
  \brief Метод служит управления событиями нажатия мыши
  */
void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* mo) {
    xRot = (1 / M_PI*(mo->pos().y() - mPos.y()));
    yRot = (1 / M_PI*(mo->pos().x() - mPos.x()));
    update();
}
  /*!
  \brief Метод служит для зануления кординат при отрисовки новой модели
  */
void MyOpenGLWidget::NullCord() {
    x = 0.0, y = 0.0, z = 0.0;
    def_x = 0.0, def_y = 0.0, def_z = 0.0;
    Rx = 0.0, Ry = 0.0, Rz = 0.0;
    defRx = 0.0, defRy = 0.0, defRz = 0.0;
    FOpen = 0;
}
