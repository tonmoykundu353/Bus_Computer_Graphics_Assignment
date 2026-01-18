[Bus_Assignment-cropped.pdf](https://github.com/user-attachments/files/24697239/Bus_Assignment-cropped.pdf)



# Khulna University of Engineering and Technology Bus 3D Visualization

A C++/OpenGL application that renders a detailed 3D bus model using modern OpenGL (3.3+) and GLM. The project demonstrates procedural geometry, indexed and non-indexed meshes, shader management, camera transforms, and keyboard controls.

## Features

- Composite bus model assembled from cubes and cylinders
- Indexed rendering (EBO) for cubes and cylinders
- Procedural cylinder and wheel spoke generation
- Toggleable headlights/taillights
- Bus movement along the X-axis with wheel rotation synchronization
- Camera rotation and perspective projection

---

## Prerequisites

- Development OS: Windows (tested), macOS/Linux may work with minor adjustments
- Visual Studio 2022 recommended (MSVC)
- OpenGL 3.3+ capable GPU

### Libraries Used

- **GLAD**: OpenGL loader
- **GLFW**: Windowing and input management
- **GLM**: Mathematics library

Libraries can be installed via vcpkg or manually.

---

## Project Structure

Files you'll typically work with:

- `FileName.cpp`    — Application entry point, main loop, input handling
- `Class.h`        — `Cube`, `Cylinder`, `WheelSpokes` classes (geometry)
- `BusModel.h`     — Bus composition and high-level rendering logic
- `Camera.h`       — View/projection utilities
- `Shader.h`       — Shader loading/compilation/uniform helpers
- `Vertices.h`     — Helper geometry functions
- `BusInterior.h`  — Optional interior components
- `vertex.glsl`    — Vertex shader source
- `fragment.glsl`  — Fragment shader source
- `README.md`      — This file

Adjust names/locations in your Visual Studio project as needed.

---


## Controls

- `ESC`  — Exit application
- `L`    — Rotate camera (small step)
- `F`    — Move bus forward (negative X direction)
- `B`    — Move bus backward (positive X direction)
- `R`    — Rotate wheels (manual increment)
- `O`    — Toggle headlights/taillights
- `F11`  — Toggle fullscreen mode

**Behavior note**: `F` moves the bus along negative X (forward in scene), `B` moves it along positive X (backward). Wheel rotation is updated to match movement direction when pressing these keys.

*** Press M to toggle between ORBIT and FREE-FLIGHT modes ***

*** Press 3 for INTERIOR VIEW | Press 4 to return to exterior ***
*** Press 5 for DRIVER VIEW | Press 6 to return to normal mode ***

FREE-FLIGHT MODE (default)
Movement:
  W/S - Move Forward/Backward
  A/D - Move Left/Right
  E/Q - Move Up/Down
Rotation:
  X/Shift+X - Pitch (Look Up/Down)
  Y/Shift+Y - Yaw (Look Left/Right)
  Z/Shift+Z - Roll (Rotate Left/Right)
Zoom:
  Scroll - Zoom In/Out (FOV)

VIEW MODES:
  3 - Enter Interior View (rear of bus)
  4 - Exit Interior View (return to exterior)
  5 - Enter Driver View (behind driver seat)
  6 - Exit Driver View (return to normal mode)

Door Controls:
  1 - Open Doors
  2 - Close Doors
