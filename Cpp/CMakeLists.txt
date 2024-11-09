cmake_minimum_required(VERSION 3.10.0)
project(TaskManager)
cmake_policy(SET CMP0072 NEW)

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/imgui
${CMAKE_CURRENT_SOURCE_DIR}/src
${CMAKE_CURRENT_SOURCE_DIR}/src/common
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB IMGUI_SOURCES "imgui/*.cpp")
file(GLOB IMGUI_HEADERS "imgui/*.h")
file(GLOB TASK_MANAGER_SOURCES "src/*.cpp")
file(GLOB TASK_MANAGER_HEADERS "src/*.h")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wno-dev)
add_executable(TaskManager ${IMGUI_SOURCES} ${IMGUI_HEADERS}  ${TASK_MANAGER_SOURCES} ${TASK_MANAGER_HEADERS})
target_link_libraries(TaskManager  OpenGL glfw GLEW)
target_include_directories(TaskManager  PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/imgui
${CMAKE_CURRENT_SOURCE_DIR}/src
${CMAKE_CURRENT_SOURCE_DIR}/src/common
${OPENGL_INCLUDE_DIR}
${GLFW_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}

)
