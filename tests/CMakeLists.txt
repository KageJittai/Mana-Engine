cmake_minimum_required(VERSION 3.0)

project(Mana_Engine_Tests)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Link to Mana-Engine
find_library(MANA_ENGINE_LIB Mana-Engine ${CMAKE_BINARY_DIR})

# Make test executable
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch "${MANA_ENGINE_LIB}")
