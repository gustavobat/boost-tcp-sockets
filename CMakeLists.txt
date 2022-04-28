project(boost-tcp-sockets)
cmake_minimum_required(VERSION 3.1)

find_package(Boost REQUIRED system)

add_subdirectory(src)