cmake_minimum_required(VERSION 3.8)
project(dhtml)

# Engine library
add_executable(${PROJECT_NAME}
			main.cpp
			networking.hpp networking.cpp
			utils.hpp
			dhtml.hpp dhtml.cpp
			)
target_include_directories(${PROJECT_NAME} PUBLIC .)

# Optional, pretty formatting
# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# Libraries
if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32.lib)
endif ()