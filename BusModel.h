#ifndef BUSMODEL_H
#define BUSMODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

// ==================== BusModel Class ====================
class BusModel {
private:
    std::vector<Cube> bodyCubes;
    std::vector<Cube> lightCubes;
    std::vector<Cylinder> wheels;
    std::vector<WheelSpokes> wheelSpokes;

    // Door system
    std::vector<Cube> frontDoorLeft;
    std::vector<Cube> frontDoorRight;
    std::vector<Cube> rearDoorLeft;
    std::vector<Cube> rearDoorRight;

    bool lightsOn;
    float doorOffset;  // Current door offset (0.0 = closed, 1.0 = fully open)
    float doorSpeed;   // Animation speed
    bool doorsOpening;
    bool doorsClosing;

    void createBodyCubes() {
        bodyCubes.emplace_back(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(8.0f, 2.0f, 2.0f), glm::vec3(0.96f, 0.95f, 0.92f));
        bodyCubes.emplace_back(glm::vec3(-0.3f, 0.03f, 1.01f), glm::vec3(5.2f, 0.1f, 0.03f), glm::vec3(0.45f, 0.10f, 0.18f));
        bodyCubes.emplace_back(glm::vec3(0.5f, 0.03f, 1.01f), glm::vec3(5.2f, 0.1f, 0.03f), glm::vec3(0.45f, 0.10f, 0.18f));
        bodyCubes.emplace_back(glm::vec3(1.9f, 0.03f, 1.01f), glm::vec3(5.2f, 0.1f, 0.03f), glm::vec3(0.45f, 0.10f, 0.18f));
        bodyCubes.emplace_back(glm::vec3(0.5f, -0.15f, -1.02f), glm::vec3(8.05f, 0.12f, 0.03f), glm::vec3(0.45f, 0.10f, 0.18f));
        bodyCubes.emplace_back(glm::vec3(0.5f, 1.0f, 0.0f), glm::vec3(8.0f, 0.1f, 1.8f), glm::vec3(1.0f, 1.0f, 1.0f));
        bodyCubes.emplace_back(glm::vec3(0.5f, -0.65f, 0.0f), glm::vec3(8.2f, 0.7f, 2.0f), glm::vec3(0.45f, 0.10f, 0.18f));
        bodyCubes.emplace_back(glm::vec3(-3.7f, -0.4f, 0.0f), glm::vec3(0.1f, 0.8f, 2.0f), glm::vec3(0.45f, 0.10f, 0.18f));
        bodyCubes.emplace_back(glm::vec3(-3.75f, -0.45f, 0.0f), glm::vec3(0.05f, 0.5f, 1.8f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.8f, -0.15f, 0.0f), glm::vec3(0.02f, 0.1f, 1.8f), glm::vec3(1.0f, 1.0f, 1.0f));

        addDriverWindows();
        addSideMirrors();
        addDoorFrames();  // Only add frames, doors are separate now
        addPassengerWindows();
        addWindshield();
        addRearWindows();
        addBottomPanels();
    }

    void addDriverWindows() {
        bodyCubes.emplace_back(glm::vec3(-3.2f, 0.3f, 1.05f), glm::vec3(0.4f, 0.6f, 0.02f), glm::vec3(0.5f, 0.65f, 0.75f));
        bodyCubes.emplace_back(glm::vec3(-3.2f, 0.3f, 1.06f), glm::vec3(0.42f, 0.62f, 0.01f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.2f, 0.3f, 1.07f), glm::vec3(0.02f, 0.6f, 0.015f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.2f, 0.3f, -1.05f), glm::vec3(0.4f, 0.6f, 0.02f), glm::vec3(0.5f, 0.65f, 0.75f));
        bodyCubes.emplace_back(glm::vec3(-3.2f, 0.3f, -1.06f), glm::vec3(0.42f, 0.62f, 0.01f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.2f, 0.3f, -1.07f), glm::vec3(0.02f, 0.6f, 0.015f), glm::vec3(0.1f, 0.1f, 0.1f));
    }

