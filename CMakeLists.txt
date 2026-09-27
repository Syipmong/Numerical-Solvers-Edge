cmake_minimum_required(VERSION 3.16)
project(NumericalSolversEdge C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(solvers_static STATIC src/solvers.c)
target_include_directories(solvers_static PUBLIC include)

add_executable(bench_solvers bench/main.c)
target_link_libraries(bench_solvers PRIVATE solvers_static)

if(MSVC)
	target_compile_options(solvers_static PRIVATE /W4 /WX)
	target_compile_options(bench_solvers PRIVATE /W4 /WX)
else()
	target_compile_options(solvers_static PRIVATE -Wall -Wextra -Werror)
	target_compile_options(bench_solvers PRIVATE -Wall -Wextra -Werror)
	target_compile_options(solvers_static PRIVATE $<$<CONFIG:Release>:-O3>)
	target_compile_options(bench_solvers PRIVATE $<$<CONFIG:Release>:-O3>)
endif()