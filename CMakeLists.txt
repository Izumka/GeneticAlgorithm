cmake_minimum_required(VERSION 3.9)
project(chromosome)
find_package (Threads)

set(CMAKE_CXX_STANDARD 14)



add_executable(chromosome main.cpp  Chromosome/Chromosome.cpp Chromosome/Chromosome.h
        Chromosome/Chromosome_binary.cpp Chromosome/Chromosome_binary.h Chromosome/functions.cpp Chromosome/functions.h
        Population/Populaton.cpp Population/Populaton.h)
target_link_libraries(chromosome ${CMAKE_THREAD_LIBS_INIT})