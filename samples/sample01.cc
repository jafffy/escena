#include <cstdio>
#include <cerrno>

#include <unistd.h>

#include <GL/glew.h>

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLFWapp.h"

#include "utils/shader.h"

using namespace std;

static class {
public:
    const char *title = "Sample 01";
    int width = 800;
    int height = 600;

    GLuint program_id = 0;
    GLuint MVP_id = 0;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ibo = 0;

    glm::mat4 MVP = glm::mat4(1.0f);
} app_context;

void on_create() {
    app_context.program_id = create_program("./transform.vert", "./simple.frag");

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

    static const unsigned int index_buffer_data[] = {
            0, 1, 2
    };

    glGenBuffers(1, &app_context.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app_context.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    glDisableVertexAttribArray(0);

    app_context.MVP_id = glGetUniformLocation(app_context.program_id, "MVP");

    glBindVertexArray(0);
}

void on_destroy() {
    glDeleteProgram(app_context.program_id);

    glDeleteBuffers(1, &app_context.ibo);
    glDeleteBuffers(1, &app_context.vbo);
    glDeleteVertexArrays(1, &app_context.vao);
}

void on_update(double) {
    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 V = glm::lookAt(glm::vec3(0, 5, -5),
                              glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 P = glm::perspective(glm::pi<float>() / 4,
                                   (float) (app_context.width) / (float) (app_context.height),
                                   0.1f, 100.0f);

    app_context.MVP = P * V * M;
}

void on_render() {
    glViewport(0, 0, app_context.width, app_context.height);

    GLuint color_buffer_bit = GL_COLOR_BUFFER_BIT;
    GLuint depth_buffer_bit = GL_DEPTH_BUFFER_BIT;
    glClear(color_buffer_bit | depth_buffer_bit);

    glUseProgram(app_context.program_id);

    glUniformMatrix4fv(app_context.MVP_id, 1, GL_FALSE, glm::value_ptr(app_context.MVP));

    glBindVertexArray(app_context.vao);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glUseProgram(0);
}

int main() {
    GLFWapp(app_context.width, app_context.height, app_context.title);

    return 0;
}
