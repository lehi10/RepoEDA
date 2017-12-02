#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "framegl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openGLWidget,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->openGLWidget,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->openGLWidget,SIGNAL(Mouse_Left()),this,SLOT(Mouse_left()));


}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::Mouse_current_pos()
{

    //cout<<ui->openGLWidget->x<<endl;
}

void MainWindow::Mouse_Pressed()
{
    //cout<<ui->openGLWidget->x<<endl;
}

void MainWindow::Mouse_left()
{
    //cout<<ui->openGLWidget->x<<endl;
}




