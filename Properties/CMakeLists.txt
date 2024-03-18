cmake_minimum_required(VERSION 3.12)

include(add-vls-library)
include(add-vls-library-test)

add_VLS_library( Properties )

target_link_libraries( VLSProperties
  PRIVATE VLS::Log
  PUBLIC VLS::Converter
  PUBLIC VLS::Event
)

add_VLS_library_test( Properties )
