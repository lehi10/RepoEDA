#include "framegl.h"
#include "kdtree.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>

#define val_reescale  0.001


#define def_insert 0
#define def_lines 1
#define def_range_search  0
#define def_nearest_neighbor  0
#define def_print 1
#define def_cant_pts 10

using namespace std;




FrameGL::FrameGL(QWidget *parent) : QGLWidget(parent)
{
    connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(10);

    int dim=2;
    kdt=new KDTree(dim);
    for(int i=0;i<def_cant_pts;i++)
    {
        vector<float> *point_=new vector<float>(dim);
        (*point_)[0]=rand()%_w;
        (*point_)[1]=rand()%_h;
        //(*point_)[0]=rand()%30;
        //(*point_)[1]=rand()%30;
        kdt->insertVecCoord(dim,point_);
    }
    if(def_print == 1)
        kdt->print(kdt->root);
}


void FrameGL::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}




void printPoints(KDNode * node)
{
    if(!node)
        return;
    glPointSize(5);

    glBegin(GL_POINTS);
        glColor3f(0,1,node->color);
        glVertex3f((*node->coordK)[0],(*node->coordK)[1],0);
    glEnd();

    if(def_lines == 1)
    {
        glBegin(GL_LINES);
            glColor3f(1,0,0);
            if(node->hv==0)
            {
                glVertex3f((*node->coordK)[0],node->yi,0);
                glVertex3f((*node->coordK)[0],node->yf,0);
            }
            if(node->hv==1)
            {
                glVertex3f(node->xi,(*node->coordK)[1],0);
                glVertex3f(node->xf,(*node->coordK)[1],0);
            }
        glEnd();
    }

    printPoints(node->children[0]);
    printPoints(node->children[1]);
}

void rectangle( int face)
{
    int med=face/2;
    glColor3f(0.0f, 1.0f, 1.0f);
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

    printPoints(kdt->root);

    if(temx!=0 && temy!=0)
    {
        glPointSize(6);
        glBegin(GL_POINTS);
            glColor3f(0.0,1.0,1.0);
            glVertex3f(x,y,0);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(1,0,1);
            glVertex3f(x,y,0);
            glVertex3f(temx,temy,0);
        glEnd();
    }

    // Esto es para la busqueda en rango ....
    if(def_range_search==1)
    {
        glTranslated(this->x,this->y,0);
        rectangle(500);
        kdt->range(x-250,y-250,x+250,y+250);
    }
    // ......

}


void FrameGL::resizeGL( int w, int h)
{
    glViewport(-1*w,-1*h, w*2,h*2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45., (float)w/h, 0.01, 100.0 );
    updateGL();
}



void FrameGL::mousePressEvent(QMouseEvent *event)
{
    x = event->x()*(3.45);
    y = _h+65-(event->y()*3.45);


    vector<float> * point=new vector<float>(3);
    (*point)[0]=x;
    (*point)[1]=y;


    if(def_nearest_neighbor)
    {
        KDNode*tempNode = kdt->shortPath(kdt->root,point);
        this->temx=(*tempNode->coordK)[0];
        this->temy=(*tempNode->coordK)[1];
    }
    if(def_insert)
    {
        kdt->insertVecCoord(2,point);
    }


    emit Mouse_Pressed();
}

void FrameGL::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x()*(3.45);
    y = _h+65-(event->y()*3.45);
    emit Mouse_Pos();
}

void FrameGL::leaveEvent(QEvent *event)
{
    emit Mouse_Left();
}




