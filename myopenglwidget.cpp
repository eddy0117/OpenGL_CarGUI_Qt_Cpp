#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent):QOpenGLWidget(parent) {

}

void MyOpenGLWidget::initializeGL()
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGLES); // 指定 OpenGL ES
    format.setVersion(3, 0);  // 使用 OpenGL ES 3.0
    format.setProfile(QSurfaceFormat::CoreProfile);
    // QSurfaceFormat::setDefaultFormat(format);

    initializeOpenGLFunctions();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

}

void MyOpenGLWidget::init_my_setup(MainWindow* app)
{
    Factory* factory = new Factory(app->transformComponents);

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

    // 產生 unordered map, key 是 obj name, value 是 (texture idx, VAO idx, vertex count)
    unsigned int fakeVAO;
    glGenVertexArrays(1, &fakeVAO);
    app->model_dict = factory->make_obj_list(file_path_list);
    app->color_dict = factory->make_color_list(colors_path_list);

    // Normal mode perspective
    // factory->make_camera(cam_params_list);


    CameraComponent* camera = new CameraComponent();


    app->cameraComponent = camera;
}


void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

}
