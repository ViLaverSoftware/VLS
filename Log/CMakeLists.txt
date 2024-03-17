cmake_minimum_required(VERSION 3.12)

include(add-vls-library)
include(add-vls-library-mock)
include(add-vls-library-test)

add_VLS_library( Log )

add_VLS_library_mock( Log )

add_VLS_library_test( Log )

target_link_libraries( VLSTestLog
  PUBLIC VLS::Mock::Log
)