    void addSideMirrors() {
        bodyCubes.emplace_back(glm::vec3(-3.5f, 0.2f, 1.15f), glm::vec3(0.05f, 0.05f, 0.15f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.45f, 0.2f, 1.28f), glm::vec3(0.15f, 0.25f, 0.05f), glm::vec3(0.7f, 0.8f, 0.9f));
        bodyCubes.emplace_back(glm::vec3(-3.5f, 0.2f, 1.25f), glm::vec3(0.18f, 0.28f, 0.08f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.5f, 0.2f, -1.15f), glm::vec3(0.05f, 0.05f, 0.15f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.45f, 0.2f, -1.28f), glm::vec3(0.15f, 0.25f, 0.05f), glm::vec3(0.7f, 0.8f, 0.9f));
        bodyCubes.emplace_back(glm::vec3(-3.5f, 0.2f, -1.25f), glm::vec3(0.18f, 0.28f, 0.08f), glm::vec3(0.1f, 0.1f, 0.1f));
    }

    void addDoorFrames() {
        // Front door frame
        bodyCubes.emplace_back(glm::vec3(-2.0f, -0.3f, 1.05f), glm::vec3(0.9f, 1.4f, 0.03f), glm::vec3(0.2f, 0.2f, 0.2f));

        // Rear door frame
        bodyCubes.emplace_back(glm::vec3(2.9f, -0.3f, 1.05f), glm::vec3(0.9f, 1.4f, 0.03f), glm::vec3(0.2f, 0.2f, 0.2f));
    }

    void createDoorPanel(std::vector<Cube>& doorPanel, float xPos, bool isLeft) {
        doorPanel.clear();

        // Main door panel
        doorPanel.emplace_back(glm::vec3(xPos, -0.3f, 1.06f), glm::vec3(0.42f, 1.2f, 0.02f), glm::vec3(0.3f, 0.3f, 0.3f));

        // Window on door
        doorPanel.emplace_back(glm::vec3(xPos, 0.0f, 1.07f), glm::vec3(0.32f, 0.6f, 0.01f), glm::vec3(0.5f, 0.7f, 0.85f));

        // Door handle
        float handleX = isLeft ? xPos - 0.15f : xPos + 0.15f;
        doorPanel.emplace_back(glm::vec3(handleX, -0.3f, 1.075f), glm::vec3(0.05f, 0.15f, 0.02f), glm::vec3(0.8f, 0.7f, 0.2f));
    }

    void addDoors() {
        // Create front door panels (left and right) - positioned to meet in center when closed
        createDoorPanel(frontDoorLeft, -2.225f, true);   // Left panel center
        createDoorPanel(frontDoorRight, -1.775f, false); // Right panel center

        // Create rear door panels (left and right) - positioned to meet in center when closed
        createDoorPanel(rearDoorLeft, 2.675f, true);     // Left panel center
        createDoorPanel(rearDoorRight, 3.125f, false);   // Right panel center

        // Setup all door cubes
        for (auto& cube : frontDoorLeft) cube.setup();
        for (auto& cube : frontDoorRight) cube.setup();
        for (auto& cube : rearDoorLeft) cube.setup();
        for (auto& cube : rearDoorRight) cube.setup();
    }

