cmake_minimum_required(VERSION 3.12)
project(TimeProposalAssignment)

set(CMAKE_CXX_STANDARD 11)

add_executable(TimeProposalAssignment main.cpp Param.h Customer.h Customer.cpp Chromosome.h Chromosome.cpp TimeWindow.cpp TimeWindow.h)
