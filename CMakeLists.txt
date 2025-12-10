cmake_minimum_required(VERSION 3.28)

# vcpkg integration
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

project(Asteroids VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SFML
find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System Audio)

# Create executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp  ${SOURCES})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)
