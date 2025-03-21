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
// #include <array>
#include <chrono>


// #include <nlohmann/json.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

#include <QSurfaceFormat>
#include <QOpenGLContext>
enum class CamType {
    NORMAL,
    BEV
};

std::vector<std::string> split(std::string line, std::string delimiter);

float cal_distance(std::pair<float, float> p1, std::pair<float, float> p2);


