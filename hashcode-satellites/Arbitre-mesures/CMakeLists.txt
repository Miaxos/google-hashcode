cmake_minimum_required(VERSION 2.8)
# Nom du projet
project(hashcode_2016)

if (UNIX)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -g -Wall")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("./")

file(GLOB SRC_FOLDER
    "./*.cpp"
	"./main.cpp"

)
add_executable(hashcode ${SRC_FOLDER})