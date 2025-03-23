#include "config.h"
#include <cstddef>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::vector<std::string> split(std::string line, std::string delimiter) {

    std::vector<std::string> splitLine;

    size_t pos = 0;
    std::string token;
    while((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0,pos);
        splitLine.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    splitLine.push_back(line);

    return splitLine;
}

std::vector<uchar> base64Decode(const std::string& base64Str) {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::vector<uchar> decodedData;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;

    int val = 0, valb = -8;
    for (unsigned char c : base64Str) {
        if (T[c] == -1) break; // 遇到無效字元就停止
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            decodedData.push_back((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    return decodedData;
}


float cal_distance(std::pair<float, float> p1, std::pair<float, float> p2) {
  
   
    float distance = sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    return distance;
}

void print_cur_dir() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}

