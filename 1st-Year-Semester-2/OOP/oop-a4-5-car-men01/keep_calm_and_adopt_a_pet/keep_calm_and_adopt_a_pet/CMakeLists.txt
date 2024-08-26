cmake_minimum_required(VERSION 3.27)
project(keep_calm_and_adopt_a_pet)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(keep_calm_and_adopt_a_pet
        dog.cpp
        dog.h
        dynamic_array.cpp
        dynamic_array.h
        main.cpp
        repository.cpp
        repository.h
        service.cpp
        service.h
        tests.cpp
        tests.h
        UI.cpp
        UI.h)
