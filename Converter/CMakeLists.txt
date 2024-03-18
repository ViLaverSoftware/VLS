cmake_minimum_required(VERSION 3.12)

include(add-vls-library)
include(add-vls-library-test)

add_VLS_library( Converter )

target_link_libraries( VLSConverter
  PUBLIC VLS::Log
)

add_VLS_library_test( Converter )
