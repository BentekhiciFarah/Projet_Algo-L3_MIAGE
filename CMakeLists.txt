cmake_minimum_required(VERSION 3.10)
project(Projet_Algo_L3_MIAGE C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(Projet_Algo_L3_MIAGE
        fichier.c
        SaintAubinBentekhci2bis.c
        SaintAubinBentekhci3.c)
