cmake_minimum_required(VERSION 3.20)

project(imgui-speed-comparison C CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(bindings)

add_executable(imgui-speed-comparison src/main.cpp src/Window/Window.cpp)
target_link_libraries(imgui-speed-comparison ${CONAN_LIBS})
target_link_libraries(imgui-speed-comparison imgui implot ${CONAN_LIBS})
