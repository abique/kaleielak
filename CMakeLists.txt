cmake_minimum_required(VERSION 3.2)

project(KALEIELAK C CXX)

add_definitions(-std=c++11)

# cinder? openframework?
find_package(PkgConfig)

pkg_check_modules(FFTW3 REQUIRED fftw3)
pkg_check_modules(VPX REQUIRED vpx)
pkg_check_modules(CAIRO REQUIRED cairo)

include_directories(mimosa)
include_directories(${CAIRO_CFLAGS})

add_subdirectory(mimosa EXCLUDE_FROM_ALL)
add_subdirectory(src)
