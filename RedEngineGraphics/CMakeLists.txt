cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(RedEngineGraphics)

# RedLib
find_library(RedLib RedLib)
add_subdirectory(../RedLib ../RedLib-build)

# GLFW
find_library(glfw glfw)
set(_GLFW_WIN32 true)
add_subdirectory(../glfw-3.3.7/src ../glfw-3.3.7/out/build/x64-Debug/src)

# This is the main part:
include_directories("Header Files" "Source Files" "../RedLib/Header Files")
set(PROJECT_NAME RedEngineGraphics)
set(PROJECT_SOURCES "Source Files/glad.c" "Source Files/GraphicsSystem.cpp" "Source Files/Mesh2D.cpp" "Source Files/Shader.cpp" "Source Files/ShaderProgram.cpp" "Source Files/main.cpp")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set(raylib_VERBOSE 1)
target_include_directories(RedEngineGraphics PUBLIC ../RedLib ../RedLib-build ../glfw-3.3.7/src)
target_link_libraries(${PROJECT_NAME} PUBLIC RedLib glfw)
# That's it! You should have an example executable that you can run. Have fun!
