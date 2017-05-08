cmake_minimum_required(VERSION 2.8.3)
project(cpp)

add_definitions(-std=c++11)

find_package(Boost REQUIRED system filesystem thread chrono)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(boost_threading boost_threading.cpp)
target_link_libraries(boost_threading ${Boost_LIBRARIES})