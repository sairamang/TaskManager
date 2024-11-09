#include "TaskManager.h"
#include "stdio.h"

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

TaskManager::TaskManager()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;
    // Create window with graphics context
    m_window = glfwCreateWindow(1280, 720, "Task Manager", nullptr, nullptr);
    if (m_window == nullptr)
        return;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL2_Init();
}
void TaskManager::render()
{

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w, m_clear_color.z * m_clear_color.w, m_clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    glfwMakeContextCurrent(m_window);
    glfwSwapBuffers(m_window);
}
void TaskManager::initialize_small_window()
{
    ImVec2 size = SMALL_WINDOW_SIZE;
    ImGui::SetWindowSize(size);
}
void TaskManager::runeventloop()
{
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    bool show_demo_window = false;
    bool show_another_window = false;
    bool show_task_manager = true;
    bool show_task_window = false;
    bool show_list_window = false;
    m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);               // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&m_clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Show Task Manager
        if (show_task_manager)
        {
            ImGui::Begin("DashBoard", &show_task_manager);
            ImVec2 Size = {1200 , 720};
            ImVec2 Pos = {10 , 20};
            ImGui::SetWindowSize(Size);
            ImGui::SetWindowPos(Pos);
            if (ImGui::Button("Create Task"))
            {
                show_task_window = true;
            }
            if (ImGui::Button("Create List"))
            {
                show_list_window = true;
            }
            ImGui::End();
        }

        if (show_task_window)
        {
            ImGui::Begin("Create Task", &show_task_window);
            char task_name[TEXT_SIZE] = {0};
            if (ImGui::InputText("Task Name", task_name, TEXT_SIZE, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                printf("Task Name entered %s \n", task_name);
            }
            ImGui::End();
        }

        if (show_list_window)
        {
            ImGui::Begin("Create List ", &show_list_window);
            initialize_small_window();
            char list_name[TEXT_SIZE] = {0};
            if (ImGui::InputText("List Name", list_name, TEXT_SIZE, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                printf("List Name %s \n", list_name);
            }
            ImGui::End();
        }

        render();
    }
}

TaskManager::~TaskManager()
{
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}