cmake_minimum_required(VERSION 2.8.3)
project(cpp)

add_definitions(-std=c++11)

find_package(Boost REQUIRED system filesystem thread chrono)
include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(boost_threading boost_threading.cpp)
target_link_libraries(boost_threading ${Boost_LIBRARIES})

add_executable(single_prodcons single_producer_consumer.cpp)
target_link_libraries(single_prodcons ${Boost_LIBRARIES})

add_executable(producer_consumer producer_consumer.cpp)
target_link_libraries(producer_consumer ${Boost_LIBRARIES})
