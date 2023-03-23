cmake_minimum_required(VERSION 3.22.1)
project(linmath.h LANGUAGES C)

add_library(linmath.h ./include/linmath.h)
set_target_properties(linmath.h PROPERTIES LINKER_LANGUAGE C)
target_include_directories(linmath.h PUBLIC include/)