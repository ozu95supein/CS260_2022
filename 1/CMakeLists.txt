cmake_minimum_required(VERSION 3.8)

set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(CS260A1)

############################
# Compiler options (for all targets)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
	add_compile_options(/W3)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

# For VSCODE (improves intellisense)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

add_subdirectory(src)