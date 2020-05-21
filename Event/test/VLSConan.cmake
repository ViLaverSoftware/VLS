
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                    ${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)

# Add external targets
conan_cmake_run(CONANFILE conanfileExternal.txt 
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()