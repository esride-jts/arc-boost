# CMakeList.txt : CMake project for arcboost, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (arcboost "arcboost.cpp" "arcboost.h")
find_package(pybind11 REQUIRED)
pybind11_add_module(arcboost arcboost.cpp pygeometry.cpp)

# TODO: Add tests and install targets if needed.
