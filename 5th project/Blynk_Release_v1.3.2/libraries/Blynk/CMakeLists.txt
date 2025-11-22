cmake_minimum_required(VERSION 3.3)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "src"
                       REQUIRES arduino)
