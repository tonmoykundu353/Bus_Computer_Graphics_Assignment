#ifndef CLASS_H
#define CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

const float PI = 3.1415926536f;


// ==================== Cube Class ====================
class Cube {
private:
    unsigned int VAO, VBO, EBO;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 color;
    unsigned int indexCount;

public:
    Cube(const glm::vec3& pos, const glm::vec3& scl, const glm::vec3& col)
        : VAO(0), VBO(0), EBO(0), position(pos), scale(scl), color(col), indexCount(0) {
    }

    void setup() {
        // Define 8 unique vertices for a cube
        std::vector<float> vertices = {
            // Position (x, y, z)     Color (r, g, b)
            -0.5f, -0.5f, -0.5f,     color.r, color.g, color.b,  // 0
             0.5f, -0.5f, -0.5f,     color.r, color.g, color.b,  // 1
             0.5f,  0.5f, -0.5f,     color.r, color.g, color.b,  // 2
            -0.5f,  0.5f, -0.5f,     color.r, color.g, color.b,  // 3
            -0.5f, -0.5f,  0.5f,     color.r, color.g, color.b,  // 4
             0.5f, -0.5f,  0.5f,     color.r, color.g, color.b,  // 5
             0.5f,  0.5f,  0.5f,     color.r, color.g, color.b,  // 6
            -0.5f,  0.5f,  0.5f,     color.r, color.g, color.b   // 7
        };

        // Define indices for 6 faces (2 triangles per face)
        std::vector<unsigned int> indices = {
            // Front face
            4, 5, 6,  4, 6, 7,
            // Back face
            1, 0, 3,  1, 3, 2,
            // Left face
            0, 4, 7,  0, 7, 3,
            // Right face
            5, 1, 2,  5, 2, 6,
            // Top face
            7, 6, 2,  7, 2, 3,
            // Bottom face
            0, 1, 5,  0, 5, 4
        };

        indexCount = indices.size();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw(const ShaderProgram& shader, const glm::mat4& baseModel) const {
        glm::mat4 model = baseModel;
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};

// ==================== Cylinder Class (with EBO) ====================
class Cylinder {
private:
    unsigned int VAO, VBO, EBO;
    glm::vec3 position;
    float radius;
    float height;
    glm::vec3 color;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void createGeometry() {
        vertices.clear();
        indices.clear();
        int segments = 30;

        // Generate vertices for top and bottom circles
        // Center vertices for caps
        vertices.insert(vertices.end(), { 0.0f, 0.0f, height / 2, color.r, color.g, color.b });  // 0: top center
        vertices.insert(vertices.end(), { 0.0f, 0.0f, -height / 2, color.r, color.g, color.b }); // 1: bottom center

        // Circle vertices for top cap
        for (int i = 0; i < segments; i++) {
            float theta = (float)i / segments * 2.0f * PI;
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            vertices.insert(vertices.end(), { x, y, height / 2, color.r, color.g, color.b });
        }

        // Circle vertices for bottom cap
        for (int i = 0; i < segments; i++) {
            float theta = (float)i / segments * 2.0f * PI;
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            vertices.insert(vertices.end(), { x, y, -height / 2, color.r, color.g, color.b });
        }

        // Indices for cylinder side
        for (int i = 0; i < segments; i++) {
            int topCurrent = 2 + i;
            int topNext = 2 + (i + 1) % segments;
            int bottomCurrent = 2 + segments + i;
            int bottomNext = 2 + segments + (i + 1) % segments;

            // Two triangles for each side quad
            indices.push_back(topCurrent);
            indices.push_back(bottomCurrent);
            indices.push_back(topNext);

            indices.push_back(bottomCurrent);
            indices.push_back(bottomNext);
            indices.push_back(topNext);
        }

        // Indices for top cap
        for (int i = 0; i < segments; i++) {
            indices.push_back(0);
            indices.push_back(2 + i);
            indices.push_back(2 + (i + 1) % segments);
        }

        // Indices for bottom cap
        for (int i = 0; i < segments; i++) {
            indices.push_back(1);
            indices.push_back(2 + segments + (i + 1) % segments);
            indices.push_back(2 + segments + i);
        }
    }

public:
    float rotation;

    Cylinder(const glm::vec3& pos, float r, float h, const glm::vec3& col)
        : VAO(0), VBO(0), EBO(0), position(pos), radius(r), height(h), color(col), rotation(0.0f) {
    }

    void setup() {
        createGeometry();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw(const ShaderProgram& shader, const glm::mat4& baseModel) const {
        glm::mat4 model = baseModel;
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};


// ==================== WheelSpokes Class ====================
class WheelSpokes {
private:
    unsigned int VAO, VBO;
    glm::vec3 position;
    float radius;
    float height;
    std::vector<float> vertices;

    void createSpokes(int numSpokes) {
        vertices.clear();
        glm::vec3 spokeColor(1.0f, 1.0f, 1.0f);

        auto addVertex = [this](float x, float y, float z, const glm::vec3& col) {
            vertices.insert(vertices.end(), { x, y, z, col.r, col.g, col.b });
            };

        for (int i = 0; i < numSpokes; i++) {
            float angle = (float)i / numSpokes * 2.0f * PI;
            float spokeWidth = 2.0f * PI / numSpokes * 0.3f;

            addVertex(0.0f, 0.0f, height / 2 + 0.01f, spokeColor);
            addVertex(radius * 0.7f * cos(angle), radius * 0.7f * sin(angle), height / 2 + 0.01f, spokeColor);
            addVertex(radius * 0.7f * cos(angle + spokeWidth), radius * 0.7f * sin(angle + spokeWidth), height / 2 + 0.01f, spokeColor);
        }

        for (int i = 0; i < numSpokes; i++) {
            float angle = (float)i / numSpokes * 2.0f * PI;
            float spokeWidth = 2.0f * PI / numSpokes * 0.3f;

            addVertex(0.0f, 0.0f, -height / 2 - 0.01f, spokeColor);
            addVertex(radius * 0.7f * cos(angle + spokeWidth), radius * 0.7f * sin(angle + spokeWidth), -height / 2 - 0.01f, spokeColor);
            addVertex(radius * 0.7f * cos(angle), radius * 0.7f * sin(angle), -height / 2 - 0.01f, spokeColor);
        }

        int segments = 20;
        float hubRadius = radius * 0.15f;
        glm::vec3 hubColor(0.7f, 0.7f, 0.7f);

        for (int i = 0; i < segments; i++) {
            float theta1 = (float)i / segments * 2.0f * PI;
            float theta2 = (float)(i + 1) / segments * 2.0f * PI;

            addVertex(0.0f, 0.0f, height / 2 + 0.01f, hubColor);
            addVertex(hubRadius * cos(theta1), hubRadius * sin(theta1), height / 2 + 0.01f, hubColor);
            addVertex(hubRadius * cos(theta2), hubRadius * sin(theta2), height / 2 + 0.01f, hubColor);

            addVertex(0.0f, 0.0f, -height / 2 - 0.01f, hubColor);
            addVertex(hubRadius * cos(theta2), hubRadius * sin(theta2), -height / 2 - 0.01f, hubColor);
            addVertex(hubRadius * cos(theta1), hubRadius * sin(theta1), -height / 2 - 0.01f, hubColor);
        }
    }

public:
    float rotation;

    WheelSpokes(const glm::vec3& pos, float r, float h)
        : VAO(0), VBO(0), position(pos), radius(r), height(h), rotation(0.0f) {
    }

    void setup(int numSpokes = 6) {
        createSpokes(numSpokes);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void draw(const ShaderProgram& shader, const glm::mat4& baseModel) const {
        glm::mat4 model = baseModel;
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
        glBindVertexArray(0);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

#endif
