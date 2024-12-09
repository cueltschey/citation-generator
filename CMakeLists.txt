cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
project(gen-citation)

add_subdirectory(external/CLI11)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include_directories(hdr)
file(GLOB SOURCE src/*.cpp)

add_executable(gen-citation ${SOURCE})

target_link_libraries(gen-citation PRIVATE CLI11::CLI11 ${CURL_LIBRARIES})

install(TARGETS gen-citation
        RUNTIME DESTINATION bin)

