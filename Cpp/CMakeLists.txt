cmake_minimum_required(VERSION 3.10.0)
project(TaskManager)
cmake_policy(SET CMP0072 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
# Fetch Google Test 
include(FetchContent)
# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
SET (
RAPIDJSON_HEADER 
${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/
${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/error 
${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/internal 
${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/msinttypes
)
set (
TASK_MANAGER_INC
src/core/include
src/conf/include
src/datastore/include
src/utils/include
)
include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/imgui
${CMAKE_CURRENT_SOURCE_DIR}/src
${TASK_MANAGER_INC}
${RAPIDJSON_HEADER}
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file (COPY ${CMAKE_SOURCE_DIR}/resources/TaskManager.json DESTINATION ${CMAKE_BINARY_DIR})
file (COPY ${CMAKE_SOURCE_DIR}/resources/TaskData.json DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB IMGUI_SOURCES "imgui/*.cpp")
file(GLOB IMGUI_HEADERS "imgui/*.h")
set (TASK_MANAGER_SOURCES 
src/core/src/TaskManager.cpp
src/conf/src/TaskManagerConfig.cpp
src/datastore/src/TaskDataHandler.cpp
src/datastore/src/TaskDataStore.cpp 
src/utils/src/JSONHelper.cpp
src/main.cpp
)
set(TASK_MANAGER_HEADERS 
src/core/include/TaskManager.h
src/conf/include/TaskManagerConfig.h
src/datastore/include/TaskDataHandler.h
src/datastore/include/TaskDataModel.h
src/datastore/include/TaskDataStore.h
src/utils/include/JSONHelper.h
)


set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wno-dev)
add_executable(TaskManager ${IMGUI_SOURCES} ${IMGUI_HEADERS}  ${TASK_MANAGER_SOURCES} ${TASK_MANAGER_HEADERS})
add_library(TaskManager_lib STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS}  ${TASK_MANAGER_SOURCES} ${TASK_MANAGER_HEADERS})
target_link_libraries(TaskManager  OpenGL glfw GLEW)
target_include_directories(TaskManager  PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/imgui
${TASK_MANAGER_INC}
${OPENGL_INCLUDE_DIR}
${GLFW_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}
${RAPIDJSON_HEADER}
)
target_link_libraries(TaskManager_lib  OpenGL glfw GLEW)
target_include_directories(TaskManager_lib  PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/imgui
${TASK_MANAGER_INC}
${OPENGL_INCLUDE_DIR}
${GLFW_INCLUDE_DIR}
${GLEW_INCLUDE_DIR}
${RAPIDJSON_HEADER}
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)


