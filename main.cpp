#include "mainwindow.h"
#include "src/config.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow app;

    // app.set_up_opengl();
    // app.make_systems();
    app.show();
    app.make_systems();
    return a.exec();
}
