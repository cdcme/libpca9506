target_sources(pca9506
    PUBLIC
        libpca9506.h
    PRIVATE
        registers.h
)

target_include_directories(pca9506 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
