cmake_minimum_required(VERSION 3.8)
project(projeto_ads)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c ClienteMetodos.c CarroMetodos.c Header Utils Arquivos)
add_executable(pim ${SOURCE_FILES})