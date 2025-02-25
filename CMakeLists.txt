cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(HelloTriangle CXX)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SOURCES
    ${SOURCES_DIR}/main.cpp
    ${SOURCES_DIR}/HelloTriangleApp.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    glfw
    vulkan
)