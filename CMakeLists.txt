cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0091 NEW)

project(VLS VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# This is needed when building shared libraries with MSVC compiler or it will not create any .lib files to link with
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Add options to enable tests and examples
option(TEST_VLS_ALL "All VLS modules unit tests" ON)
option(EXAMPLES_VLS_ALL "All VLS modules examples" OFF)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CompilerFlags
  CMAKE_CXX_FLAGS
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_C_FLAGS
  CMAKE_C_FLAGS_DEBUG
  CMAKE_C_FLAGS_RELEASE
)

if(${BUILD_SHARED_LIBS})
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Add the cmake function source files to the project
file( GLOB CMAKE_SOURCES "CMake/*.cmake")
add_custom_target( CMake SOURCES ${CMAKE_SOURCES} )

add_subdirectory(Log)
add_subdirectory(Converter)
add_subdirectory(Event)
#add_subdirectory(Properties)
