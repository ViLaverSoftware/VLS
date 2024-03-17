cmake_minimum_required(VERSION 3.12)

project(VLSProperties VERSION 1.0.0)

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

file(GLOB_RECURSE PUBLIC_HEADERS include/*.h)
target_sources(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS})

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

file(GLOB_RECURSE SOURCE_HEADERS src/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE src )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC VLSConverter VLSEvent)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY
  ARCHIVE
  RUNTIME
)

install(
    DIRECTORY include/
    DESTINATION include/
    FILES_MATCHING PATTERN "*.h"
)

# Add tests directory.
option(TEST_${PROJECT_NAME} "${PROJECT_NAME} module unit tests" OFF)
if( ( TEST_VLS_ALL OR TEST_${PROJECT_NAME} ) AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/test" )
    add_subdirectory(test)
endif()

# Add example directory.
option(EXAMPLES_${PROJECT_NAME} "${PROJECT_NAME} module examples" OFF)
if( ( EXAMPLES_VLS_ALL OR EXAMPLES_${PROJECT_NAME} ) AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/examples" )
    add_subdirectory(examples)
endif()
