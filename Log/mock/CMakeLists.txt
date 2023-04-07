cmake_minimum_required( VERSION 3.10 )

find_package( GTest REQUIRED )

file( GLOB SOURCES "*.h" )

add_library( Mock${PROJECT_NAME} INTERFACE ${SOURCES} )

target_include_directories(Mock${PROJECT_NAME}
  INTERFACE .
)

target_link_libraries( Mock${PROJECT_NAME}
  INTERFACE ${PROJECT_NAME}
  INTERFACE gtest::gtest
)
