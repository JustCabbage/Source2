cmake_minimum_required(VERSION 3.6.0)
project(Source2 VERSION 0.1.0 LANGUAGES CXX)

# Serves the purpose, do not recommend
file(GLOB_RECURSE SourceCompile CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)

add_library(Source2 SHARED ${SourceCompile})

