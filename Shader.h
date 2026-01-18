#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class ShaderProgram {
private:
    unsigned int programID;

    inline std::string loadSource(const char* filePath) {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(filePath);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            return stream.str();
        }
        catch (...) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "
                << filePath << std::endl;
            return "";
        }
    }

    inline unsigned int compileShader(unsigned int type, const char* source) {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                << infoLog << std::endl;
        }
        return shader;
    }

public:
    ShaderProgram() : programID(0) {}

    inline bool create(const char* vPath = "vertex.glsl",
        const char* fPath = "fragment.glsl") {
        std::string vertexSource = loadSource(vPath);
        std::string fragmentSource = loadSource(fPath);

        if (vertexSource.empty() || fragmentSource.empty()) {
            std::cerr << "ERROR::SHADER::EMPTY_SOURCE" << std::endl;
            return false;
        }

        unsigned int vertexShader =
            compileShader(GL_VERTEX_SHADER, vertexSource.c_str());
        unsigned int fragmentShader =
            compileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);

        int success;
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(programID, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::LINK_FAILED\n"
                << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return success;
    }

    inline void use() const {
        glUseProgram(programID);
    }

    inline void setMat4(const char* name, const glm::mat4& mat) const {
        glUniformMatrix4fv(
            glGetUniformLocation(programID, name),
            1, GL_FALSE, glm::value_ptr(mat)
        );
    }

    inline unsigned int getID() const {
        return programID;
    }

    inline void cleanup() {
        glDeleteProgram(programID);
    }
};

#endif
