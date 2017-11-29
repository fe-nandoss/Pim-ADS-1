cmake_minimum_required(VERSION 3.8)
project(projeto_ads)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c ClienteMetodos.c CarroMetodos.c Header/Carro.h Header/Cliente.h Header/H_CarroMetodos.h Header/H_ClienteMetodos.h Utils/_globals.h Utils/data.h Utils/utils.h Arquivos Header/H_Interface.h Interface.c)
add_executable(pim ${SOURCE_FILES})