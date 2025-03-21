#include "factory.h"
#include "../stb_image.h"

Factory::Factory(
    std::unordered_map<CamType, TransformComponent>& transformComponents):
    transformComponents(transformComponents) {
    initializeOpenGLFunctions();
}

Factory::~Factory() {
    glDeleteBuffers(VBOs.size(), VBOs.data());
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    glDeleteTextures(textures.size(), textures.data());
}

void Factory::make_camera(std::vector<std::tuple<glm::vec3, glm::vec3, CamType>> cam_params_list) {

    for (const auto& cam_params : cam_params_list) {
        glm::vec3 position = std::get<0>(cam_params);
        glm::vec3 eulers = std::get<1>(cam_params);
        CamType cam_type = std::get<2>(cam_params);
        
        TransformComponent transform;
        transform.position = position;
        transform.eulers = eulers;

        transformComponents[cam_type] = transform;

    }
    

    
}


// 產出多個物件的 VAO, texture的 dict
std::unordered_map<std::string, RenderComponent> Factory::make_obj_list(std::unordered_map<std::string, 
                                                                        std::vector<std::string>>& file_path_list) {

    std::unordered_map<std::string, RenderComponent> model_dict;
    glm::mat4 preTransform = glm::mat4(0.8f);
	preTransform = glm::rotate(preTransform, 
        glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });// 繞 x 軸轉90度
    preTransform = glm::rotate(preTransform, 
        glm::radians(90.0f), { 0.0f, 1.0f, 0.0f });// 繞 y 軸轉90度

    for(const auto& [cls, paths] : file_path_list){
        std::string obj_path = paths[0];
        std::string img_path = paths[1];

        RenderComponent render = make_obj_mesh((model_path_prefix + obj_path).c_str(), preTransform);
        render.material = make_texture((img_path_prefix + img_path).c_str());
        model_dict[cls] = render;
    }
    return model_dict; 
}

// 讀取 .obj 檔案， 建立 OpenGL 的 VAO 和 VBO,將模型數據傳送到 GPU ， 回傳包含 VAO 與頂點數量的 RenderComponent
RenderComponent Factory::make_obj_mesh(
    const char* filepath, glm::mat4 preTransform) {

    std::vector<glm::vec3> v;   // 頂點位置
    std::vector<glm::vec2> vt;  // 紋理座標
    std::vector<glm::vec3> vn;  // 法向量
    std::vector<float> vertices; // 展平後的頂點數據 （位置、UV、法向量）

    size_t vertexCount = 0;
    size_t texcoordCount = 0;
    size_t normalCount = 0;
    size_t triangleCount = 0;

    std::string line;
    std::vector<std::string> words;

    std::ifstream file;

    file.open(filepath);
    //解析 3D 模型檔案資料 並存入對應的容器
    while (std::getline(file, line)) {
        words = split(line, " ");

        if (!words[0].compare("v")) {
            v.push_back(read_vec3(words, preTransform, 1.0f));// 解析頂點
        } 
        else if (!words[0].compare("vt")) {
            vt.push_back(read_vec2(words));// 紋理座標
        } 
        else if (!words[0].compare("vn")) {
            vn.push_back(read_vec3(words, preTransform, 0.0f));// 法向量
        } 
        else if (!words[0].compare("f")) {
            read_face(words, v, vt, vn, vertices);// 資料
        }
    }
    file.close();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    VBOs.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), 
        vertices.data(), GL_STATIC_DRAW);
    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    //texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    //normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    
    RenderComponent render;
    render.VAO = VAO;
    render.vertexCount = vertices.size() / 8;
    return render;
}



glm::vec3 Factory::read_vec3(std::vector<std::string> words,
    glm::mat4 preTransform, float w) {
    return glm::vec3(
        preTransform 
        * glm::vec4(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]), w)
    );
}

glm::vec2 Factory::read_vec2(std::vector<std::string> words) {
    return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}

void Factory::read_face(std::vector<std::string> words, 
    std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, 
    std::vector<glm::vec3>& vn, std::vector<float>& vertices) {
    
    size_t triangleCount = words.size() - 3; // 計算需要建立多少個三角形

    for (size_t i = 0; i < triangleCount; ++i) {
        read_corner(words[1], v, vt, vn, vertices);
        read_corner(words[2 + i], v, vt, vn, vertices);
        read_corner(words[3 + i], v, vt, vn, vertices);
    }

}

// read_corner 函式將 .obj 檔案中的頂點、UV、法向量資訊解析並整合進 vertices
void Factory::read_corner(std::string description, 
    std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, 
    std::vector<glm::vec3>& vn, std::vector<float>& vertices) {
    
    std::vector<std::string> v_vt_vn = split(description, "/");

    //position
    glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
    vertices.push_back(pos[0]);
    vertices.push_back(pos[1]);
    vertices.push_back(pos[2]);

    //tex coord (UV)
    glm::vec2 texcoord = vt[std::stol(v_vt_vn[1]) - 1];
    vertices.push_back(texcoord[0]);
    vertices.push_back(texcoord[1]);

    //normal
    glm::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
    vertices.push_back(normal[0]);
    vertices.push_back(normal[1]);
    vertices.push_back(normal[2]);

}

// 載入材質貼圖
unsigned int Factory::make_texture(const char* filename) {

    int width, height, channels;

    // stbi 設定讀取時垂直翻轉圖片, 由於 OpenGL UV coords 是以左下角為 (0, 0)
    stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(
        filename, &width, &height, &channels, STBI_rgb_alpha);
	//make the texture
    unsigned int texture;
	glGenTextures(1, &texture);
    textures.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	
    //load data
    glTexImage2D(GL_TEXTURE_2D, 
        0, GL_RGBA, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free data
	stbi_image_free(data);

    //Configure sampler
    // 在 U 方向和 V 方向上分別設定 Wrapping (U = S, V = T)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 上採樣 filter 使用 linear interpolation , 下採樣 filter 使用 nearest
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

std::unordered_map<std::string, unsigned int> Factory::make_color_list(
        std::unordered_map<std::string, std::string>& colors_path_list) {

    std::unordered_map<std::string, unsigned int> color_dict;

    for(const auto& [cls, path] : colors_path_list) {
        color_dict[cls] = make_texture((img_path_prefix + path).c_str());
    }
    return color_dict;
}
