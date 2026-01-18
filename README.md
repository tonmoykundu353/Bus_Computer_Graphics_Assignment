[Bus_Assignment-cropped.pdf](https://github.com/user-attachments/files/24697239/Bus_Assignment-<img width="792" height="632" alt="Screenshot 2026-01-18 220158" src="https://github.com/user-attachments/assets/9e87c9ad-5208-452c-9d12-b8029d66840d" />
<img width="793" height="638" alt="Screenshot 2026-01-18 220121" src="https://github.com/user-attachments/assets/b6bcf1cd-b2e3-4f53-a02a-99befdba893e" />
<img width="796" height="636" alt="Screenshot 2026-01-18 220045" src="https://github.com/user-attachments/assets/d0559743-c4fb-4143-9156-f883dfad18cc" />
<img width="799" height="635" alt="Screenshot 2026-01-18 220017" src="https://github.com/user-attachments/assets/006f06c2-217a-46ff-83e0-bd22528f398b" />
<img width="795" height="635" alt="Screenshot 2026-01-18 215942" src="https://github.com/user-attachments/assets/99c2dc09-1b94-4b11-9adf-b379892bda74" />
<img width="796" height="630" alt="Screenshot 2026-01-18 215859" src="https://github.com/user-attachments/assets/0f7c7115-6508-46af-bb55-f88ad7671f33" />
<img width="796" height="631" alt="Screenshot 2026-01-18 215831" src="https://github.com/user-attachments/assets/db9dc070-e447-4ee6-87c3-9594aa51505a" />
<img width="798" height="634" alt="Screenshot 2026-01-18 215741" src="https://github.com/user-attachments/assets/91e44a9d-b499-42e4-8572-381759f59bd3" />
<img width="797" height="631" alt="Screenshot 2026-01-18 215717" src="https://github.com/user-attachments/assets/6d5c0c42-9ad0-4dd5-a7fa-a87fbf134d8d" />
<img width="798" height="631" alt="Screenshot 2026-01-18 221054" src="https://github.com/user-attachments/assets/277132cc-dc12-4998-9ff1-a04358f76517" />
<img width="794" height="632" alt="Screenshot 2026-01-18 221012" src="https://github.com/user-attachments/assets/c334dada-018c-49b6-9cbf-aad227456cad" />
<img width="797" height="636" alt="Screenshot 2026-01-18 220654" src="https://github.com/user-attachments/assets/5bf0672d-c631-467c-9ca8-798b71a91ede" />
<img width="797" height="628" alt="Screenshot 2026-01-18 220641" src="https://github.com/user-attachments/assets/33a86ecf-44ed-4fed-baed-d8415815cd55" />
<img width="795" height="641" alt="Screenshot 2026-01-18 220318" src="https://github.com/user-attachments/assets/55911ed7-0480-4b34-9e84-bfb9e8ceb559" />
cropped.pdf)



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
