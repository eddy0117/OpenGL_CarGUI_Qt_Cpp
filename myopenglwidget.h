#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include "src/config.h"

// #include "src/controller/app.h"

#include "src/components/camera_component.h"
#include "src/components/render_component.h"
#include "src/components/transform_component.h"

#include "src/factories/factory.h"
#include "mainwindow.h"



class MyOpenGLWidget : public QOpenGLWidget, QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    void init_my_setup(MainWindow* app);
private:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

};

#endif // MYOPENGLWIDGET_H
