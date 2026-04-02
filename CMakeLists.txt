cmake_minimum_required(VERSION 4.0)
project(String_matching)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(String_matching
        aho.cpp
        AhoCorasick.cpp
        BoyerMoore.cpp
        BruteForce.cpp
        Function.h
        function.hpp
        gen-test.cpp
        KMP.cpp
        main.cpp
        naive.cpp
        RabinKarp.cpp)
