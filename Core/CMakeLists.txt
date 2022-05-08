cmake_minimum_required(VERSION 3.12)

project(VLSCore VERSION 1.0.0)

set(VLS_CMAKE_DIR "${VLSCore_SOURCE_DIR}/cmake" CACHE STRING "Directory of VLS CMake extensions, set if VLSCore is added as CMake taget or included as Conan dependency" FORCE)

add_library(${PROJECT_NAME})

file(GLOB_RECURSE PUBLIC_HEADERS include/*.h)
target_sources(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS})

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

file(GLOB_RECURSE SOURCE_HEADERS src/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include/ PRIVATE src/)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY 
        DESTINATION lib 
    ARCHIVE 
        DESTINATION lib
)

install(
    DIRECTORY include/ 
    DESTINATION include/
    FILES_MATCHING PATTERN "*.h"
)

# Add options to enable tests
option(VLS_TEST_CORE "Unit test of the core module" OFF)
if(NOT DEFINED VLS_TEST_ALL) 
    option(VLS_TEST_ALL "Unit test of all VLS modules" OFF)
endif(NOT DEFINED VLS_TEST_ALL)

# Add tests directory.
if(VLS_TEST_ALL OR VLS_TEST_CORE)
    add_subdirectory(test)
endif()
