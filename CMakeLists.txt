cmake_minimum_required(VERSION 3.10)
project(gsnake C)
set(CMAKE_C_STANDARD 99)
add_executable(gsnake 
	src/main.c
	src/screen_gameplay.c
	src/screen_mainmenu.c
)
target_include_directories( gsnake PRIVATE
	src/include
)
link_directories(${CMAKE_SOURCE_DIR}/lib/raylib)

if (EMSCRIPTEN)
set(CMAKE_EXECUTABLE_SUFFIX ".html")
string(APPEND LINK_FLAGS "-Os -Wall ")
string(APPEND LINK_FLAGS "${CMAKE_SOURCE_DIR}/lib/raylib/web_libraylib.a ")
string(APPEND LINK_FLAGS "-I ${CMAKE_SOURCE_DIR}/externals ")
string(APPEND LINK_FLAGS "-s USE_GLFW=3 ")
string(APPEND LINK_FLAGS "-sASYNCIFY ")
string(APPEND LINK_FLAGS "-DPLATFORM_WEB ")
string(APPEND LINK_FLAGS "--shell-file ${CMAKE_SOURCE_DIR}/template.html ")
string(APPEND LINK_FLAGS "--embed-file ${CMAKE_SOURCE_DIR}/res@/res/ ")
set_target_properties(gsnake PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
target_compile_definitions(gsnake PRIVATE PLATFORM_WEB)

else()

target_link_libraries(gsnake PRIVATE ${CMAKE_SOURCE_DIR}/lib/raylib/windows_libraylib.a -lopengl32 -lgdi32 -lwinmm)

endif()

