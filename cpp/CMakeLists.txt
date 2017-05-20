cmake_minimum_required(VERSION 2.8.3)
project(cpp)

add_definitions(-std=c++11)

set(CUSTOM_TARGETS boost_threading single_producer_consumer multiple_producer_consumer 
)

find_package(Boost REQUIRED system filesystem thread chrono)
include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(boost_threading src/boost_threading.cpp)
target_link_libraries(boost_threading ${Boost_LIBRARIES})

add_executable(single_producer_consumer src/single_producer_consumer.cpp)
target_link_libraries(single_producer_consumer ${Boost_LIBRARIES})

add_executable(multiple_producer_consumer src/producer_consumer.cpp)
target_link_libraries(multiple_producer_consumer ${Boost_LIBRARIES})

install(
  TARGETS ${CUSTOM_TARGETS}
  DESTINATION ${PROJECT_SOURCE_DIR}/bin
)