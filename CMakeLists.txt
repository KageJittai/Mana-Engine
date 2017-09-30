project(Mana-Engine)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Added so QtCreator "sees" everything:
FILE(GLOB_RECURSE ManaEngineHeaders "include/Mana/*.hpp")
add_custom_target(headers SOURCES ${ManaEngineHeaders})

aux_source_directory(src SRC_LIST)

include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

add_subdirectory(tests)
