cmake_minimum_required(VERSION 3.22)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgoAnalysis
        AlgoAnalysis-C/InsertionSort/insertionSort.c
)
add_executable(AlgoAnalysis2 AlgoAnalysis-C/MergeSort/mergeSort.c)
add_executable(AlgoAnalysis3 AlgoAnalysis-C/MaxSubArrayProblem/MaxSubArrayProblem.c)
