#include "engine.h"

void Engine::init() {

    m_renderer.init();
    m_camera.init();
    m_input_state.init();

    Services::provide<InputState> (&m_input_state);
    Services::provide<Renderer>   (&m_renderer   );
    Services::provide<Camera>     (&m_camera     );

    load_models();
}

void Engine::load_models() {
    m_temp.init("assets/models/test.obj");
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

    m_renderer.submit(&m_temp, "default", glm::mat4(1.0f));
    m_renderer.submit(&m_temp, "default-blue", glm::mat4(0.1f));

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

