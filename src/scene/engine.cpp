#include "engine.h"

void Engine::init() {

    m_renderer.init();
    m_camera.init();
    m_input_state.init();

    Services::provide<InputState> (&m_input_state);
    Services::provide<Renderer>   (&m_renderer   );
    Services::provide<Camera>     (&m_camera     );
    Services::provide<Scene>      (&m_scene      );

    m_models.reserve(100);
    load_models();
}

void Engine::load_models() {
    Model model;
    model.init("assets/models/test.obj");
    m_models.push_back(std::move(model));

    m_scene.add_object(
        &m_models.back(),
        "default",
        "none",
        glm::mat4(1.0f)
    );

    glm::mat4 temp = 
        glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 1.0f));
    ;
    m_scene.add_object(
        &m_models.back(),
        "default-blue",
        "none",
        temp
    );
}

void Engine::run() {
    init();

    m_running = true;
    float last_time = glfwGetTime();
    
    while (m_running && !m_renderer.should_close()) {
        float now = glfwGetTime();
        float dt = now - last_time;
        last_time = now;

        tick(dt);
    }
    shutdown();
}

void Engine::tick(float dt) {
    m_input_state.poll_input(m_renderer.get_window());

    m_scene.update(dt);

    m_camera.update(dt);
    m_renderer.update(dt);


    if (m_input_state.just_pressed(GLFW_KEY_ESCAPE)) { m_running = false; }
}

void Engine::shutdown() {
    m_running = false;
    m_renderer.shutdown();
    std::cout << "Goodbye :) \n";
}

Engine::Engine() = default;

