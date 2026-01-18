<img width="799" height="635" alt="Screenshot 2026-01-18 220017" src="https://github.com/user-attachments/assets/b031ef1e-fb8e-4208-94db-9cc7a7663c6a" />
<img width="795" height="635" alt="Screenshot 2026-01-18 215942" src="https://github.com/user-attachments/assets/e83e207f-c99e-494a-9e72-eb36520be90f" />
<img width="796" height="630" alt="Screenshot 2026-01-18 215859" src="https://github.com/user-attachments/assets/72bac076-bb58-4cfa-8a7e-11c14ad5af4c" />
<img width="796" height="631" alt="Screenshot 2026-01-18 215831" src="https://github.com/user-attachments/assets/d25a4a97-babb-4e3c-83d6-c82ecf4009f7" />
<img width="798" height="634" alt="Screenshot 2026-01-18 215741" src="https://github.com/user-attachments/assets/b6c13a51-3275-4c54-b78f-4fec7f2cac1d" />
<img width="797" height="631" alt="Screenshot 2026-01-18 215717" src="https://github.com/user-attachments/assets/feb5a5f0-5417-4fc0-bc2c-d18087ba84b3" />
<img width="798" height="631" alt="Screenshot 2026-01-18 221054" src="https://github.com/user-attachments/assets/f966e31e-f2f0-4d01-a779-cd84a61d46ca" />
<img width="794" height="632" alt="Screenshot 2026-01-18 221012" src="https://github.com/user-attachments/assets/191f9e7d-cc81-41ee-9d26-482e151e3aea" />
<img width="797" height="636" alt="Screenshot 2026-01-18 220654" src="https://github.com/user-attachments/assets/e57f9ec0-1c2e-45aa-88ef-a5ca670b4fb3" />
<img width="797" height="628" alt="Screenshot 2026-01-18 220641" src="https://github.com/user-attachments/assets/1401ea59-97d0-4a1e-a6b8-4139a0bf3e81" />
<img width="795" height="641" alt="Screenshot 2026-01-18 220318" src="https://github.com/user-attachments/assets/e2ce4365-09f1-49ef-ac57-97ec135df4c8" />
<img width="792" height="632" alt="Screenshot 2026-01-18 220158" src="https://github.com/user-attachments/assets/7a431815-2393-4e56-a630-8c2319ec7c5e" />
<img width="793" height="638" alt="Screenshot 2026-01-18 220121" src="https://github.com/user-attachments/assets/8a51bceb-1b47-4915-bdac-cbfaf8570459" />
<img width="796" height="636" alt="Screenshot 2026-01-18 220045" src="https://github.com/user-attachments/assets/5d8d66e6-cad1-418e-9f08-4ec6afc96b02" />


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
