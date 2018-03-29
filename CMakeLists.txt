cmake_minimum_required (VERSION 3.5)

project (caketracer)

option(YOCTO_NO_OPENGL "Skip OpenGL apps" OFF)
option(YOCTO_CPP11 "Compile as C++11" OFF)

if(NOT YOCTO_CPP11)
    set(CMAKE_CXX_STANDARD 14)
else(NOT YOCTO_CPP11)
    set(CMAKE_CXX_STANDARD 11)
endif(NOT YOCTO_CPP11)

set(CMAKE_CXX_STANDARD_REQUIRED on)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# compile flags
if(APPLE)
    add_definitions(-Wno-missing-braces)
endif(APPLE)
if(WIN32)
    add_definitions(/D_CRT_SECURE_NO_WARNINGS /wd4018 /wd4244 /wd4305 /wd4800 /wd4267)
endif(WIN32)

if(NOT YOCTO_NO_OPENGL)
    # opengl
    find_package(OpenGL REQUIRED)

    # opengl support libaries
    if(APPLE)
        include_directories(/usr/local/include)
        link_directories(/usr/local/lib)
        find_library(GLFW_LIBRARY NAMES glfw3 glfw PATHS /usr/local/lib)
    endif(APPLE)
    if(WIN32)
        include_directories(${CMAKE_SOURCE_DIR}/apps/w32/include)
        link_directories(${CMAKE_SOURCE_DIR}/apps/w32/lib/lib-vc2015)
        find_library(GLEW_LIBRARIES NAMES glew32 PATHS ${CMAKE_SOURCE_DIR}/apps/w32/lib-vc2015)
        find_library(GLFW_LIBRARY NAMES glfw3dll PATHS ${CMAKE_SOURCE_DIR}/apps/w32/lib-vc2015)
    endif(WIN32)
    if(UNIX AND NOT APPLE)
        include_directories(/usr/include /usr/local/include)
        find_library(GLFW_LIBRARY NAMES glfw3 glfw PATHS /usr/lib /usr/local/lib64 /usr/lib64 /usr/local/lib /usr/lib/x86_64-linux-gnu)
        find_package(GLEW REQUIRED)
    endif(UNIX AND NOT APPLE)
endif(NOT YOCTO_NO_OPENGL)

set(yocto_files
        yocto/yocto_gl.h
        yocto/yocto_gl.cpp
        yocto/ext/nanosvg.cpp
        yocto/ext/stb_image.cpp
        yocto/ext/imgui/imgui.cpp
        yocto/ext/imgui/imgui_draw.cpp
        yocto/ext/imgui/imgui_demo.cpp
        yocto/ext/imgui/imgui_impl_glfw_gl3.cpp
        yocto/ext/imgui/imgui_extra_fonts.cpp
        )

add_library(yocto_lib STATIC ${yocto_files})

if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(yocto Threads::Threads)
endif(UNIX AND NOT APPLE)

if(NOT YOCTO_NO_OPENGL)
    target_link_libraries(yocto_lib ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARY} ${GLEW_LIBRARIES})
endif(NOT YOCTO_NO_OPENGL)


add_library(tracer_lib STATIC trace.cpp trace.h)
target_link_libraries(tracer_lib yocto_lib)

add_executable(viewer viewer.cpp)

target_link_libraries(viewer tracer_lib)