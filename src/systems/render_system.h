#pragma once
#include "../config.h"
#include "../components/transform_component.h"
#include "../components/render_component.h"

class RenderSystem : public QOpenGLExtraFunctions {
public:

    RenderSystem(unsigned int shader);
    

    
    void draw_model(
        RenderComponent& renderable, 
        TransformComponent& transform);

    void draw_model_ins_mat(
        RenderComponent& renderable, 
        TransformComponent& transform);

    void draw_line_dots(
        RenderComponent& renderable, 
        std::vector<TransformComponent>& positions);

    void draw_occ_dots(
        RenderComponent& renderable, 
        unsigned int color,
        std::vector<TransformComponent>& positions);

    
private:

    unsigned int modelLocation;

};
