#ifndef FRAMEGL_H
#define FRAMEGL_H

#include <QGLWidget>
#include <QTimer>



#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include "kdtree.h"



class FrameGL : public QGLWidget
{


    Q_OBJECT
public:
    explicit FrameGL(QWidget *parent);

    void initializeGL();
    void paintGL();
    void resizeGL( int w,  int h);
    QTimer timer;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void activateAddEvent(QEvent *event);




     int x=500,y=300;
    KDTree *kdt;

    //temporal points
    int temx=0;
    int temy=0;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
    void Insertar_Option();






};

#endif // FRAMEGL_H
