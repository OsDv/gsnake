cmake_minimum_required(VERSION 3.10)
project(gsnake C)
set(CMAKE_C_STANDARD 99)
link_directories(${CMAKE_SOURCE_DIR}/lib/raylib)
add_executable(gsnake 
	src/main.c
	src/screen_gameplay.c
)
target_link_libraries(gsnake PRIVATE ${CMAKE_SOURCE_DIR}/lib/raylib/windows_libraylib.a -lopengl32 -lgdi32 -lwinmm)
target_include_directories( gsnake PRIVATE
	src/include
)
