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
void MainWindow::make_systems() {
    ui->openGLWidget->init_my_setup(this);
    cameraSystem = new CameraSystem(window);
    renderSystem = new RenderSystem(shader, window);
}

MainWindow::~MainWindow()
{
    delete ui;
}
