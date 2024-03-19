cmake_minimum_required(VERSION 3.12)

function( add_VLS_library_mock name )

  if( NOT TEST_VLS_ALL AND NOT TEST_${name} )
    return()
  endif()

  set( mock_name VLSMock${name})

  find_package(GTest)

  if ( NOT ${GTest_FOUND})
    message( "WARNING GTest not found. ${mock_name} target not created." )
    return()
  endif()

  file( GLOB MOCK_HEADERS "mock/*.h")
  file( GLOB MOCK_SOURCES "mock/*.cpp")

  if ( NOT MOCK_SOURCES )
    # Only header files so creating a interface target
    add_library( ${mock_name} INTERFACE ${MOCK_HEADERS} )

    target_include_directories( ${mock_name}
      INTERFACE mock
    )

    target_link_libraries( ${mock_name}
      INTERFACE VLS::${name}
      INTERFACE gtest::gtest
    )
  else()
    add_library( ${mock_name} )
    target_sources( ${mock_name} PUBLIC ${MOCK_HEADERS} )
    target_sources( ${mock_name} PRIVATE ${MOCK_SOURCES} )


    target_compile_features( ${mock_name} PUBLIC cxx_std_20 )
    set_target_properties( ${mock_name} PROPERTIES LINKER_LANGUAGE CXX )
    set_target_properties( ${mock_name} PROPERTIES COMPILE_WARNING_AS_ERROR ON)

    target_include_directories( ${mock_name}
      mock
    )

    target_link_libraries( ${mock_name}
      VLS::${name}
      gtest::gtest
    )
  endif()

  add_library( VLS::Mock::${name} ALIAS ${mock_name})
  message( "-- VLS: Library target declared 'VLS::Mock::${name}'" )

endfunction()
