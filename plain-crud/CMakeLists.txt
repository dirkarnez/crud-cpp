cmake_minimum_required(VERSION 3.0)
project(plain-crud)

add_library(${PROJECT_NAME} STATIC
    "include/plain-crud.h"
    "src/plain-crud.cpp")

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "include")