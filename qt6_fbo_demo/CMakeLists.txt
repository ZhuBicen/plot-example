cmake_minimum_required(VERSION 3.16)
project(qt6_fbo_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to Qt6
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${HOME}/qt/6.8.0/macos/lib/cmake")

# Find required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGL OpenGLWidgets)

# Set automatic moc, uic, and rcc processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add executable
add_executable(${PROJECT_NAME} main.cpp)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

# OS X specific settings
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()

