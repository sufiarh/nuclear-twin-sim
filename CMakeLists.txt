cmake_minimum_required(VERSION 3.10)
project(NuclearTwinSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(nuclear_sim ${SOURCES})

# Mengaktifkan optimasi O3 untuk performa tinggi komputasi nuklir
target_compile_options(nuclear_sim PRIVATE -O3 -Wall -Wextra)
