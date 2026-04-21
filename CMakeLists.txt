cmake_minimum_required(VERSION 3.10)
project(sample_minifb)

include_directories(C:/Users/boran/minifb/include)

add_executable(sample_minifb main.c)

target_link_libraries(sample_minifb
    C:/Users/boran/minifb/build/libminifb.a
    gdi32
    opengl32
    winmm
    stdc++
)