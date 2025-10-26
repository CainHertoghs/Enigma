cmake_minimum_required(VERSION 3.30.5)
project(enigma)

set(CMAKE_CXX_STANDARD 20)

add_executable(enigma main.cpp
        encryption/Enigma.cpp
        encryption/Enigma.h
        decryption/TuringBombe.cpp
        decryption/TuringBombe.h
)
