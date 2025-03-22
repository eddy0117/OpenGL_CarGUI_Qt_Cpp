#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include "src/config.h"

// #include "src/controller/app.h"

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
    QJsonObject cur_frame_data; // 從 MainWindow 傳入的當前 frame 的資料

private:
    // OpenGL widget essential methods
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    // Build-up functions
    void init_my_setup();
    void make_systems();

    // Drawing functions
    void switch_to_shader(Shader* target_shader);
    void set_up_glfw();
    void clear_last_frame_data();
    void show_ego_car();
    void draw_objs();
    void draw_lines();
    void draw_ego_car();
    void draw_ego_car_BEV();
    void draw_occ_dots();
    std::vector<TransformComponent> line_interpolation(
        std::vector<TransformComponent>& positions,
        int num_points);

    // Component setting functions
    void set_camera();
    void update_camera();


    // Member variables
    // 將 MainWindow 實例傳入
    MainWindow* app;
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

    // 需要在 myopenglwidget.cpp 被調用
    glm::mat4 projection;
    glm::mat4 view;

    std::unordered_map<std::string, Shader*> shader_dict;
    std::unordered_map<std::string, glm::mat4> view_dict;

    TransformComponent ego_car_pos;


};

#endif // MYOPENGLWIDGET_H
