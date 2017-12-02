#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

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
}

void MainWindow::Mouse_Pressed()
{
}

void MainWindow::Mouse_left()
{
}



