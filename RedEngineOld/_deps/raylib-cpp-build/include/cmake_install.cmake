# Install script for directory: E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/raylib-cpp-example")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/AudioDevice.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/AudioStream.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/BoundingBox.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Camera2D.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Camera3D.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Color.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Font.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Functions.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Gamepad.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Image.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Material.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Matrix.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Mesh.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Model.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/ModelAnimation.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Mouse.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Music.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/physac.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Physics.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Ray.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/RayHitInfo.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/raylib-cpp-utils.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/raylib-cpp.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/raylib.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/raymath.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Rectangle.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/RenderTexture.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Shader.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Sound.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Text.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Texture.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Vector2.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Vector3.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Vector4.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/VrStereoConfig.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Wave.hpp"
    "E:/RedEngine/RedEngine/_deps/raylib-cpp-src/include/Window.hpp"
    )
endif()

