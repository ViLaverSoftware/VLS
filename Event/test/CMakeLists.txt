cmake_minimum_required(VERSION 3.10)

include("VLSConan.cmake")

file(GLOB SOURCES "src/*.cpp")

add_executable(UnitTest${PROJECT_NAME} ${SOURCES})

target_link_libraries(UnitTest${PROJECT_NAME} ${PROJECT_NAME} ${CONAN_LIBS})

# Google test has different targets for debug and release builds
target_link_libraries(UnitTest${PROJECT_NAME} debug gtestd debug gtest_maind)       # debug
target_link_libraries(UnitTest${PROJECT_NAME} optimized gtest optimized gtest_main) # release

include(GoogleTest)

gtest_add_tests(TARGET UnitTest${PROJECT_NAME})
