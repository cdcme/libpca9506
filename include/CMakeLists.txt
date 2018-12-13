target_sources(pca9606
    PUBLIC
        libpca9606.h
    PRIVATE
        registers.h
)

target_include_directories(pca9606 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
