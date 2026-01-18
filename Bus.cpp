#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Vertices.h"
#include "Class.h"
#include "BusModel.h"
#include "BusInterior.h"

// Constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

#include "Camera.h"

// Forward declarations
class Cube;
class Cylinder;
class WheelSpokes;
class BusModel;
class BusInterior;
class Camera;
class InputHandler;

// ==================== InputHandler Class ====================
class InputHandler {
private:
    GLFWwindow* window;
    Camera& camera;
    BusModel& bus;
    BusInterior& interior;
    float& wheelRotation;
    bool& showInterior;
    bool fullscreen;
    float deltaTime;

    static InputHandler* instance;

    static void keyCallbackStatic(GLFWwindow* win, int key, int scancode, int action, int mods) {
        if (instance) instance->keyCallback(win, key, scancode, action, mods);
    }

    static void scrollCallbackStatic(GLFWwindow* win, double xoffset, double yoffset) {
        if (instance) instance->scrollCallback(win, xoffset, yoffset);
    }

    void scrollCallback(GLFWwindow* win, double xoffset, double yoffset) {
        camera.processMouseScroll(static_cast<float>(yoffset));
    }

    void toggleOrbitMode() {
        camera.toggleOrbitMode();

        if (camera.isOrbitMode()) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            std::cout << "Cursor controls view angle | Scroll to zoom | Movement keys DISABLED" << std::endl;
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            std::cout << "Use WASD/E/Q to move | X/Y/Z to rotate | Movement keys ENABLED" << std::endl;
        }
    }

    void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
        if (action != GLFW_PRESS && action != GLFW_REPEAT) return;

        float moveSpeed = 2.5f;
        float rotateSpeed = 45.0f;
        float busSpeed = 5.0f;
        float wheelSpeed = 200.0f;

        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(win, true);
            break;

            // Camera Movement
        case GLFW_KEY_W:
            camera.moveForward(moveSpeed * deltaTime);
            break;
        case GLFW_KEY_S:
            camera.moveBackward(moveSpeed * deltaTime);
            break;
        case GLFW_KEY_A:
            camera.moveLeft(moveSpeed * deltaTime);
            break;
        case GLFW_KEY_D:
            camera.moveRight(moveSpeed * deltaTime);
            break;
        case GLFW_KEY_E:
            camera.moveUp(moveSpeed * deltaTime);
            break;
        case GLFW_KEY_Q:
            camera.moveDown(moveSpeed * deltaTime);
            break;

            // Camera Rotation
        case GLFW_KEY_X:
            if (mods & GLFW_MOD_SHIFT)
                camera.rotatePitch(-rotateSpeed * deltaTime);
            else
                camera.rotatePitch(rotateSpeed * deltaTime);
            break;
        case GLFW_KEY_Y:
            if (mods & GLFW_MOD_SHIFT)
                camera.rotateYaw(-rotateSpeed * deltaTime);
            else
                camera.rotateYaw(rotateSpeed * deltaTime);
            break;
        case GLFW_KEY_Z:
            if (mods & GLFW_MOD_SHIFT)
                camera.rotateRoll(-rotateSpeed * deltaTime);
            else
                camera.rotateRoll(rotateSpeed * deltaTime);
            break;

            // Bird's Eye View
        case GLFW_KEY_B:
            camera.toggleBirdsEyeView();
            break;

            // Bus Controls
        case GLFW_KEY_F:
            bus.busPosition -= busSpeed * deltaTime;
            wheelRotation += wheelSpeed * deltaTime;
            if (wheelRotation >= 360.0f) wheelRotation -= 360.0f;
            break;
        case GLFW_KEY_G:
            bus.busPosition += busSpeed * deltaTime;
            wheelRotation -= wheelSpeed * deltaTime;
            if (wheelRotation <= -360.0f) wheelRotation += 360.0f;
            break;
        case GLFW_KEY_R:
            wheelRotation += wheelSpeed * deltaTime;
            if (wheelRotation >= 360.0f) wheelRotation -= 360.0f;
            break;
        case GLFW_KEY_O:
            bus.toggleLights();
            break;

            // Door Controls
        case GLFW_KEY_1:
            bus.openDoors();
            break;
        case GLFW_KEY_2:
            bus.closeDoors();
            break;

            // Interior View Toggle
        case GLFW_KEY_3:
            camera.toggleInteriorView();
            showInterior = camera.isInInteriorView() || camera.isInDriverView();
            break;
        case GLFW_KEY_4:
            if (camera.isInInteriorView()) {
                camera.toggleInteriorView();
                showInterior = false;
            }
            break;

            // Driver View Toggle
        case GLFW_KEY_5:
            camera.toggleDriverView();
            showInterior = camera.isInInteriorView() || camera.isInDriverView();
            break;
        case GLFW_KEY_6:
            if (camera.isInDriverView()) {
                camera.toggleDriverView();
                showInterior = false;
            }
            break;

            // Debug info
        case GLFW_KEY_I:
            camera.printInfo();
            std::cout << "FPS: " << (1.0f / deltaTime) << std::endl;
            break;

            // Toggle orbit mode
        case GLFW_KEY_M:
            toggleOrbitMode();
            break;

            // Fullscreen
        case GLFW_KEY_F11:
            toggleFullscreen();
            break;


            // Look-at rotation mode
        case GLFW_KEY_K:
            if (mods & GLFW_MOD_SHIFT)
                camera.rotateCameraAroundLookAt(-rotateSpeed * 0.001f * deltaTime);
            else
                camera.rotateCameraAroundLookAt(rotateSpeed * 0.001f * deltaTime);
            break;
        case GLFW_KEY_L:
            camera.stopLookAtRotation();
            break;
        }
    }

    void toggleFullscreen() {
        if (!fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            fullscreen = true;
        }
        else {
            glfwSetWindowMonitor(window, nullptr, 100, 100, SCR_WIDTH, SCR_HEIGHT, 0);
            fullscreen = false;
        }
    }

