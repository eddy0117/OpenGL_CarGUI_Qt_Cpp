#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include "src/config.h"

#include <QMouseEvent>

#include "src/components/camera_component.h"
#include "src/components/render_component.h"
#include "src/components/transform_component.h"
#include "src/systems/camera_system.h"
#include "src/systems/render_system.h"
#include "src/factories/factory.h"
#include "mainwindow.h"



class MyOpenGLWidget : public QOpenGLWidget, QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    ~MyOpenGLWidget();
    QJsonObject cur_frame_data; // 從 MainWindow 傳入的當前 frame 的資料
    std::vector<float> consume_time_list;

private:
    // OpenGL widget essential methods
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    // Build-up functions
    void init_my_setup();
    void make_systems();

    // Drawing functions
    void switch_to_shader(Shader* target_shader);
    void set_up_glfw();
    void clear_last_frame_data();
    void draw_objs();
    void draw_lines();
    void draw_ego_car();
    void draw_ego_car_BEV();
    void show_ego_car();
    void draw_occ_dots();
    std::vector<TransformComponent> line_interpolation(
        std::vector<TransformComponent>& positions,
        int num_points);

    // Component setting functions
    void set_camera();
    void update_camera();

    // Other functions
    void waitForEvent();

    // Member variables

    unsigned int shader;
    std::string mode = "normal";
    bool KeyPressed = false;

    GLfloat tempArray[MAX_LIGHTS];

    // 將投影矩陣和視圖矩陣宣告為成員變數，方便使用

    std::vector<std::unordered_map<std::string, std::string>> cur_frame_objs;
    std::vector<std::unordered_map<std::string, std::string>> cur_frame_dots;
    std::vector<std::pair<float, std::pair<float, float>>> dangerous_objs;



    //Systems
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;

    //Components
    std::unordered_map<CamType, TransformComponent> transformComponents;
    CameraComponent* cameraComponent;
    unsigned int cameraID;
    std::unordered_map<std::string, RenderComponent> model_dict;
    std::unordered_map<std::string, unsigned int> color_dict;

    glm::mat4 projection;
    glm::mat4 view;

    std::unordered_map<std::string, Shader*> shader_dict;
    std::unordered_map<std::string, glm::mat4> view_dict;

    TransformComponent ego_car_pos;

    // Resources
    std::unordered_map<std::string, std::string> colors_path_list = {
        {"0", "0_0_0.png"},
        {"1", "255_120_50.png"},
        {"2", "255_192_203.png"},
        {"3", "255_255_0.png"},
        {"4", "0_150_245.png"},
        {"5", "0_255_255.png"},
        {"6", "255_127_0.png"},
        {"7", "255_0_0.png"},
        {"8", "255_240_150.png"},
        {"9", "135_60_0.png"},
        {"10", "160_32_240.png"},
        {"11", "50_50_50.png"},
        {"12", "139_137_137.png"},
        {"13", "75_0_75.png"},
        {"14", "150_240_80.png"},
        {"15", "230_230_250.png"},
        {"16", "0_175_0.png"},
    };

    std::unordered_map<std::string, std::vector<std::string>> file_path_list = {
        {"ego_car", {"SUV.obj", "SUV.jpg"}},
        // {"pedestrian", {"walking_person.obj", "walking_person.jpg"}},
        {"pedestrian", {"new/pedestrian.obj", "new/pedestrian.jpg"}},
        {"motorcycyle", {"new/scooter.obj", "new/scooter.jpg"}},
        {"truck", {"new/truck.obj", "new/truck.jpg"}},
        {"bus", {"bus.obj", "bus.jpg"}},
        {"traffic_cone", {"cone.obj", "cone.png"}},
        {"car", {"new/sedan.obj", "new/sedan.jpg"}},
        {"0", {"cube.obj", "side.png"}},
        {"1", {"cube.obj", "crossroad.png"}},
        {"2", {"cube.obj", "roadline.png"}},
        {"occ_dot", {"cube4m.obj", "cube4m_frame.png"}}

    };

    std::vector<std::tuple<glm::vec3, glm::vec3, CamType>> cam_params_list = {
        {{-5.0f, 0.0f, 5.0f}, {0.0f, -15.0f, 0.0f}, CamType::NORMAL},
        {{5.0f, 0.0f, 7.0f}, {0.0f, -89.0f, 0.0f}, CamType::BEV}
    };

protected:
    void mousePressEvent(QMouseEvent *event) override;

    // void mouseMoveEvent(QMouseEvent *event) override;

    // void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void eventOccurred();

};

#endif // MYOPENGLWIDGET_H
