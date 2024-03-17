cmake_minimum_required(VERSION 3.12)

function( add_VLS_library name )

  set( target_name VLS${name} )

  add_library(${target_name})

  set_target_properties( ${target_name} PROPERTIES LINKER_LANGUAGE CXX )

  file(GLOB_RECURSE PUBLIC_HEADERS include/*.h)
  target_sources(${target_name} PUBLIC ${PUBLIC_HEADERS})

  file(GLOB_RECURSE SOURCES src/*.cpp)
  target_sources(${target_name} PRIVATE ${SOURCES})

  file(GLOB_RECURSE SOURCE_HEADERS src/*.h)
  target_sources(${target_name} PRIVATE ${SOURCE_HEADERS})

  target_include_directories(${target_name}
    PUBLIC include
    PRIVATE src
  )

  target_compile_features(${target_name} PUBLIC cxx_std_20)

  install(
    TARGETS ${target_name}
    LIBRARY
    ARCHIVE
    RUNTIME
  )

  install(
    DIRECTORY include/
    DESTINATION include/
    FILES_MATCHING PATTERN "*.h"
  )

  add_library( VLS::${name} ALIAS ${target_name})
  message( "-- VLS: Library target declared 'VLS::${name}'" )
endfunction()
