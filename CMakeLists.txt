cmake_minimum_required(VERSION 3.9)
project(chromosome)
find_package (Threads)

set(CMAKE_CXX_STANDARD 14)



add_executable(chromosome main.cpp chromosome.h population.cpp population.h)
target_link_libraries(chromosome ${CMAKE_THREAD_LIBS_INIT})