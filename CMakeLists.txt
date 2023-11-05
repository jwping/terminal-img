cmake_minimum_required (VERSION 3.8)

project ("terminal-img")

aux_source_directory(. TERMINALIMG_SOURCE)

add_executable (terminal-img ${TERMINALIMG_SOURCE})
# add_library (terminal-img ${TERMINALIMG_SOURCE})

# message(terminal-img "最终的gcc命令： ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_INCLUDE_DIRS} ${CMAKE_CXX_SOURCE_FILES}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET terminal-img PROPERTY CXX_STANDARD 23)
endif()