    void addPassengerWindows() {
        float positions[] = { -1.1f, -0.1f, 0.9f, 1.8f, 3.8f };
        glm::vec3 borderCol(0.1f, 0.1f, 0.1f);

        for (float x : positions) {
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, 1.05f), glm::vec3(0.5f, 0.5f, 0.02f), glm::vec3(0.4f, 0.5f, 0.6f));
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, 1.06f), glm::vec3(0.52f, 0.52f, 0.01f), borderCol);
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, 1.07f), glm::vec3(0.02f, 0.5f, 0.015f), borderCol);
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, 1.07f), glm::vec3(0.5f, 0.02f, 0.015f), borderCol);
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, -1.05f), glm::vec3(0.5f, 0.5f, 0.02f), glm::vec3(0.4f, 0.5f, 0.6f));
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, -1.06f), glm::vec3(0.52f, 0.52f, 0.01f), borderCol);
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, -1.07f), glm::vec3(0.02f, 0.5f, 0.015f), borderCol);
            bodyCubes.emplace_back(glm::vec3(x, 0.5f, -1.07f), glm::vec3(0.5f, 0.02f, 0.015f), borderCol);
        }
    }

    void addWindshield() {
        bodyCubes.emplace_back(glm::vec3(-3.6f, 0.3f, 0.0f), glm::vec3(0.15f, 0.8f, 1.9f), glm::vec3(0.5f, 0.65f, 0.75f));
        bodyCubes.emplace_back(glm::vec3(-3.59f, 0.3f, 0.0f), glm::vec3(0.14f, 0.82f, 1.92f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(-3.58f, 0.3f, 0.0f), glm::vec3(0.13f, 0.8f, 0.03f), glm::vec3(0.1f, 0.1f, 0.1f));
    }

    void addRearWindows() {
        bodyCubes.emplace_back(glm::vec3(4.55f, 0.4f, -0.45f), glm::vec3(0.02f, 0.7f, 0.7f), glm::vec3(0.4f, 0.5f, 0.6f));
        bodyCubes.emplace_back(glm::vec3(4.55f, 0.4f, 0.45f), glm::vec3(0.02f, 0.7f, 0.7f), glm::vec3(0.4f, 0.5f, 0.6f));
    }

    void addBottomPanels() {
        bodyCubes.emplace_back(glm::vec3(-3.8f, -0.9f, 0.0f), glm::vec3(0.02f, 0.2f, 2.0f), glm::vec3(0.1f, 0.1f, 0.1f));
        bodyCubes.emplace_back(glm::vec3(4.6f, -0.9f, 0.0f), glm::vec3(0.02f, 0.2f, 2.0f), glm::vec3(0.1f, 0.1f, 0.1f));
    }

    void createLightCubes() {
        glm::vec3 headlightCol = lightsOn ? glm::vec3(1.0f, 1.0f, 0.0f) : glm::vec3(0.1f, 0.1f, 0.1f);
        glm::vec3 taillightCol = lightsOn ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.1f, 0.0f, 0.0f);

        lightCubes.emplace_back(glm::vec3(-3.82f, -0.6f, 0.7f), glm::vec3(0.02f, 0.2f, 0.4f), headlightCol);
        lightCubes.emplace_back(glm::vec3(-3.82f, -0.6f, -0.7f), glm::vec3(0.02f, 0.2f, 0.4f), headlightCol);
        lightCubes.emplace_back(glm::vec3(4.62f, -0.6f, 0.7f), glm::vec3(0.02f, 0.2f, 0.4f), taillightCol);
        lightCubes.emplace_back(glm::vec3(4.62f, -0.6f, -0.7f), glm::vec3(0.02f, 0.2f, 0.4f), taillightCol);
    }

    void createWheels(float x, float y) {
        auto addWheel = [&](float z) {
            wheels.emplace_back(glm::vec3(x, y, z), 0.4f, 0.2f, glm::vec3(0.1f, 0.1f, 0.1f));
            wheels.emplace_back(glm::vec3(x, y, z), 0.25f, 0.22f, glm::vec3(0.5f, 0.5f, 0.5f));
            wheelSpokes.emplace_back(glm::vec3(x, y, z), 0.25f, 0.22f);
            };

        addWheel(1.0f);
        addWheel(-1.0f);
    }

