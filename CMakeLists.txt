cmake_minimum_required(VERSION 3.13)

project(libpca9506 VERSION 0.2.1
        DESCRIPTION "Driver for the NXP Semiconductors PCA9505/06 40-bit I2C-bus I/O port with RESET, OE and INT"
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_library(pca9506 STATIC "")
add_library(libpca9506 ALIAS pca9506)
add_subdirectory(include)
add_subdirectory(src)

find_library(MATH m)
target_link_libraries(pca9506 ${MATH})

target_compile_options(pca9506 PUBLIC -W -Wall -Wextra -pedantic)
target_compile_features(pca9506 PUBLIC c_std_11)

if(TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS pca9506 DESTINATION lib)
install(FILES include/pca9506.h DESTINATION include)
