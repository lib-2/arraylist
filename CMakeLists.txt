cmake_minimum_required(VERSION 3.10)

project(G_2_arraylist VERSION 1.0 LANGUAGES C)

set(SOURCES
  src/arraylist.c
)

add_library(G_2_arraylist STATIC ${SOURCES})
set_target_properties(G_2_arraylist PROPERTIES
  OUTPUT_NAME "-2_arraylist"
)

target_include_directories(G_2_arraylist
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external_include
)

install(TARGETS G_2_arraylist
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  FILES
    include/-2_arraylist.h
  DESTINATION
    include
)

install(
  FILES
    include/-2/arraylist_functions.h
    include/-2/arraylist_shortcut.h
    include/-2/arraylist_types.h
  DESTINATION
    include/-2
)
