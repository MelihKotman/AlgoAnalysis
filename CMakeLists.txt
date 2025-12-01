cmake_minimum_required(VERSION 3.22)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgoAnalysis
        AlgoAnalysis-C/InsertionSort/insertionSort.c
)
add_executable(AlgoAnalysis2 AlgoAnalysis-C/MergeSort/mergeSort.c)
add_executable(AlgoAnalysis3 AlgoAnalysis-C/MaxSubArrayProblem/MaxSubArrayProblem.c)
add_executable(AlgoAnalysis4 AlgoAnalysis-C/QuickSort/QuickSort.c)
add_executable(AlgoAnalysis5 AlgoAnalysis-C/HeapSort/heapSort.c)
add_executable(AlgoAnalysis6 AlgoAnalysis-C/CountingSort/CountingSort.c)
add_executable(AlgoAnalysis7 AlgoAnalysis-C/DynamicProgramming/CuttingRodProblem.c)
add_executable(AlgoAnalysis8 AlgoAnalysis-C/DynamicProgramming/LongestCommonSubsequenceProblem.c)
