#ifndef FRAMEGL_H
#define FRAMEGL_H

#include <QWidget>
#include <QGLWidget>
#include <GL/glut.h>
#include <QTimer>
#include <list>
#include <algorithm>
#include <iostream>
#include "rangetree.h"



#include <QEvent>
#include <QDebug>
#include <QMouseEvent>



using namespace std;

class FrameGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit FrameGL(QWidget *parent);

    void initializeGL();
    void paintGL();
    void resizeGL( int w,  int h);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
     int x=500,y=300;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

private:
    QTimer timer;
    rangeTree *RTree;

     int m_x;
     int m_y;





};

#endif // FRAMEGL_H







