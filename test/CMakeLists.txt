cmake_minimum_required(VERSION 3.20)
project(Test LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options("/utf-8")
	add_compile_options("/MP")
	add_compile_options("/sdl-")
	add_compile_options("/diagnostics:caret")
	# add_compile_options("/Zc:preprocessor")
	add_compile_options("/fsanitize=address") # asan for msvc, needs to compile gtest with asan too
	add_compile_options("/permissive-")
else()
	# add_compile_options("-std=c++2b")
	add_compile_options("-fno-omit-frame-pointer")
	# add_compile_options("-Wno-deprecated")
	add_compile_options("-Wno-deprecated-declarations")
	# add_compile_options("-std=c++latest")
	# add_compile_options("-fsanitize=address") # oops, mingw doesn't support asan
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(GTest_DIR "D:/Projects/vcpkg-asan/vcpkg_installed/test-triplet-asan/share/gtest")
	# compiled by vcpkg, but with custom triplet with asan
else()
	set(GTest_DIR "D:/Projects/vcpkg-mingw-asan/mingw64/lib/cmake/GTest")
	# gtest for mingw is unavailable to compile with vcpkg
	# pls download from msys2 : "https://packages.msys2.org/packages/mingw-w64-x86_64-gtest"
endif()

# fmtlib
set(fmt_DIR "D:/Projects/3rdlibs/fmt/lib/cmake/fmt")

find_package(GTest REQUIRED)
find_package(fmt REQUIRED)


file(GLOB_RECURSE PROJ_SOURCE_FILES "*.c" "*.cpp")

add_executable(${PROJECT_NAME}
    ${PROJ_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		cutil
		fmt::fmt-header-only
		GTest::gtest
		GTest::gtest_main
)
