#include "scene.h"

void Scene::add_object(Model* model, std::string shader, std::string texture, const glm::mat4& transform) {
    m_objects.push_back({model, shader, texture, transform});
}

void Scene::update(float dt) {
    auto* renderer = Services::get<Renderer>();
    for (auto& obj : m_objects) {
        renderer->submit(obj.model, obj.shader, obj.texture, obj.transform);
    }
}





