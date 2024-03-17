cmake_minimum_required(VERSION 3.12)

include(add-vls-library)
include(add-vls-library-test)
include(add-vls-library-examples)

add_VLS_library( Event )

add_VLS_library_test( Event )

add_VLS_library_examples( Event )
