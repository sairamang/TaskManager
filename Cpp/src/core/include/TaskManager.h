#pragma once    
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <GLFW/glfw3.h>

#define TEXT_SIZE 30
#define SMALL_WINDOW_SIZE {240 , 80} 
#define SPAWN_POS {600, 100}
class TaskManager {
public: 
    TaskManager();
    ~TaskManager();
    void runeventloop();
    void render();
    void initialize_small_window();
private:
GLFWwindow *m_window;
ImVec4 m_clear_color;
};


