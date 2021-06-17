# Install script for directory: /home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/AudioDevice.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/AudioStream.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/BoundingBox.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Camera2D.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Camera3D.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Color.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Font.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Functions.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Gamepad.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Image.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Material.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Matrix.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Mesh.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Model.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/ModelAnimation.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Mouse.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Music.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/physac.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Physics.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Ray.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/RayHitInfo.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/raylib-cpp-utils.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/raylib-cpp.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/raylib.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/raymath.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Rectangle.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/RenderTexture.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Shader.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Sound.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Text.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Texture.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Vector2.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Vector3.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Vector4.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/VrStereoConfig.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Wave.hpp"
    "/home/redy9567/RedEngine/SampleGame-build/_deps/raylib-cpp-src/include/Window.hpp"
    )
endif()

