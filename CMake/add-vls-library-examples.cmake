cmake_minimum_required(VERSION 3.12)

function( add_VLS_library_examples name )

  option( EXAMPLES_VLS_${name} "VLS ${name} module examples" ON)
  if( NOT EXAMPLES_VLS_ALL AND NOT EXAMPLES_VLS_${name} )
    return()
  endif()

  set( examples_name VLSExamples${name})

  file(GLOB EXAMPLES_SOURCES "examples/*.*")

  add_executable(${examples_name} ${EXAMPLES_SOURCES})

  target_compile_features( ${examples_name} PUBLIC cxx_std_20 )
  set_target_properties( ${examples_name} PROPERTIES LINKER_LANGUAGE CXX )
  set_target_properties( ${examples_name} PROPERTIES COMPILE_WARNING_AS_ERROR ON)

  target_link_libraries(${examples_name} VLS::${name})

  message( "-- VLS: Executable target declared 'VLSExamples${name}'" )

endfunction()
