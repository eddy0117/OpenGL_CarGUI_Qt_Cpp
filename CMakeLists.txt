cmake_minimum_required(VERSION 3.16)

project(SmartDashboardSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# cmake_policy(SET CMP0072 NEW)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # multithreading support


set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        # header files

        myopenglwidget.h
        src/config.h
        src/stb_image.h
        src/components/camera_component.h
        src/components/render_component.h
        src/components/transform_component.h
        src/factories/factory.h
        src/systems/camera_system.h
        src/systems/render_system.h
        src/threads/socket_thread.h
        src/view/shader.h
        # src/controller/app.h

        # source files
        myopenglwidget.cpp
        src/config.cpp
        src/glad.cpp
        src/factories/factory.cpp
        src/systems/camera_system.cpp
        src/systems/render_system.cpp
        src/threads/socket_thread.cpp
        src/view/shader.cpp
        # src/controller/app.cpp
        # src/controller/drawing.cpp

        # shader
        src/shaders/vertex_base.vert
        src/shaders/vertex_ego.vert
        src/shaders/fragment_base.frag
        src/shaders/fragment_ego_uni.frag

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartDashboardSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        # myopenglwidget.h myopenglwidget.cpp
        # src/glad.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartDashboardSystem APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartDashboardSystem SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartDashboardSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(SmartDashboardSystem
    PRIVATE
    dependencies
)

target_link_libraries(SmartDashboardSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    glfw
    OpenGL::GL ${CMAKE_DL_LIBS}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    # Qt6::OpenGL
    Qt6::OpenGLWidgets
    # Qt6::Json
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SmartDashboardSystem)
endif()
set_target_properties(SmartDashboardSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SmartDashboardSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartDashboardSystem)
endif()

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)
