cmake_minimum_required(VERSION 3.12)

function( add_VLS_library_test name )

  option( TEST_VLS_${name} "VLS ${name} module unit tests" ON)
  if( NOT TEST_VLS_ALL AND NOT TEST_VLS_${name} )
    return()
  endif()

  set( test_name VLSTest${name})

  find_package(GTest)

  if ( NOT ${GTest_FOUND})
    message( "WARNING GTest not found. ${test_name} target not created." )
    return()
  endif()

  file( GLOB TEST_SOURCES "test/*.*")

  add_executable( ${test_name} ${TEST_SOURCES})

  set_target_properties( ${test_name} PROPERTIES LINKER_LANGUAGE CXX )

  target_link_libraries( ${test_name}
    PRIVATE VLS::${name}
    PRIVATE gtest::gtest
  )

  install(
    TARGETS ${test_name}
    RUNTIME
  )

  include( GoogleTest )

  gtest_add_tests( TARGET ${test_name} )

  message( "-- VLS: Executable target declared 'VLSTest${name}'" )

endfunction()
