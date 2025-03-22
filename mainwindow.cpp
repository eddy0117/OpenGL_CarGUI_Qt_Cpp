#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // openGLWidget = new MyOpenGLWidget(parent);
    // setCentralWidget(ui->openGLWidget);

    // QSurfaceFormat format;
    // format.setRenderableType(QSurfaceFormat::OpenGLES); // 指定 OpenGL ES
    // format.setVersion(3, 0);  // 使用 OpenGL ES 3.0
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // QSurfaceFormat::setDefaultFormat(format);
    std::cout<<"MainWindow init"<<std::endl;

}

void MainWindow::updateUI() {
    ui->openGLWidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
