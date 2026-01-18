#ifndef BUSINTERIOR_H
#define BUSINTERIOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// ==================== BusInterior Class ====================
class BusInterior {
private:
    std::vector<Cube> interiorParts;

    void createFloor() {
        // Main floor - blue with pattern
        // Position floor below the seats (at the actual bus floor level)
        interiorParts.emplace_back(
            glm::vec3(0.5f, -0.2f, 0.0f),
            glm::vec3(7.8f, 0.05f, 1.8f),
            glm::vec3(0.2f, 0.3f, 0.6f)  // Blue floor
        );
    }

    void createCeiling() {
        // Ceiling
        interiorParts.emplace_back(
            glm::vec3(0.5f, 0.95f, 0.0f),
            glm::vec3(7.8f, 0.05f, 1.8f),
            glm::vec3(0.85f, 0.85f, 0.85f)  // Light gray ceiling
        );

        // Ceiling lights (4 panels)
        float lightPositions[] = { -2.0f, -0.5f, 1.0f, 2.5f };
        for (int i = 0; i < 4; i++) {
            interiorParts.emplace_back(
                glm::vec3(lightPositions[i], 0.92f, 0.0f),
                glm::vec3(0.6f, 0.02f, 0.4f),
                glm::vec3(1.0f, 1.0f, 0.9f)  // Warm white light
            );
        }
    }

    void createWalls() {
        // Left wall (interior side)
        interiorParts.emplace_back(
            glm::vec3(0.5f, 0.0f, -0.95f),
            glm::vec3(7.8f, 1.8f, 0.05f),
            glm::vec3(0.9f, 0.9f, 0.9f)
        );

        // Right wall (interior side)
        interiorParts.emplace_back(
            glm::vec3(0.5f, 0.0f, 0.95f),
            glm::vec3(7.8f, 1.8f, 0.05f),
            glm::vec3(0.9f, 0.9f, 0.9f)
        );
    }

    void createHandrails() {
        // Vertical handrail poles (yellow/gold) - 5 poles along the aisle
        float polePositions[] = { -2.5f, -1.0f, 0.5f, 2.0f, 3.5f };

        for (int i = 0; i < 5; i++) {
            // Vertical pole from floor to ceiling
            interiorParts.emplace_back(
                glm::vec3(polePositions[i], 0.35f, 0.0f),
                glm::vec3(0.04f, 1.1f, 0.04f),
                glm::vec3(0.95f, 0.75f, 0.15f)  // Gold/yellow color
            );
        }

        // Horizontal ceiling rail on left side
        interiorParts.emplace_back(
            glm::vec3(0.5f, 0.85f, -0.3f),
            glm::vec3(7.5f, 0.03f, 0.03f),
            glm::vec3(0.95f, 0.75f, 0.15f)
        );

        // Horizontal ceiling rail on right side
        interiorParts.emplace_back(
            glm::vec3(0.5f, 0.85f, 0.3f),
            glm::vec3(7.5f, 0.03f, 0.03f),
            glm::vec3(0.95f, 0.75f, 0.15f)
        );
    }

