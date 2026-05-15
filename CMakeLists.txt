cmake_minimum_required(VERSION 3.10)

project(orbital_sim)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    orbital_sim

    src/main.cpp

    src/physics/twobody.cpp
    src/physics/state.cpp

    src/integrators/rkf45.cpp

    src/utils/math_utils.cpp
)
