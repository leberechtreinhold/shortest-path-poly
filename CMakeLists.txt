cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    shortest-path-poly
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    shortest-path-poly_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    shortest-path-poly_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(shortest-path-poly_lib PUBLIC cxx_std_17)

find_package(fmt REQUIRED)
target_link_libraries(shortest-path-poly_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(shortest-path-poly_exe source/main.cpp)
add_executable(shortest-path-poly::exe ALIAS shortest-path-poly_exe)

set_property(TARGET shortest-path-poly_exe PROPERTY OUTPUT_NAME shortest-path-poly)

target_compile_features(shortest-path-poly_exe PRIVATE cxx_std_17)

target_link_libraries(shortest-path-poly_exe PRIVATE shortest-path-poly_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT shortest-path-poly_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of shortest-path-poly"
  )
endif()

include(cmake/dev-mode.cmake)
