#include "framegl.h"
#include <thread>
#include <iostream>
#include <QMouseEvent>

#define val_reescale  0.001

using namespace std;

FrameGL::FrameGL(QWidget *parent) : QGLWidget(parent)
{
    connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(50);
    RTree = new rangeTree;
    RTree->build();
    //RTree->print(RTree->root);
}


void FrameGL::initializeGL()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}


void rectangle( int face)
{
     int med=face/2;
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2);

    glBegin(GL_LINE_LOOP);
         glVertex2i(-med,-med);
         glVertex2i(-med,med);
         glVertex2i(med,med);
         glVertex2i(med,-med);
    glEnd();
}


void FrameGL::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0,0,5,  0,0,0,  0,1,0 );
    glScalef(val_reescale,val_reescale,val_reescale);


    glPointSize(2);
    glBegin(GL_POINTS);
        for(   int i=0;i<cant_pts;i++)
        {
             glColor3f(0.0,RTree->vec_pts[i]->color, 0.0);
             glVertex2i(RTree->vec_pts[i]->xy[0],RTree->vec_pts[i]->xy[1]);
        }
    glEnd();

    glTranslated(x,y,0);
    rectangle(300);
    RTree->query(x-150,x+150,y-150,y+150);


}


void FrameGL::resizeGL( int w, int h)
{
    glViewport(-1*w,-1*h, w*2,h*2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45., (float)w/h, 0.01, 100.0 );

    updateGL();
}



void FrameGL::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x()*(3.45);
    y = _h+65-(event->y()*3.45);
    emit Mouse_Pos();

}




void FrameGL::mousePressEvent(QMouseEvent *event)

{
    emit Mouse_Pressed();
}


void FrameGL::leaveEvent(QEvent *event)
{
    emit Mouse_Left();
}


