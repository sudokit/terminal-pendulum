cmake_minimum_required(VERSION 3.22.1)

project(termpend LANGUAGES C)

add_executable(${PROJECT_NAME}
  src/main.c
)

add_subdirectory(thirdparty/linmath.h/)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE -lm -lncurses linmath.h)
