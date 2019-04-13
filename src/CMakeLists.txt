cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        AddMatrixWidget.cpp
        AddMatrixWidget.h
        Fraction.cpp
        Fraction.h
        LibraryWindow.cpp
        LibraryWindow.h
        main.cpp
        MainWindow.cpp
        MainWindow.h
        Matrix.cpp
        Matrix.h
        MatrixLibrary.cpp
        MatrixLibrary.h
        MatriXMiXTXT.cpp
        MatriXMiXTXT.h
        Polynomial.cpp
        Polynomial.h
        ShowMatrixWidget.cpp
        ShowMatrixWidget.h
        VectorX.cpp
        VectorX.h)
