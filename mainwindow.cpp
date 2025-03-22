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
    // ui->openGLWidget->update();
    if (!queue_json.empty()) {
        ui->openGLWidget->cur_frame_data = queue_json.front();
        queue_json.pop();

        ui->speedometer->display(ui->openGLWidget->cur_frame_data["speed"].toString().toDouble());
    }


}

void MainWindow::setupUI() {
    std::thread socket_thread(&MainWindow::recv_data, this);
    socket_thread.detach(); // 讓線程獨立運行，不會受到 setupUI 的生命週期影響
    setupTimer();
    ui->speedometer->display(0);
}

void MainWindow::setupTimer() {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateUI);
    timer->start(16); // 30fps
}


MainWindow::~MainWindow()
{
    delete ui;
}
