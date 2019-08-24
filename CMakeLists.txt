cmake_minimum_required(VERSION 3.14)
project(Offline_4_ICG_MINE)

set(CMAKE_CXX_STANDARD 14)




include_directories(.)

add_executable(Offline_4_ICG_MINE
        1605115_symboltable.h
        func.cpp
        ICGFunctions.h
        input.c
        lex.yy.c
        utilityfunctions.h
        y.tab.c
        y.tab.h)


SET_SOURCE_FILES_PROPERTIES(${1605115_symboltable.h} PROPERTIES LANGUAGE CXX)
