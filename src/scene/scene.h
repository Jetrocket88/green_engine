#ifndef SCENE_H
#define SCENE_H

#include "../renderer/model.h"
#include "../renderer/renderer.h"
#include "../core/services.h"

#include <vector>

class Scene {

public:
    void add_object(Model* model, std::string shader, std::string texture, const glm::mat4& transform);
    void update(float dt);

private:
    std::vector<DrawCall> m_objects;
};

#endif //SCENE_H
