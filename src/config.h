#pragma once

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>

#include <fstream>
#include <sstream>
#include <string>

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <algorithm>
#include <chrono>

// OpenCV
#include <opencv2/opencv.hpp>

// Qt Json
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

// Qt OpenGL
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QSurfaceFormat>
#include <QOpenGLContext>

// Qt Utils
#include <QTimer>

// Debug
#include <unistd.h>
#include <limits.h>


enum class CamType {
    NORMAL,
    BEV
};

std::vector<std::string> split(std::string line, std::string delimiter);
std::vector<uchar> base64Decode(const std::string& base64Str);

float cal_distance(std::pair<float, float> p1, std::pair<float, float> p2);
void print_cur_dir();

