#include "renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    auto* renderer = Services::get<Renderer>();
    renderer->set_window_width (width);
    renderer->set_window_height(height);
    glViewport(0, 0, width, height);
}

void Renderer::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_window_width, m_window_height, "My Engine", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }  

    if (!m_window) {
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetInputMode(m_window , GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* w, double x, double y) {
        auto* cam = Services::get<Camera>();
        cam->on_mouse_move(x, y);
    });

    load_shader("default", "assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
    load_shader("default-blue", "assets/shaders/vertex.shader", "assets/shaders/fragment-blue.shader");
}

void Renderer::load_shader(
    const std::string& name,
    const std::string& vPath,
    const std::string& fPath) 
{
    auto shader = std::make_unique<Shader>();
    shader->init(vPath, fPath);
    m_shaders[name] = std::move(shader); 
}

Shader *Renderer::get_shader(const std::string& name) {
    auto it = m_shaders.find(name);
    if (it == m_shaders.end()) {
        std::cout << "Shader not found :( \n";
        return nullptr;
    }
    return it->second.get();
}

void Renderer::update(float dt) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCheckError("Gl clear");

    Shader* active_shader = nullptr;
    Camera* camera = Services::get<Camera>();
    glm::mat4 view, projection;

    for (auto& call : m_draw_queue) {
        Shader* shader = get_shader(call.shader);
        if (!shader) continue;

        if (shader != active_shader) {
            shader->bind();
            view       = camera->get_view_matrix();
            projection = camera->get_projection_matrix();
            shader->set_mat4f("view",       &view      );
            shader->set_mat4f("projection", &projection);
            active_shader = shader;
            glCheckError("Changing shader to active_shader");
        }
        shader->set_mat4f("model", &call.transform);
        glCheckError("Setting the call.transform matrix");
        call.model->bind();
        glCheckError("After binding the call.model");
        glDrawArrays(GL_TRIANGLES, 0, call.model->index_count());

        glCheckError("After drawing");
    }

    m_draw_queue.clear();
    glfwSwapBuffers(m_window);
}


void Renderer::shutdown() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

Renderer::Renderer() = default;

void Renderer::submit(const Model* model, std::string shader, std::string texture, const glm::mat4& transform) {
    m_draw_queue.push_back((DrawCall){model, shader, texture, transform});
}
