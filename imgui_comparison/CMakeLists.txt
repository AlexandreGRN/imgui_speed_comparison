cmake_minimum_required(VERSION 3.18)
project(dear-imgui-conan2 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# CONFIG option is important so that CMake doesnt search for modules into the default modules directory
find_package(imgui CONFIG)
find_package(glfw3 CONFIG)
find_package(glew CONFIG)

add_executable( dear-imgui-conan2
                main.cpp
                opengl_shader.cpp
                file_manager.cpp
                opengl_shader.h
                file_manager.h
                bindings/imgui_impl_glfw.cpp
                bindings/imgui_impl_opengl3.cpp
                bindings/imgui_impl_glfw.h
                bindings/imgui_impl_opengl3.h
                assets/simple-shader.vs
                assets/simple-shader.fs )

target_compile_definitions(dear-imgui-conan2 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(dear-imgui-conan2 imgui::imgui GLEW::glew_s glfw::glfw ${CONAN_LIBS})
