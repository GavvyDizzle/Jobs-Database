cmake_minimum_required(VERSION 3.23)
project(CS203_Project1 C)

set(CMAKE_C_STANDARD 99)

add_executable(CS203_Project1 main.c BTNodeQueue.c BTNodeQueue.h LinkedList.c LinkedList.h Job.c Job.h JobManager.c JobManager.h StringArrayList.c StringArrayList.h JobArrayList.c JobArrayList.h bt.c bt.h)
