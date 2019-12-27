cmake_minimum_required (VERSION 3.0)
project (escena)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

set(FRAMEWORK_SRCS
		"lib/scene_node.cc"
		include/renderer.h lib/GLFWapp.cpp include/GLFWapp.h include/utils/shader.h lib/utils/shader.cpp)

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

add_executable(sample02
		${FRAMEWORK_SRCS} samples/sample02.cc)
target_link_libraries(sample02
		${ALL_LIBS})