public:
    float busPosition;

    BusModel() : lightsOn(true), busPosition(0.0f), doorOffset(0.0f),
        doorSpeed(0.02f), doorsOpening(false), doorsClosing(false) {
    }

    void initialize() {
        createBodyCubes();
        createLightCubes();
        addDoors();
        createWheels(-3.1f, -1.0f);
        createWheels(-0.5f, -1.0f);
        createWheels(2.0f, -1.0f);
        createWheels(3.8f, -1.0f);

        for (auto& cube : bodyCubes) cube.setup();
        for (auto& cube : lightCubes) cube.setup();
        for (auto& wheel : wheels) wheel.setup();
        for (auto& spoke : wheelSpokes) spoke.setup(6);
    }

    void toggleLights() {
        lightsOn = !lightsOn;
        for (auto& cube : lightCubes) cube.cleanup();
        lightCubes.clear();
        createLightCubes();
        for (auto& cube : lightCubes) cube.setup();
    }

    void openDoors() {
        if (!doorsOpening && doorOffset < 1.0f) {
            doorsOpening = true;
            doorsClosing = false;
            std::cout << "Opening doors..." << std::endl;
        }
    }

    void closeDoors() {
        if (!doorsClosing && doorOffset > 0.0f) {
            doorsClosing = true;
            doorsOpening = false;
            std::cout << "Closing doors..." << std::endl;
        }
    }

    void updateDoors() {
        if (doorsOpening) {
            doorOffset += doorSpeed;
            if (doorOffset >= 1.0f) {
                doorOffset = 1.0f;
                doorsOpening = false;
                std::cout << "Doors fully open" << std::endl;
            }
        }

        if (doorsClosing) {
            doorOffset -= doorSpeed;
            if (doorOffset <= 0.0f) {
                doorOffset = 0.0f;
                doorsClosing = false;
                std::cout << "Doors fully closed" << std::endl;
            }
        }
    }

    void updateWheelRotation(float rotation) {
        for (auto& wheel : wheels) wheel.rotation = rotation;
        for (auto& spoke : wheelSpokes) spoke.rotation = rotation;
    }

    void draw(const ShaderProgram& shader, const glm::mat4& baseModel) const {
        // Draw main body
        for (const auto& cube : bodyCubes) cube.draw(shader, baseModel);
        for (const auto& cube : lightCubes) cube.draw(shader, baseModel);
        for (const auto& wheel : wheels) wheel.draw(shader, baseModel);
        for (const auto& spoke : wheelSpokes) spoke.draw(shader, baseModel);

        // Draw sliding doors with offset
        float maxSlide = 0.45f;  // Maximum slide distance

        // Front doors
        glm::mat4 frontLeftTransform = glm::translate(baseModel, glm::vec3(-doorOffset * maxSlide, 0.0f, 0.0f));
        glm::mat4 frontRightTransform = glm::translate(baseModel, glm::vec3(doorOffset * maxSlide, 0.0f, 0.0f));

        for (const auto& cube : frontDoorLeft) cube.draw(shader, frontLeftTransform);
        for (const auto& cube : frontDoorRight) cube.draw(shader, frontRightTransform);

        // Rear doors
        glm::mat4 rearLeftTransform = glm::translate(baseModel, glm::vec3(-doorOffset * maxSlide, 0.0f, 0.0f));
        glm::mat4 rearRightTransform = glm::translate(baseModel, glm::vec3(doorOffset * maxSlide, 0.0f, 0.0f));

        for (const auto& cube : rearDoorLeft) cube.draw(shader, rearLeftTransform);
        for (const auto& cube : rearDoorRight) cube.draw(shader, rearRightTransform);
    }

    void cleanup() {
        for (auto& cube : bodyCubes) cube.cleanup();
        for (auto& cube : lightCubes) cube.cleanup();
        for (auto& cube : frontDoorLeft) cube.cleanup();
        for (auto& cube : frontDoorRight) cube.cleanup();
        for (auto& cube : rearDoorLeft) cube.cleanup();
        for (auto& cube : rearDoorRight) cube.cleanup();
        for (auto& wheel : wheels) wheel.cleanup();
        for (auto& spoke : wheelSpokes) spoke.cleanup();
    }
};

#endif