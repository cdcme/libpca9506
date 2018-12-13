cmake_minimum_required(VERSION 3.13)

project(libpca9606 VERSION 1.0.0
        DESCRIPTION "Driver for the NXP Semiconductors PCA9605/06 40-bit I2C-bus I/O port with RESET, OE and INT"
        LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_library(pca9606 STATIC "")
add_library(libpca9606 ALIAS pca9606)
add_subdirectory(include)
add_subdirectory(src)

find_library(MATH m)
target_link_libraries(pca9606 ${MATH})

target_compile_options(pca9606 PUBLIC -W -Wall -Werror)
target_compile_features(pca9606 PUBLIC c_std_11)

if(TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
