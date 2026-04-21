cmake_minimum_required(VERSION 3.14)
project(sample_minifb)

include(FetchContent)

FetchContent_Declare(
    minifb
    GIT_REPOSITORY https://github.com/emoon/minifb.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(minifb)

add_executable(sample_minifb main.c)

target_link_libraries(sample_minifb minifb)

if(WIN32)
    target_link_libraries(sample_minifb gdi32 opengl32 winmm)
elseif(APPLE)
    target_link_libraries(sample_minifb
        "-framework Cocoa"
        "-framework Metal"
        "-framework MetalKit"
        "-framework QuartzCore"
    )
endif()
