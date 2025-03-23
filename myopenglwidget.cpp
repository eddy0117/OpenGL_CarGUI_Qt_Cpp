#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent):QOpenGLWidget(parent) {

}

void debug_func(){
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    QOpenGLContext* context = QOpenGLContext::currentContext();
    if (context) {
        std::cout << "Qt OpenGL Context Version: "
                  << context->format().majorVersion() << "."
                  << context->format().minorVersion() << std::endl;
    } else {
        std::cerr << "Failed to get current OpenGL context!" << std::endl;
    }
}

void MyOpenGLWidget::initializeGL()
{
    // QSurfaceFormat format;
    // format.setRenderableType(QSurfaceFormat::OpenGLES); // 指定 OpenGL ES
    // format.setVersion(3, 0);  // 使用 OpenGL ES 3.0
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // QSurfaceFormat::setDefaultFormat(format);

    initializeOpenGLFunctions();
    // std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.0, 0.0, 0.0, 1.0);


    init_my_setup();
    set_camera();

    // debug_func();



}

void MyOpenGLWidget::init_my_setup()
{

    Factory* factory = new Factory(transformComponents);
    make_systems();

    // 產生 unordered map, key 是 obj name, value 是 (texture idx, VAO idx, vertex count)

    model_dict = factory->make_obj_list(file_path_list);
    color_dict = factory->make_color_list(colors_path_list);

    // Normal mode perspective
    factory->make_camera(cam_params_list);

    CameraComponent* camera = new CameraComponent();
    cameraComponent = camera;

    std::cout << "init shader" << std::endl;
    Shader* base_shader = new Shader(
        "../../src/shaders/vertex_base.vert",
        "../../src/shaders/fragment_base.frag");
    Shader* ego_car_shader = new Shader(
        "../../src/shaders/vertex_ego.vert",
        "../../src/shaders/fragment_ego_uni.frag");

    // 設定接下來繪製時要用的 shader 程式
    shader_dict.insert_or_assign("base", base_shader);
    shader_dict.insert_or_assign("ego", ego_car_shader);

    projection = glm::perspective(
        45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

    // set ego car position
    ego_car_pos.position = {5.0f, 0.0f, 0.0f};
    ego_car_pos.eulers = {0.0f, 0.0f, 0.0f};
}


void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGLWidget::paintGL()
{
    shader_dict["base"]->begin();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update_camera();

    draw_ego_car();

    if (!cur_frame_data.isEmpty()) {
        draw_objs();
        draw_lines();
        draw_occ_dots();
    }

    update();
}

void MyOpenGLWidget::switch_to_shader(Shader* target_shader) {
    glUseProgram(0);
    target_shader->begin();
}

void MyOpenGLWidget::make_systems() {
    cameraSystem = new CameraSystem();
    renderSystem = new RenderSystem(shader);
}

void MyOpenGLWidget::set_camera() {
    // 設定 view arr
    view_dict.insert_or_assign("normal", cameraSystem->get_updated_view(
                                             transformComponents, CamType::NORMAL, *cameraComponent, 16.67f/1000.0f));
    view_dict.insert_or_assign("BEV", cameraSystem->get_updated_view(
                                          transformComponents, CamType::BEV, *cameraComponent, 16.67f/1000.0f));

}

void MyOpenGLWidget::update_camera() {
    view = view_dict[mode];
    shader_dict["base"]->set_proj_view_mat(projection, view);
}
