cmake_minimum_required(VERSION 3.8)
project(Ex5_Chrispens_Gahbiche)

#set(CXX_CXX_COMPILER /usr/local/bin/g++-7)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp producers_consumers.h MulticastMutextTransport.h)
add_executable(Ex5_Chrispens_Gahbiche ${SOURCE_FILES})