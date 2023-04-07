cmake_minimum_required(VERSION 3.12)

project(VLS VERSION 1.0.0)

# Add options to enable tests and examples
option(TEST_VLS_ALL "All VLS modules unit tests" OFF)
option(EXAMPLES_VLS_ALL "All VLS modules examples" OFF)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  if(${BUILD_SHARED_LIBS})
      string(REPLACE "/MT" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
  else()
      string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endif()
endforeach()


add_subdirectory(Log)
add_subdirectory(Converter)
add_subdirectory(Event)
add_subdirectory(Properties)
