cmake_minimum_required(VERSION 3.9)

project(RecipeBackend LANGUAGES CXX)

find_package(cpprestsdk REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RecipeBackend main.cpp recipeapi.cpp)
target_link_libraries(RecipeBackend PRIVATE cpprestsdk::cpprest)
