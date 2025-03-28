#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 直接建立 DataReceiveThread 並啟動，不再建立額外的 QThread
    DataReceiveThread* data_receive_worker = new DataReceiveThread();
    data_receive_worker->start();
    // 若需要使用 signal-slot 進行資料傳遞可取消註解：
    connect(data_receive_worker, &DataReceiveThread::cur_frame_data_signal,
            this, &MainWindow::process_recv_data);



    std::cout<<"MainWindow init"<<std::endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateUI() {
    // ui->openGLWidget->update();
    if (!cur_frame_data.empty()) {

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

