#include "mainwindow.h"
#include "src/config.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    // print_cur_dir();
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGLES); // 指定 OpenGL ES
    format.setVersion(3, 0);  // 使用 OpenGL ES 3.0
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);




    MainWindow app;

    // app.set_up_opengl();
    // app.make_systems();

    app.show();
    app.setupUI();
    return a.exec();
}
