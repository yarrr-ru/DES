cmake_minimum_required(VERSION 2.8)

set(PROJECT feistel)

project(${PROJECT})

SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O2")

set(BOOST_COMPONENTS 
  program_options
)

set(Boost_USE_STATIC_LIBS ON)

set(SOURCES
  src/feistel.cpp
  src/key.cpp
  src/generator.cpp
  src/main.cpp
)

find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
  include
)

add_executable(${PROJECT} ${SOURCES})

target_link_libraries (${PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

