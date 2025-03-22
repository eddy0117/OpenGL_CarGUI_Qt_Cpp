#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/transform_component.h"
#include "../view/shader.h"

class CameraSystem : public QOpenGLExtraFunctions{
public:

    CameraSystem();
    
    glm::mat4 get_updated_view(
        std::unordered_map<CamType,TransformComponent> &transformComponents,
        const CamType& cam_type, CameraComponent& cameraComponent, float dt);
    
private:
    unsigned int viewLocation;
    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    Shader* shader;
};
