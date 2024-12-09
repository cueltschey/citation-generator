cmake_minimum_required(VERSION 3.20)
project(MyProject)

add_subdirectory(external/CLI11)

include_directories(hdr)
file(GLOB SOURCE src/*.cpp)

add_executable(gen-citation ${SOURCE})

target_link_libraries(gen-citation PRIVATE CLI11::CLI11)
