#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

// Forward declare constants
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

// ==================== Camera Class (Flying Simulator with Delta Time) ====================
class Camera {
private:
    glm::vec3 position;      // Camera position in world space
    glm::vec3 front;         // Direction camera is looking
    glm::vec3 up;            // Up vector
    glm::vec3 right;         // Right vector
    glm::vec3 worldUp;       // World up vector

    float pitch;             // Rotation around X-axis
    float yaw;               // Rotation around Y-axis
    float roll;              // Rotation around Z-axis

    float fov;               // Field of view for zoom
    glm::mat4 projection;
    float mouseSensitivity;

    // Orbit mode variables
    bool orbitMode;
    glm::vec3 orbitTarget;   // Point to orbit around (bus center)
    float orbitDistance;     // Distance from target
    float orbitPitch;        // Pitch angle for orbit
    float orbitYaw;          // Yaw angle for orbit

    // Bird's eye view state
    bool isBirdsEye;
    glm::vec3 savedPosition;
    float savedPitch;
    float savedYaw;
    float savedRoll;
    bool savedOrbitMode;

    // Interior view state
    bool isInteriorView;
    glm::vec3 interiorSavedPosition;
    float interiorSavedPitch;
    float interiorSavedYaw;
    float interiorSavedRoll;
    bool interiorSavedOrbitMode;

    // Driver view state
    bool isDriverView;
    glm::vec3 driverSavedPosition;
    float driverSavedPitch;
    float driverSavedYaw;
    float driverSavedRoll;
    bool driverSavedOrbitMode;

    // Look-at rotation mode
    bool lookAtRotationMode;
    glm::vec3 lookAtPoint;
    float lookAtDistance;
    float lookAtRotationAngle;  // Current rotation angle around look-at point

