cmake_minimum_required (VERSION 3.0)
project (escena)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

set(FRAMEWORK_SRCS
	"lib/scene_node.cc"
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

include_directories(
	"/usr/local/include"
	"./include"
)

link_directories(
	"/usr/local/lib"
)

add_compile_options(
	"-std=c++14"
	"-O2"
)
add_executable(sample01
	samples/sample01.cc
	${FRAMEWORK_SRCS}
)
target_link_libraries(sample01
	${ALL_LIBS}
)
