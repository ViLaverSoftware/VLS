cmake_minimum_required(VERSION 3.10)

find_package(GTest)

if (${GTest_FOUND})
    file(GLOB SOURCES "src/*.cpp")

    add_executable(UnitTest${PROJECT_NAME} ${SOURCES})

    target_link_libraries(UnitTest${PROJECT_NAME}
        ${PROJECT_NAME}
        gtest::gtest)

    include(GoogleTest)

    gtest_add_tests(TARGET UnitTest${PROJECT_NAME})
else()
    message( "WARNING GTest not found. UnitTest${PROJECT_NAME} target not created." )
endif()
