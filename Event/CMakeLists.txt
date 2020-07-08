cmake_minimum_required(VERSION 3.12)

project(VLSEvent VERSION 1.0.0)

set(VLS_CMAKE_DIR "${VLSCore_SOURCE_DIR}/cmake" CACHE STRING "Directory of VLS CMake extensions, set if VLSCore is added as CMake taget or included as Conan dependency" FORCE)

add_library(${PROJECT_NAME})

file(GLOB_RECURSE PUBLIC_HEADERS include/*.h)
target_sources(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS})

file(GLOB_RECURSE SOURCES src/*.cpp)#
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
option(VLS_TEST_EVENT "Event module unit tests" OFF)
if(NOT DEFINED VLS_TEST_ALL) 
    option(VLS_TEST_ALL "All VLS modules unit tests" OFF)
endif(NOT DEFINED VLS_TEST_ALL)

# Add tests directory.
if(VLS_TEST_ALL OR VLS_TEST_EVENT)
    add_subdirectory(test)
endif()

# Add options to enable examples
option(VLS_EXAMPLES_EVENT "Event module examples" OFF)
if(NOT DEFINED VLS_EXAMPLES_ALL) 
    option(VLS_EXAMPLES_ALL "All VLS modules examples" OFF)
endif(NOT DEFINED VLS_EXAMPLES_ALL)

# Add example directory.
if(VLS_EXAMPLES_ALL OR VLS_EXAMPLES_EVENT)
    add_subdirectory(examples)
endif()
