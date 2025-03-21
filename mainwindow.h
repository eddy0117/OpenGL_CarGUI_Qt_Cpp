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

    //Components
    std::unordered_map<CamType, TransformComponent> transformComponents;
    CameraComponent* cameraComponent;
    unsigned int cameraID;
    std::unordered_map<std::string, RenderComponent> model_dict;
    std::unordered_map<std::string, unsigned int> color_dict;

private:
    Ui::MainWindow *ui;
    // MyOpenGLWidget* openGLWidget;

    void set_up_glfw();
    void clear_last_frame_data();
    void show_ego_car();
    void draw_objs();
    void draw_lines();
    void draw_ego_car();
    void draw_ego_car_BEV();
    void draw_occ_dots();

    void recv_data(); // 改為成員函式
    void set_camera();
    void update_camera();

    std::vector<TransformComponent> line_interpolation(
        std::vector<TransformComponent>& positions,
        int num_points);

    QWindow* window;

    unsigned int shader;
    std::string mode = "normal";
    bool KeyPressed = false;

    GLfloat tempArray[MAX_LIGHTS];

    // 將投影矩陣和視圖矩陣宣告為成員變數，方便使用
    glm::mat4 projection;
    glm::mat4 view;

    std::vector<std::unordered_map<std::string, std::string>> cur_frame_objs;
    std::vector<std::unordered_map<std::string, std::string>> cur_frame_dots;
    std::vector<std::pair<float, std::pair<float, float>>> dangerous_objs;

    std::unordered_map<std::string, Shader*> shader_dict;
    std::unordered_map<std::string, glm::mat4> view_dict;
    // std::queue<nlohmann::json> queue_json;
    // nlohmann::json cur_frame_data;
    QJsonObject cur_frame_data;

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
    TransformComponent ego_car_pos;

};
#endif // MAINWINDOW_H
