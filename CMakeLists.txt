cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SoundEffects)

add_library(SoundEffects SHARED src/main.cpp)

include(cmake/CPM.cmake)

CPMAddPackage("gh:matcool/mat-dash#cdc9f70")
CPMAddPackage("gh:iAndyHD3/cocos-headers#9af919e")
CPMAddPackage("gh:HJfod/gd.h#90f2110")
CPMAddPackage("gh:TsudaKageyu/minhook#4a45552")
CPMAddPackage("gh:fmtlib/fmt#a337011")

target_compile_definitions(SoundEffects PRIVATE CC_DLL=)

target_include_directories(SoundEffects PRIVATE
    ${gd.h_SOURCE_DIR}/include ${gd.h_SOURCE_DIR}
    ${minhook_SOURCE_DIR}/include
	${fmt_SOURCE_DIR}/include
)

target_link_libraries(SoundEffects mat-dash cocos2d minhook fmt)
