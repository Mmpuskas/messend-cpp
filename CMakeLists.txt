cmake_minimum_required(VERSION 3.5)

message(STATUS "Building Messend")

# Add our static library target
add_library(Messend STATIC
    messend/private/messend.c
    messend/public/messend.h
	public/messend.hpp
)

target_include_directories(Messend
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/messend/private
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/messend/public
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

# Compile with C++17
target_compile_features(Messend PRIVATE cxx_std_17)
set_target_properties(Messend PROPERTIES CXX_EXTENSIONS OFF)