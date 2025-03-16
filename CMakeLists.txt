cmake_minimum_required(VERSION 3.14)
project(mapped VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build test programs" ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find required packages
find_package(Threads REQUIRED)

# Detect platform
if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DPLATFORM_LINUX)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/app.cpp
    src/ui/main_window.cpp
    src/core/data_model.cpp
    src/core/map_layer.cpp
    src/core/map_provider.cpp
)

# Add platform-specific source files
if(WIN32)
    list(APPEND SOURCES src/platform/platform_windows.cpp)
elseif(APPLE)
    list(APPEND SOURCES src/platform/platform_macos.cpp)
elseif(UNIX)
    list(APPEND SOURCES src/platform/platform_linux.cpp)
endif()

# Add resource files
file(GLOB_RECURSE RESOURCES
    resources/icons/*.png
    resources/images/*.jpg
    resources/translations/*.qm
    resources/map_styles/*.json
)

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Testing
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
