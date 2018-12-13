target_sources(test_runner
    PRIVATE
        suites.h
        tests.h
        tests.c
        test_register_ops.c
        test_driver_init.c
)

target_include_directories(test_runner PUBLIC ${CMAKE_CURRENT_LIST_DIR})
