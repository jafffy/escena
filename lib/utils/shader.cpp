//
// Created by jafffy on 12/25/19.
//

#include "utils/shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cerrno>

#include <sys/stat.h>
#include <unistd.h>

static std::string get_file_contents(const char *filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);

    if (in.good()) {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();

        return contents.str();
    }

    perror(filename);

    throw std::exception();
}

GLuint create_program(const char *vertex_shader_path, const char *fragment_shader_path) {
    GLuint program_id = glCreateProgram();

    std::string vertex_shader_src = get_file_contents(vertex_shader_path);
    std::string fragment_shader_src = get_file_contents(fragment_shader_path);

    const char *vertex_shader_src_c = vertex_shader_src.c_str();
    const char *fragment_shader_src_c = fragment_shader_src.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src_c, nullptr);
    glCompileShader(vertex_shader);
    glAttachShader(program_id, vertex_shader);

    {
        GLint is_compiled = 0;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);

        if (is_compiled == GL_FALSE) {
            GLint max_length = 0;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> error_log(max_length);
            glGetShaderInfoLog(vertex_shader, max_length, &max_length, &error_log[0]);

            fprintf(stderr, "%s\n", error_log.data());
        }
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_src_c, nullptr);
    glCompileShader(fragment_shader);
    glAttachShader(program_id, fragment_shader);

    {
        GLint is_compiled = 0;
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);

        if (is_compiled == GL_FALSE) {
            GLint max_length = 0;
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> error_log(max_length);
            glGetShaderInfoLog(fragment_shader, max_length, &max_length, &error_log[0]);

            fprintf(stderr, "%s\n", error_log.data());
        }
    }

    glLinkProgram(program_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program_id;
}
