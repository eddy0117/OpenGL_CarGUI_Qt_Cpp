#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/config.h"


#include "src/components/camera_component.h"
#include "src/components/render_component.h"
#include "src/components/transform_component.h"

#include "src/systems/camera_system.h"
#include "src/systems/render_system.h"

#include "src/view/shader.h"

#include "src/threads/socket_thread.h"

#include <QMainWindow>
#include <qopenglfunctions.h>
// #include "myopenglwidget.h"

// 同步相關
#include <mutex>
#include <condition_variable>
#include <atomic>

#define MAX_LIGHTS 30
#define OBJ_SCALE 40
#define LINE_SCALE 35
#define MAX_DANGER_DISTANCE 8.0f


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void run();
    void set_up_opengl();
    void make_systems();

    void setupUI();


private:
    Ui::MainWindow *ui;

    QWindow* window;

    unsigned int shader;
    std::string mode = "normal";
    bool KeyPressed = false;

    QJsonObject cur_frame_data;
    // std::vector<std::vector<uchar>> cam_img_arr;

    //Systems
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;

    //＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
    std::queue<QJsonObject> queue_json;  // 生產者佇列

    // 多執行緒同步資源
    std::mutex g_mtx;
    std::condition_variable g_cv;
    std::atomic<bool> g_done{false};  // 建議使用{}


    // 記錄 Producer 通知時間與 Consumer 處理時間
    std::unordered_map<int, std::chrono::high_resolution_clock::time_point> g_notify_times;

    // Threads
    QThread* thread_container = nullptr;
    void recv_data();

    // Qt methods
    void updateUI();
    void setupTimer();

    // GUI methods
    void update_image();

    // Helper methods
    void process_recv_data(QJsonObject cur_frame_data);
    QPixmap convert_cv_qt(cv::Mat img);
};
#endif // MAINWINDOW_H
