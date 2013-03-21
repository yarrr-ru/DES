cmake_minimum_required(VERSION 2.8)

set(PROJECT feistel)

project(${PROJECT})

include_directories(
  include
)

set(SOURCES
  src/test.cpp
  src/main.cpp
)

add_executable(${PROJECT} ${SOURCES})