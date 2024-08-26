cmake_minimum_required(VERSION 3.27)
project(a2_3_car_men01 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(a2_3_car_men01
        controller.c
        controller.h
        domain.c
        domain.h
        repository.c
        repository.h
        UI.c
        UI.h
        main.c
        dynamic_array.h
        dynamic_array.c
        undo.c
        undo.h
        tests.c
        tests.h
)
