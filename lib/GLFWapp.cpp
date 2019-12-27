//
// Created by jafffy on 12/25/19.
//
#include "GLFWapp.h"

#include <cstdio>
#include <cstdlib>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

using namespace std;

GLFWapp::GLFWapp(int width, int height, const char *title) {
    GLFWwindow *window = nullptr;

    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height,
                              title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(-1);
    }

    glClearColor(0, 0, 0.3f, 0);

    on_create();

    auto last_time = chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        auto current_time = chrono::steady_clock::now();
        double elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - last_time).count();

        last_time = current_time;

        on_update(elapsed_time);

        on_render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    on_destroy();

    glfwTerminate();
}
