# greatest: a single-file, header-only unit-testing lib
set(GREATEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vendor/greatest)
add_library(greatest INTERFACE)
target_include_directories(greatest INTERFACE
    $<BUILD_INTERFACE:${GREATEST_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:greatest>)

# project test runner setup
add_executable(test_runner)
add_subdirectory(suites)

target_sources(test_runner
       PRIVATE
            runner.c
        PUBLIC
            runner.h
)

# theft: property-based testing lib
find_library(THEFT_LIB theft)
find_library(MATH_LIBRARY m)

target_link_libraries(test_runner PUBLIC greatest ${MATH_LIBRARY} ${THEFT_LIB} libpca9506)
set_target_properties(test_runner PROPERTIES FOLDER test)

add_test(test_runner test_runner)
