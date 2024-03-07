cmake_minimum_required(VERSION 3.10)

file(GLOB SOURCES "src/*.*")

add_executable(${PROJECT_NAME}Examples ${SOURCES} "src/main.cpp")

target_link_libraries(${PROJECT_NAME}Examples ${PROJECT_NAME})
