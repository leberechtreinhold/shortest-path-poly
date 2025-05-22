# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(shortest-path-polyTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(shortest-path-poly_test source/shortest-path-poly_test.cpp)
target_link_libraries(
    shortest-path-poly_test PRIVATE
    shortest-path-poly_lib
    Catch2::Catch2WithMain
)
target_compile_features(shortest-path-poly_test PRIVATE cxx_std_17)

catch_discover_tests(shortest-path-poly_test)

# ---- End-of-file commands ----

add_folders(Test)
