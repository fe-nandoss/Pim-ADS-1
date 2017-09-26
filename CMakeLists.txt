cmake_minimum_required(VERSION 3.8)
project(projeto_ads)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c CarrosDisponiveis.h Carro.h)
add_executable(projeto_ads ${SOURCE_FILES})