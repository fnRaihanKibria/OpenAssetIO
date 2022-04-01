find_package(Catch2 2 REQUIRED)

include(Catch)

# C API bindings tests.
add_subdirectory(openassetio-core-c)
