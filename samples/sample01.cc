#include <cstdio>
#include <cerrno>

#include <unistd.h>

#include <GL/glew.h>

#include "GLFWapp.h"

#include "utils/shader.h"

using namespace std;

static class {
public:
    const char *title = "Sample 01";
    int width = 800;
    int height = 600;

    GLuint program_id = 0;

    GLuint vao = 0;
    GLuint vbo = 0;
} app_context;

void on_create() {
    app_context.program_id = create_program("./simple.vert", "./simple.frag");

    glGenVertexArrays(1, &app_context.vao);
    glBindVertexArray(app_context.vao);

    static const float vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
    };

    glGenBuffers(1, &app_context.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, app_context.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    glDisableVertexAttribArray(0);

    glBindVertexArray(0);
}

void on_destroy() {
    glDeleteProgram(app_context.program_id);

    glDeleteBuffers(1, &app_context.vbo);
    glDeleteVertexArrays(1, &app_context.vao);
}

void on_update(double) {
}

void on_render() {
    GLuint color_buffer_bit = GL_COLOR_BUFFER_BIT;
    GLuint depth_buffer_bit = GL_DEPTH_BUFFER_BIT;
    glClear(color_buffer_bit | depth_buffer_bit);

    glUseProgram(app_context.program_id);

    glBindVertexArray(app_context.vao);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glUseProgram(0);
}

int main() {
    GLFWapp(app_context.width, app_context.height, app_context.title);

    return 0;
}
