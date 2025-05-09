cmake_minimum_required(VERSION 3.16)
project(qt_fbo_demo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(qt_fbo_demo
    main.cpp
    glwidget.h
    glwidget.cpp
)

target_link_libraries(qt_fbo_demo PRIVATE 
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

# For macOS, ensure the application bundle gets created
if(APPLE)
    set_target_properties(qt_fbo_demo PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()
