cmake_minimum_required(VERSION 3.21)
project(Progtest C)

set(CMAKE_C_STANDARD 11)

add_executable(Progtest
        cv03.c
        cv05.c
        DU1.c
        DU2.c
        DU3.c
        DU3_copy.c
        DU4.c
        DU4_unformatted.c
        DU5.c
        DU5_reserve.c
        test.c
        ZahrivaciUloha.c)
