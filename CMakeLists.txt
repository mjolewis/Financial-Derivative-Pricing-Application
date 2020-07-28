cmake_minimum_required(VERSION 3.16)
project(Group_A_and_B)

set(CMAKE_CXX_STANDARD 14)

add_executable(Group_A_and_B Test.cpp Input.cpp Input.hpp RNG.cpp RNG.hpp Instrument.hpp)

set(BOOST_INCLUDE /usr/local/Cellar/boost/1.72.0)
set(BOOST_LIBRARY /usr/local/Cellar/boost/1.72.0)

find_package(Boost 1.72.0)
include_directories(${Boost_INCLUDE_DIR})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()