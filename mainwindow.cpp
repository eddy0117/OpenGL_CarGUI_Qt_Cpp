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
        process_recv_data(queue_json.front());
        queue_json.pop();

        std::vector<uchar> img_data = base64Decode(cur_frame_data["img"].toObject()["CAM_FRONT"].toString().toStdString());
        cv::Mat img = cv::imdecode(img_data, cv::IMREAD_COLOR);
        cv::resize(img, img, cv::Size(211, 119));
        ui->img_front->setPixmap(convert_cv_qt(img));

        // 小數點後一位後截斷
        float speed = std::trunc(cur_frame_data["speed"].toString().toFloat() * 10) / 10.0f;
        ui->speedometer->setText(QString::number(speed));

    }


}

void MainWindow::setupUI() {
    std::thread socket_thread(&MainWindow::recv_data, this);
    socket_thread.detach(); // 讓線程獨立運行，不會受到 setupUI 的生命週期影響
    setupTimer();
    ui->speedometer->setText("0");

}

void MainWindow::setupTimer() {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateUI);
    timer->start(16); // 30fps
}

void MainWindow::update_image() {
    for (auto key : cur_frame_data["img"].toObject().keys()) {
        std::vector<uchar> img_data = base64Decode(cur_frame_data["img"]
                                                       .toObject()[key]
                                                       .toString()
                                                       .toStdString());
        cv::Mat img = cv::imdecode(img_data, cv::IMREAD_COLOR);
        cv::resize(img, img, cv::Size(211, 119));
        if (key == "CAM_FRONT") {
            ui->img_front->setPixmap(convert_cv_qt(img));
        } else if (key == "CAM_BACK") {
            ui->img_back->setPixmap(convert_cv_qt(img));
        }
    }
}

void MainWindow::process_recv_data(QJsonObject cur_frame_data) {
    this->cur_frame_data = cur_frame_data;
    ui->openGLWidget->cur_frame_data = cur_frame_data;
    update_image();
}


QPixmap MainWindow::convert_cv_qt(cv::Mat img){
    auto qt_img = QImage(img.data,
                         img.cols,
                         img.rows,
                         img.step, QImage::Format_BGR888);
    return QPixmap::fromImage(qt_img);
}

MainWindow::~MainWindow()
{
    delete ui;
}
