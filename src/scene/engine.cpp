#include "engine.h"

void Engine::init() {

    m_renderer.init();
    m_camera.init();
    m_input_state.init();

    Services::provide<InputState> (&m_input_state);
    Services::provide<Renderer>   (&m_renderer   );
    Services::provide<Camera>     (&m_camera     );
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
    
}

void Engine::tick(float dt) {

    GLFWwindow* window = m_renderer.get_window();
    m_input_state.poll_input(window);
}

void Engine::shutdown() {
    m_renderer.shutdown();
}

Engine::Engine() = default;

