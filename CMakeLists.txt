cmake_minimum_required(VERSION 3.31)
project(green_eng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE VENDOR_SOURCES "vendor/*.cpp" "vendor/*.c")
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${VENDOR_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src/
    vendor/glad/include
    vendor/glfw/include
    vendor/stb
    vendor/imgui/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/libglfw3.a
    opengl32
    gdi32
    user32
)
