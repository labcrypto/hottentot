cmake_minimum_required(VERSION 3.2)
project(java-generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(java-generator ${SOURCE_FILES}  ds/hot.cpp ds/hot.h ds/struct.cpp ds/struct.h  ds/member.cpp ds/member.h ds/module.cpp ds/module.h ds/service.cpp ds/service.h ds/argument.cpp ds/argument.h ds/method.cpp ds/method.h)