    void createSeat(float xPos, float zPos, bool facingForward) {
        // Seat colors
        glm::vec3 seatColor(0.85f, 0.4f, 0.2f);      // Orange seat
        glm::vec3 frameColor(0.7f, 0.7f, 0.7f);      // Gray frame
        glm::vec3 cushionColor(0.9f, 0.45f, 0.25f);  // Lighter orange cushion

        float seatWidth = 0.4f;
        float seatDepth = 0.4f;
        float seatHeight = 0.3f;
        float backHeight = 0.45f;

        // Position seats on the floor - floor is at y = -0.2f
        float floorY = -0.2f;
        float seatBaseY = floorY + 0.05f;  // Slightly above floor

        // All seats face forward (towards negative X direction, front of bus)
        // Seat back should be behind the seat (positive X direction)
        float backXOffset = seatDepth / 2.5f;  // Back is behind the seat

        // Seat base (horizontal part where you sit)
        interiorParts.emplace_back(
            glm::vec3(xPos, seatBaseY + seatHeight / 2, zPos),
            glm::vec3(seatDepth, 0.08f, seatWidth),  // X=depth, Z=width
            seatColor
        );

        // Seat cushion (on top of base)
        interiorParts.emplace_back(
            glm::vec3(xPos, seatBaseY + seatHeight / 2 + 0.05f, zPos),
            glm::vec3(seatDepth - 0.04f, 0.06f, seatWidth - 0.04f),
            cushionColor
        );

        // Seat back - positioned behind the seat, facing forward
        interiorParts.emplace_back(
            glm::vec3(xPos + backXOffset, seatBaseY + seatHeight + backHeight / 2, zPos),
            glm::vec3(0.08f, backHeight, seatWidth),  // Thin in X, tall in Y, wide in Z
            seatColor
        );

        // Seat back cushion
        interiorParts.emplace_back(
            glm::vec3(xPos + backXOffset - 0.02f, seatBaseY + seatHeight + backHeight / 2, zPos),
            glm::vec3(0.06f, backHeight - 0.08f, seatWidth - 0.04f),
            cushionColor
        );

        // Seat frame/legs (4 legs at corners) - connecting to floor
        float legXOffsets[] = { -seatDepth / 3, seatDepth / 3 };
        float legZOffsets[] = { -seatWidth / 3, seatWidth / 3 };

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                interiorParts.emplace_back(
                    glm::vec3(xPos + legXOffsets[i], seatBaseY + seatHeight / 4, zPos + legZOffsets[j]),
                    glm::vec3(0.04f, seatHeight / 2, 0.04f),
                    frameColor
                );
            }
        }

        // Armrests on both sides
        // Left armrest
        interiorParts.emplace_back(
            glm::vec3(xPos, seatBaseY + seatHeight + 0.1f, zPos - seatWidth / 2 - 0.03f),
            glm::vec3(seatDepth - 0.1f, 0.04f, 0.06f),
            frameColor
        );

        // Right armrest
        interiorParts.emplace_back(
            glm::vec3(xPos, seatBaseY + seatHeight + 0.1f, zPos + seatWidth / 2 + 0.03f),
            glm::vec3(seatDepth - 0.1f, 0.04f, 0.06f),
            frameColor
        );
    }

    void createSeats() {
        // Two columns of seats
        // Left side (z = -0.55) - no doors on this side
        // Right side (z = 0.55) - doors are further out at z = 1.0+

        float startX = -1.3f;
        float endX = 2.2f;
        int numRows = 7;
        float actualSpacing = (endX - startX) / (float)(numRows - 1);
        float leftZ = -0.55f;
        float rightZ = 0.55f;

        for (int i = 0; i < numRows; i++) {
            float xPos = startX + (float)i * actualSpacing;
            // Left column
            createSeat(xPos, leftZ, true);
            // Right column
            createSeat(xPos, rightZ, true);
        }
    }

    void createDriverArea() {
        glm::vec3 darkGray(0.25f, 0.25f, 0.25f);
        glm::vec3 lightGray(0.6f, 0.6f, 0.6f);
        glm::vec3 black(0.1f, 0.1f, 0.1f);
        glm::vec3 seatFabric(0.35f, 0.35f, 0.4f);  // Grayish seat fabric
        glm::vec3 chrome(0.8f, 0.8f, 0.85f);

        float floorY = -0.2f;

        // ===== DRIVER SEAT =====
        float seatX = -3.3f;
        float seatY = floorY + 0.25f;
        float seatZ = 0.5f;

        // Seat base
        interiorParts.emplace_back(
            glm::vec3(seatX, seatY, seatZ),
            glm::vec3(0.35f, 0.08f, 0.4f),
            seatFabric
        );

        // Seat cushion texture
        interiorParts.emplace_back(
            glm::vec3(seatX, seatY + 0.05f, seatZ),
            glm::vec3(0.33f, 0.06f, 0.38f),
            glm::vec3(0.4f, 0.4f, 0.45f)
        );

        // Seat back
        interiorParts.emplace_back(
            glm::vec3(seatX + 0.15f, seatY + 0.25f, seatZ),
            glm::vec3(0.08f, 0.5f, 0.4f),
            seatFabric
        );

        // Seat back cushion
        interiorParts.emplace_back(
            glm::vec3(seatX + 0.13f, seatY + 0.25f, seatZ),
            glm::vec3(0.06f, 0.48f, 0.38f),
            glm::vec3(0.4f, 0.4f, 0.45f)
        );

        // Headrest
        interiorParts.emplace_back(
            glm::vec3(seatX + 0.15f, seatY + 0.55f, seatZ),
            glm::vec3(0.08f, 0.15f, 0.25f),
            seatFabric
        );

        // Seat armrest (right side)
        interiorParts.emplace_back(
            glm::vec3(seatX, seatY + 0.15f, seatZ + 0.22f),
            glm::vec3(0.25f, 0.06f, 0.08f),
            darkGray
        );

        // Seat base frame
        interiorParts.emplace_back(
            glm::vec3(seatX, seatY - 0.15f, seatZ),
            glm::vec3(0.38f, 0.2f, 0.43f),
            black
        );

        // ===== DASHBOARD =====
        float dashX = -3.65f;
        float dashY = 0.1f;

        // Main dashboard panel
        interiorParts.emplace_back(
            glm::vec3(dashX, dashY, 0.0f),
            glm::vec3(0.12f, 0.4f, 1.5f),
            darkGray
        );

        // Dashboard top surface (angled)
        interiorParts.emplace_back(
            glm::vec3(dashX + 0.05f, dashY + 0.25f, 0.0f),
            glm::vec3(0.15f, 0.08f, 1.5f),
            black
        );

        // ===== INSTRUMENT CLUSTER =====
        float clusterX = dashX + 0.08f;
        float clusterY = dashY + 0.1f;
        float clusterZ = 0.3f;

        // Instrument cluster housing
        interiorParts.emplace_back(
            glm::vec3(clusterX, clusterY, clusterZ),
            glm::vec3(0.05f, 0.25f, 0.4f),
            black
        );

        // Speedometer display
        interiorParts.emplace_back(
            glm::vec3(clusterX + 0.02f, clusterY + 0.05f, clusterZ),
            glm::vec3(0.02f, 0.12f, 0.12f),
            glm::vec3(0.9f, 0.9f, 0.95f)  // White display
        );

        // Tachometer display
        interiorParts.emplace_back(
            glm::vec3(clusterX + 0.02f, clusterY - 0.05f, clusterZ),
            glm::vec3(0.02f, 0.12f, 0.12f),
            glm::vec3(0.9f, 0.9f, 0.95f)
        );

        // ===== STEERING WHEEL =====
        float wheelX = -3.55f;
        float wheelY = seatY + 0.1f;
        float wheelZ = 0.45f;

        // Steering column
        interiorParts.emplace_back(
            glm::vec3(wheelX + 0.1f, wheelY - 0.1f, wheelZ),
            glm::vec3(0.15f, 0.05f, 0.05f),
            darkGray
        );

        // Steering wheel rim
        interiorParts.emplace_back(
            glm::vec3(wheelX, wheelY, wheelZ),
            glm::vec3(0.03f, 0.3f, 0.3f),
            black
        );

        // Steering wheel center hub
        interiorParts.emplace_back(
            glm::vec3(wheelX, wheelY, wheelZ),
            glm::vec3(0.04f, 0.12f, 0.12f),
            darkGray
        );

        // Steering wheel spokes (3 spokes)
        for (int i = 0; i < 3; i++) {
            float angle = i * 120.0f;
            float rad = glm::radians(angle);
            float spokeY = wheelY + 0.09f * cos(rad);
            float spokeZ = wheelZ + 0.09f * sin(rad);

            interiorParts.emplace_back(
                glm::vec3(wheelX, spokeY, spokeZ),
                glm::vec3(0.03f, 0.08f, 0.02f),
                darkGray
            );
        }

        // ===== CONTROL PANEL (Right side of dashboard) =====
        float panelX = dashX + 0.05f;
        float panelY = dashY - 0.05f;
        float panelZ = -0.45f;

        // Control panel base
        interiorParts.emplace_back(
            glm::vec3(panelX, panelY, panelZ),
            glm::vec3(0.08f, 0.25f, 0.35f),
            darkGray
        );

        // Colorful control buttons (3x2 grid)
        glm::vec3 buttonColors[] = {
            glm::vec3(1.0f, 0.5f, 0.0f),  // Orange
            glm::vec3(1.0f, 1.0f, 0.0f),  // Yellow
            glm::vec3(0.0f, 1.0f, 0.0f),  // Green
            glm::vec3(1.0f, 0.0f, 0.0f),  // Red
            glm::vec3(0.0f, 0.5f, 1.0f),  // Blue
            glm::vec3(1.0f, 0.8f, 0.0f),  // Amber
        };

        int buttonIndex = 0;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 2; col++) {
                float btnY = panelY + 0.08f - row * 0.06f;
                float btnZ = panelZ - 0.08f + col * 0.08f;

                // Button
                interiorParts.emplace_back(
                    glm::vec3(panelX + 0.04f, btnY, btnZ),
                    glm::vec3(0.015f, 0.04f, 0.04f),
                    buttonColors[buttonIndex % 6]
                );

                buttonIndex++;
            }
        }

        // ===== GEAR SHIFTER =====
        float shifterX = seatX - 0.15f;
        float shifterY = seatY + 0.05f;
        float shifterZ = seatZ - 0.15f;

        // Shifter base
        interiorParts.emplace_back(
            glm::vec3(shifterX, shifterY - 0.08f, shifterZ),
            glm::vec3(0.08f, 0.05f, 0.12f),
            black
        );

        // Shifter lever
        interiorParts.emplace_back(
            glm::vec3(shifterX, shifterY + 0.05f, shifterZ),
            glm::vec3(0.02f, 0.18f, 0.02f),
            chrome
        );

        // Shifter knob
        interiorParts.emplace_back(
            glm::vec3(shifterX, shifterY + 0.15f, shifterZ),
            glm::vec3(0.04f, 0.06f, 0.04f),
            black
        );

        // ===== CENTER CONSOLE =====
        float consoleX = seatX - 0.15f;
        float consoleY = floorY + 0.12f;
        float consoleZ = 0.0f;

        // Console base
        interiorParts.emplace_back(
            glm::vec3(consoleX, consoleY, consoleZ),
            glm::vec3(0.25f, 0.2f, 0.5f),
            darkGray
        );

        // ===== WINDSHIELD FRAME =====
        // Left windshield pillar
        interiorParts.emplace_back(
            glm::vec3(-3.62f, 0.35f, 0.85f),
            glm::vec3(0.08f, 0.9f, 0.08f),
            black
        );

        // Right windshield pillar
        interiorParts.emplace_back(
            glm::vec3(-3.62f, 0.35f, -0.85f),
            glm::vec3(0.08f, 0.9f, 0.08f),
            black
        );

        // Top windshield frame
        interiorParts.emplace_back(
            glm::vec3(-3.62f, 0.8f, 0.0f),
            glm::vec3(0.08f, 0.08f, 1.7f),
            black
        );

        // ===== DOOR PANEL (Driver side - left) =====
        float doorX = -3.1f;
        float doorY = 0.2f;
        float doorZ = 0.95f;

        // Door panel
        interiorParts.emplace_back(
            glm::vec3(doorX, doorY, doorZ),
            glm::vec3(0.6f, 0.8f, 0.08f),
            lightGray
        );

        // Door handle
        interiorParts.emplace_back(
            glm::vec3(doorX - 0.15f, doorY - 0.1f, doorZ - 0.03f),
            glm::vec3(0.12f, 0.04f, 0.03f),
            chrome
        );

        // Window control buttons on door
        for (int i = 0; i < 2; i++) {
            interiorParts.emplace_back(
                glm::vec3(doorX - 0.2f, doorY - 0.2f - i * 0.06f, doorZ - 0.03f),
                glm::vec3(0.08f, 0.04f, 0.02f),
                black
            );
        }
    }

public:
    BusInterior() {}

    void initialize() {
        createFloor();
        createCeiling();
        createWalls();
        createHandrails();
        createSeats();
        createDriverArea();

        // Setup all cubes
        for (size_t i = 0; i < interiorParts.size(); i++) {
            interiorParts[i].setup();
        }
    }

    void draw(const ShaderProgram& shader, const glm::mat4& baseModel) const {
        for (size_t i = 0; i < interiorParts.size(); i++) {
            interiorParts[i].draw(shader, baseModel);
        }
    }

    void cleanup() {
        for (size_t i = 0; i < interiorParts.size(); i++) {
            interiorParts[i].cleanup();
        }
    }
};

#endif