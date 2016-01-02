cmake_minimum_required(VERSION 3.2)

project(KALEIELAK C CXX)

add_definitions(-std=c++14 -fopenmp)

# cinder? openframework?
find_package(PkgConfig)
find_package(OpenMP)

pkg_check_modules(SNDFILE REQUIRED sndfile)
pkg_check_modules(FFTW3 REQUIRED fftw3)
pkg_check_modules(CAIRO REQUIRED cairo)

include_directories(mimosa)
include_directories(${CAIRO_CFLAGS})

add_subdirectory(mimosa EXCLUDE_FROM_ALL)
add_subdirectory(src)
