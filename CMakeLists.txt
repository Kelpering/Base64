cmake_minimum_required(VERSION 3.25.1)
project(Base64)

include_directories(include)

file (GLOB SOURCES "src/*.c")

add_executable(Base64 ${SOURCES})

target_compile_options(Base64 PRIVATE
  -Wall -Wextra -Wpedantic
)