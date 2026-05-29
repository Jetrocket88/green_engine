#ifndef ENGINE_H
#define ENGINE_H

#include "core/services.h"
#include "core/input_state.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"

enum class GameState { Playing, Paused, MainMenu, GameOver };

class Engine {
public:
    Engine();
    void init();
    void run();
    void shutdown();
private:
    void tick(float dt);

    InputState m_input_state;
    Renderer   m_renderer;
    Camera     m_camera;
    bool m_running = false;
};

#endif //ENGINE_H