    void updateCameraVectors() {
        if (orbitMode) {
            // In orbit mode, calculate position based on spherical coordinates
            position.x = orbitTarget.x + orbitDistance * cos(glm::radians(orbitPitch)) * cos(glm::radians(orbitYaw));
            position.y = orbitTarget.y + orbitDistance * sin(glm::radians(orbitPitch));
            position.z = orbitTarget.z + orbitDistance * cos(glm::radians(orbitPitch)) * sin(glm::radians(orbitYaw));

            // Always look at the target
            front = glm::normalize(orbitTarget - position);
            right = glm::normalize(glm::cross(front, worldUp));
            up = glm::normalize(glm::cross(right, front));
        }
        else {
            // Free-flight mode
            glm::vec3 newFront;
            newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            newFront.y = sin(glm::radians(pitch));
            newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(newFront);

            right = glm::normalize(glm::cross(front, worldUp));
            up = glm::normalize(glm::cross(right, front));

            // Apply roll rotation
            if (roll != 0.0f) {
                glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(roll), front);
                up = glm::vec3(rollMatrix * glm::vec4(up, 0.0f));
                right = glm::normalize(glm::cross(front, up));
            }
        }
    }

    void updateProjectionMatrix() {
        projection = glm::perspective(glm::radians(fov),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
    }

public:
    Camera()
        : position(0.0f, 5.0f, 15.0f),
        front(0.0f, 0.0f, -1.0f),
        up(0.0f, 1.0f, 0.0f),
        worldUp(0.0f, 1.0f, 0.0f),
        pitch(0.0f),
        yaw(-90.0f),
        roll(0.0f),
        fov(45.0f),
        mouseSensitivity(0.15f),
        orbitMode(false),
        orbitTarget(0.0f, 0.0f, 0.0f),
        orbitDistance(15.0f),
        orbitPitch(20.0f),
        orbitYaw(-90.0f),
        isBirdsEye(false),
        savedPosition(0.0f, 5.0f, 15.0f),
        savedPitch(0.0f),
        savedYaw(-90.0f),
        savedRoll(0.0f),
        savedOrbitMode(false),
        isInteriorView(false),
        interiorSavedPosition(0.0f, 5.0f, 15.0f),
        interiorSavedPitch(0.0f),
        interiorSavedYaw(-90.0f),
        interiorSavedRoll(0.0f),
        interiorSavedOrbitMode(false),
        isDriverView(false),
        driverSavedPosition(0.0f, 5.0f, 15.0f),
        driverSavedPitch(0.0f),
        driverSavedYaw(-90.0f),
        driverSavedRoll(0.0f),
        driverSavedOrbitMode(false),
        lookAtRotationMode(false),
        lookAtPoint(0.0f, 0.0f, 0.0f),
        lookAtDistance(5.0f),
        lookAtRotationAngle(0.0f) {

        updateProjectionMatrix();
        updateCameraVectors();
    }

    // Movement controls with deltaTime (speed is units per second)
    void moveForward(float speed) {
        if (!orbitMode) {  // Only allow movement in free-flight mode
            position += front * speed;
        }
    }

    void moveBackward(float speed) {
        if (!orbitMode) {
            position -= front * speed;
        }
    }

    void moveLeft(float speed) {
        if (!orbitMode) {
            position -= right * speed;
        }
    }

    void moveRight(float speed) {
        if (!orbitMode) {
            position += right * speed;
        }
    }

    void moveUp(float speed) {
        if (!orbitMode) {
            position += worldUp * speed;  // Always move along world Y-axis
        }
    }

    void moveDown(float speed) {
        if (!orbitMode) {
            position -= worldUp * speed;  // Always move along world Y-axis
        }
    }

    // Rotation controls with deltaTime (angle is degrees per second already calculated)
    void rotatePitch(float angle) {
        if (!orbitMode) {
            pitch += angle;
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
            updateCameraVectors();
        }
    }

    void rotateYaw(float angle) {
        if (!orbitMode) {
            yaw += angle;
            updateCameraVectors();
        }
    }

    void rotateRoll(float angle) {
        if (!orbitMode) {
            roll += angle;
            if (roll > 360.0f) roll -= 360.0f;
            if (roll < -360.0f) roll += 360.0f;
            updateCameraVectors();
        }
    }

    // Bird's Eye View toggle
    void toggleBirdsEyeView() {
        if (!isBirdsEye) {
            // Save current state
            savedPosition = position;
            savedPitch = pitch;
            savedYaw = yaw;
            savedRoll = roll;
            savedOrbitMode = orbitMode;

            // Switch to bird's eye view
            orbitMode = false;
            position = glm::vec3(0.0f, 20.0f, 0.0f);
            pitch = -89.0f;
            yaw = -90.0f;
            roll = 0.0f;
            isBirdsEye = true;

            std::cout << "Bird's Eye View ACTIVATED" << std::endl;
        }
        else {
            // Restore saved state
            position = savedPosition;
            pitch = savedPitch;
            yaw = savedYaw;
            roll = savedRoll;
            orbitMode = savedOrbitMode;
            isBirdsEye = false;

            std::cout << "Returned to previous view" << std::endl;
        }

        updateCameraVectors();
    }

    // Interior view toggle
    void toggleInteriorView() {
        if (!isInteriorView) {
            // Save current state
            interiorSavedPosition = position;
            interiorSavedPitch = pitch;
            interiorSavedYaw = yaw;
            interiorSavedRoll = roll;
            interiorSavedOrbitMode = orbitMode;

            // Switch to interior view - position at the back of bus looking forward
            orbitMode = false;
            position = glm::vec3(-3.7f, 0.55f, 0.0f);  // Near rear of bus, eye level, centered in aisle
            pitch = 0.0f;
            yaw = 0.0f;  // Looking towards the front (negative X direction)
            roll = 0.0f;
            isInteriorView = true;
            isDriverView = false;

            std::cout << "INTERIOR VIEW ACTIVATED - You are now inside the bus" << std::endl;
        }
        else {
            // Restore saved state
            position = interiorSavedPosition;
            pitch = interiorSavedPitch;
            yaw = interiorSavedYaw;
            roll = interiorSavedRoll;
            orbitMode = interiorSavedOrbitMode;
            isInteriorView = false;

            std::cout << "Returned to exterior view" << std::endl;
        }

        updateCameraVectors();
    }

    // Driver view toggle
    void toggleDriverView() {
        if (!isDriverView) {
            // Save current state
            driverSavedPosition = position;
            driverSavedPitch = pitch;
            driverSavedYaw = yaw;
            driverSavedRoll = roll;
            driverSavedOrbitMode = orbitMode;

            // Switch to driver view - behind driver seat looking forward through windshield
            orbitMode = false;
            position = glm::vec3(-1.2f, 0.3f, 0.0f);  // Behind driver seat, slightly to the right
            pitch = 0.0f;
            yaw = -180.0f;  // Looking towards front of bus (negative X direction)
            roll = 0.0f;
            isDriverView = true;
            isInteriorView = false;

            std::cout << "DRIVER VIEW ACTIVATED - Behind driver's seat, looking through windshield" << std::endl;
        }
        else {
            // Restore saved state
            position = driverSavedPosition;
            pitch = driverSavedPitch;
            yaw = driverSavedYaw;
            roll = driverSavedRoll;
            orbitMode = driverSavedOrbitMode;
            isDriverView = false;

            std::cout << "Returned to previous view" << std::endl;
        }

        updateCameraVectors();
    }

    // Look-at rotation around a point
    void rotateCameraAroundLookAt(float deltaAngle) {
        if (!lookAtRotationMode) {
            // Initialize look-at rotation mode
            lookAtRotationMode = true;

            // Calculate look-at point (point in front of camera)
            lookAtPoint = position + front * 3.0f;  // 3 units in front
            lookAtDistance = glm::length(lookAtPoint - position);
            lookAtRotationAngle = 0.0f;

            std::cout << "Look-at rotation mode ACTIVATED - Camera rotating around point" << std::endl;
        }

        // Update rotation angle
        lookAtRotationAngle += deltaAngle;

        // Keep angle in 0-360 range
        if (lookAtRotationAngle >= 360.0f) lookAtRotationAngle -= 360.0f;
        if (lookAtRotationAngle < 0.0f) lookAtRotationAngle += 360.0f;

        // Calculate new camera position in a circle around look-at point
        // Rotate in XZ plane (horizontal circle)
        float angleRad = glm::radians(lookAtRotationAngle);

        // Get the initial direction vector from lookAtPoint to original position
        glm::vec3 initialOffset = position - lookAtPoint;
        float radius = glm::length(glm::vec2(initialOffset.x, initialOffset.z));

        // Calculate new position
        position.x = lookAtPoint.x + radius * cos(angleRad);
        position.z = lookAtPoint.z + radius * sin(angleRad);
        position.y = lookAtPoint.y + initialOffset.y;  // Keep same height

        // Make camera look at the point
        front = glm::normalize(lookAtPoint - position);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));

        // Update yaw and pitch based on new direction
        yaw = glm::degrees(atan2(front.z, front.x));
        pitch = glm::degrees(asin(front.y));
    }

    void stopLookAtRotation() {
        if (lookAtRotationMode) {
            lookAtRotationMode = false;
            std::cout << "Look-at rotation mode DEACTIVATED" << std::endl;
        }
    }

    bool isInLookAtRotationMode() const { return lookAtRotationMode; }

    bool isInInteriorView() const { return isInteriorView; }
    bool isInDriverView() const { return isDriverView; }

    // Toggle orbit mode and process mouse position for rotation
    void toggleOrbitMode() {
        orbitMode = !orbitMode;

        if (orbitMode) {
            // Entering orbit mode - calculate initial orbit parameters
            orbitTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // Orbit around bus center

            // Calculate distance from current position to target
            glm::vec3 diff = position - orbitTarget;
            orbitDistance = glm::length(diff);

            // Ensure minimum distance
            if (orbitDistance < 2.0f) orbitDistance = 15.0f;

            // Calculate initial angles from current position
            float horizontalDist = sqrt(diff.x * diff.x + diff.z * diff.z);

            if (horizontalDist > 0.001f) {
                orbitYaw = glm::degrees(atan2(diff.z, diff.x));
                orbitPitch = glm::degrees(atan2(diff.y, horizontalDist));
            }
            else {
                orbitYaw = -90.0f;
                orbitPitch = 20.0f;
            }

            std::cout << "ORBIT MODE ENABLED - Move cursor to rotate around bus" << std::endl;
        }
        else {
            // Exiting orbit mode - transition to free-flight mode
            // Keep the current camera position from orbit
            // Calculate free-flight angles based on current view direction

            // The front vector is already correct from orbit mode (looking at target)
            // We need to extract yaw and pitch from the current front vector
            yaw = glm::degrees(atan2(front.z, front.x));
            pitch = glm::degrees(asin(front.y));
            roll = 0.0f;

            // Position is already set correctly from orbit calculations
            // No need to change it

            std::cout << "ORBIT MODE DISABLED - Free-flight mode, movement keys enabled" << std::endl;
        }

        updateCameraVectors();
    }

    // Process cursor position for orbit rotation (when in orbit mode)
    void processOrbitRotation(float mouseX, float mouseY, float screenWidth, float screenHeight) {
        if (!orbitMode) return;

        // Calculate normalized position relative to screen center (-1 to 1)
        float normalizedX = (mouseX - screenWidth / 2.0f) / (screenWidth / 2.0f);
        float normalizedY = (mouseY - screenHeight / 2.0f) / (screenHeight / 2.0f);

        // Map mouse position to rotation angles
        // X controls yaw (horizontal rotation around bus)
        orbitYaw = normalizedX * 180.0f;  // -180 to +180 degrees

        // Y controls pitch (vertical angle)
        orbitPitch = -normalizedY * 89.0f;  // -89 to +89 degrees (inverted for natural feel)

        updateCameraVectors();
    }

    bool isOrbitMode() const { return orbitMode; }

    // Mouse scroll callback for zoom
    void processMouseScroll(float yoffset) {
        if (orbitMode) {
            // In orbit mode, scroll adjusts distance from target
            orbitDistance -= yoffset * 0.5f;
            if (orbitDistance < 2.0f) orbitDistance = 2.0f;
            if (orbitDistance > 50.0f) orbitDistance = 50.0f;
            updateCameraVectors();
        }
        else {
            // In free-flight mode, scroll adjusts FOV
            fov -= yoffset;
            if (fov < 1.0f) fov = 1.0f;
            if (fov > 90.0f) fov = 90.0f;
            updateProjectionMatrix();
        }
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 getProjectionMatrix() const {
        return projection;
    }

    glm::mat4 getBaseModel(float busPosition) const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(busPosition, 0.0f, 0.0f));
        return model;
    }

    void setUniforms(const ShaderProgram& shader) const {
        shader.setMat4("view", getViewMatrix());
        shader.setMat4("projection", projection);
    }

    void printInfo() const {
        std::cout << "Camera Mode: " << (orbitMode ? "ORBIT" : "FREE-FLIGHT") << std::endl;
        if (isBirdsEye) std::cout << "View: BIRD'S EYE" << std::endl;
        if (isInteriorView) std::cout << "View: INTERIOR" << std::endl;
        if (isDriverView) std::cout << "View: DRIVER" << std::endl;
        std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

        if (orbitMode) {
            std::cout << "Orbit Pitch: " << orbitPitch << " | Orbit Yaw: " << orbitYaw << std::endl;
            std::cout << "Orbit Distance: " << orbitDistance << std::endl;
        }
        else {
            std::cout << "Pitch: " << pitch << " | Yaw: " << yaw << " | Roll: " << roll << std::endl;
            std::cout << "FOV: " << fov << " degrees" << std::endl;
        }
    }
};

#endif