cmake_minimum_required(VERSION 2.8)
project(cnets_osblinnikov C CXX)

message(STATUS "Enter subdirectory types")
add_subdirectory(types)

message(STATUS "Enter subdirectory queue")
add_subdirectory(queue)

message(STATUS "Enter subdirectory readerWriter")
add_subdirectory(readerWriter)

message(STATUS "Enter subdirectory runnablesContainer")
add_subdirectory(runnablesContainer)

message(STATUS "Enter subdirectory mapBuffer")
add_subdirectory(mapBuffer)

message(STATUS "Enter subdirectory selector")
add_subdirectory(selector)

message(STATUS "Enter subdirectory dispatchKernel")
add_subdirectory(dispatchKernel)

message(STATUS "Enter subdirectory enet")
add_subdirectory(enet)