public:
    InputHandler(GLFWwindow* win, Camera& cam, BusModel& b, BusInterior& interior, float& wr, bool& si)
        : window(win), camera(cam), bus(b), interior(interior), wheelRotation(wr),
        showInterior(si), fullscreen(false), deltaTime(0.0f) {
        instance = this;
        glfwSetKeyCallback(window, keyCallbackStatic);
        glfwSetScrollCallback(window, scrollCallbackStatic);
    }

    ~InputHandler() {
        instance = nullptr;
    }

    void setDeltaTime(float dt) {
        deltaTime = dt;
    }

    void updateOrbitRotation() {
        if (camera.isOrbitMode()) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            int width, height;
            glfwGetWindowSize(window, &width, &height);

            camera.processOrbitRotation(static_cast<float>(xpos),
                static_cast<float>(ypos),
                static_cast<float>(width),
                static_cast<float>(height));
        }
    }

    void processContinuousInput() {
        float moveSpeed = 2.5f;
        float rotateSpeed = 45.0f;
        float busSpeed = 5.0f;
        float wheelSpeed = 200.0f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.moveForward(moveSpeed * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.moveBackward(moveSpeed * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.moveLeft(moveSpeed * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.moveRight(moveSpeed * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera.moveUp(moveSpeed * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.moveDown(moveSpeed * deltaTime);

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
                camera.rotatePitch(-rotateSpeed * deltaTime);
            else
                camera.rotatePitch(rotateSpeed * deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
                camera.rotateYaw(-rotateSpeed * deltaTime);
            else
                camera.rotateYaw(rotateSpeed * deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
                camera.rotateRoll(-rotateSpeed * deltaTime);
            else
                camera.rotateRoll(rotateSpeed * deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            bus.busPosition -= busSpeed * deltaTime;
            wheelRotation += wheelSpeed * deltaTime;
            if (wheelRotation >= 360.0f) wheelRotation -= 360.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            bus.busPosition += busSpeed * deltaTime;
            wheelRotation -= wheelSpeed * deltaTime;
            if (wheelRotation <= -360.0f) wheelRotation += 360.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            wheelRotation += wheelSpeed * deltaTime;
            if (wheelRotation >= 360.0f) wheelRotation -= 360.0f;
        }
        // Look-at rotation (continuous)
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
                camera.rotateCameraAroundLookAt(-rotateSpeed * deltaTime);
            else
                camera.rotateCameraAroundLookAt(rotateSpeed * deltaTime);
        }



    }
};

InputHandler* InputHandler::instance = nullptr;

// ==================== Main Function ====================
int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
        "ST Bus - Interior View",
        nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int width, int height) {
        glViewport(0, 0, width, height);
        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    ShaderProgram shader;
    if (!shader.create()) return -1;

    BusModel bus;
    bus.initialize();

    BusInterior interior;
    interior.initialize();

    Camera camera;
    float wheelRotation = 0.0f;
    bool showInterior = false;
    InputHandler input(window, camera, bus, interior, wheelRotation, showInterior);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Print controls
    std::cout << "\n=== ST BUS SIMULATOR WITH INTERIOR VIEW ===" << std::endl;
    std::cout << "\n*** Press M to toggle between ORBIT and FREE-FLIGHT modes ***" << std::endl;
    std::cout << "\n*** Press 3 for INTERIOR VIEW | Press 4 to return to exterior ***" << std::endl;
    std::cout << "*** Press 5 for DRIVER VIEW | Press 6 to return to normal mode ***" << std::endl;
    std::cout << "\nFREE-FLIGHT MODE (default)" << std::endl;
    std::cout << "Movement:" << std::endl;
    std::cout << "  W/S - Move Forward/Backward" << std::endl;
    std::cout << "  A/D - Move Left/Right" << std::endl;
    std::cout << "  E/Q - Move Up/Down" << std::endl;
    std::cout << "Rotation:" << std::endl;
    std::cout << "  X/Shift+X - Pitch (Look Up/Down)" << std::endl;
    std::cout << "  Y/Shift+Y - Yaw (Look Left/Right)" << std::endl;
    std::cout << "  Z/Shift+Z - Roll (Rotate Left/Right)" << std::endl;
    std::cout << "Zoom:" << std::endl;
    std::cout << "  Scroll - Zoom In/Out (FOV)" << std::endl;
    std::cout << "\nVIEW MODES:" << std::endl;
    std::cout << "  3 - Enter Interior View (rear of bus)" << std::endl;
    std::cout << "  4 - Exit Interior View (return to exterior)" << std::endl;
    std::cout << "  5 - Enter Driver View (behind driver seat)" << std::endl;
    std::cout << "  6 - Exit Driver View (return to normal mode)" << std::endl;
    std::cout << "\nDoor Controls:" << std::endl;
    std::cout << "  1 - Open Doors" << std::endl;
    std::cout << "  2 - Close Doors" << std::endl;
    std::cout << "\nOther Controls:" << std::endl;
    std::cout << "  K/Shift+K - Rotate Camera Around Look-at Point" << std::endl;
    std::cout << "  L - Stop Look-at Rotation" << std::endl;
    std::cout << "  B - Toggle Bird's Eye View" << std::endl;
    std::cout << "  I - Print Camera Info & FPS" << std::endl;
    std::cout << "  F/G - Move Bus Forward/Backward" << std::endl;
    std::cout << "  R - Rotate Wheels" << std::endl;
    std::cout << "  O - Toggle Lights" << std::endl;
    std::cout << "  F11 - Fullscreen" << std::endl;
    std::cout << "  ESC - Exit\n" << std::endl;

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        input.setDeltaTime(deltaTime);

        glClearColor(0.0f, 0.44f, 0.74f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input.processContinuousInput();
        input.updateOrbitRotation();
        bus.updateDoors();

        shader.use();
        camera.setUniforms(shader);

        bus.updateWheelRotation(wheelRotation);

        glm::mat4 baseModel = camera.getBaseModel(bus.busPosition);

        if (showInterior) {
            // Show interior view only
            interior.draw(shader, baseModel);
        }
        else {
            // Show exterior view
            bus.draw(shader, baseModel);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bus.cleanup();
    interior.cleanup();
    shader.cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}