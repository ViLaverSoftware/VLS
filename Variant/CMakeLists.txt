cmake_minimum_required(VERSION 3.12)

project(VLSVariant VERSION 1.0.0)

include(VLSConan.cmake)

add_library(${PROJECT_NAME})

file(GLOB_RECURSE PUBLIC_HEADERS include/*.h)
target_sources(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS})

file(GLOB SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

file(GLOB SOURCE_HEADERS src/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include/ PRIVATE src/)

target_link_libraries(${PROJECT_NAME} PUBLIC VLSCore)

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
option(VLS_TEST_VARIANT "Unit test of the Variant module" OFF)
if(NOT DEFINED VLS_TEST_ALL) 
    option(VLS_TEST_ALL "Unit test of all VLS modules" OFF)
endif(NOT DEFINED VLS_TEST_ALL)

# Add tests directory.
if(VLS_TEST_ALL OR VLS_TEST_VARIANT)
    add_subdirectory(test)
endif()
