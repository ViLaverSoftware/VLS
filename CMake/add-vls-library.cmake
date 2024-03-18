cmake_minimum_required(VERSION 3.12)

function( add_VLS_library name )

  set( target_name VLS${name} )

  file(GLOB_RECURSE PUBLIC_HEADERS include/*.h)
  file(GLOB_RECURSE SOURCES src/*.cpp)
  file(GLOB_RECURSE SOURCE_HEADERS src/*.h)

  if ( NOT SOURCES )
    add_library(${target_name} INTERFACE ${PUBLIC_HEADERS})

    # Only header files so creating a interface target
    target_include_directories( ${target_name}
      INTERFACE include
    )
  else()
    add_library(${target_name} )
    target_sources(${target_name} PUBLIC ${PUBLIC_HEADERS})
    target_sources(${target_name} PRIVATE ${SOURCES})
    target_sources(${target_name} PRIVATE ${SOURCE_HEADERS})

    target_include_directories(${target_name}
      PUBLIC include
      PRIVATE src
    )

    target_compile_features(${target_name} PUBLIC cxx_std_20)
    set_target_properties( ${target_name} PROPERTIES LINKER_LANGUAGE CXX )

    install(
      TARGETS ${target_name}
      LIBRARY
      ARCHIVE
      RUNTIME
    )
  endif()

  install(
    DIRECTORY include/
    DESTINATION include/
    FILES_MATCHING PATTERN "*.h"
  )

  add_library( VLS::${name} ALIAS ${target_name})
  message( "-- VLS: Library target declared 'VLS::${name}'" )
endfunction()
