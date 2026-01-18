<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>KUET Bus 3D Visualization</title>
    <style>
        body {
            font-family: Arial, Helvetica, sans-serif;
            line-height: 1.6;
            margin: 40px;
            background-color: #f9f9f9;
            color: #222;
        }
        h1, h2, h3 {
            color: #003366;
        }
        h1 {
            border-bottom: 3px solid #003366;
            padding-bottom: 10px;
        }
        hr {
            margin: 30px 0;
        }
        code {
            background: #eee;
            padding: 2px 6px;
            border-radius: 4px;
            font-family: Consolas, monospace;
        }
        ul {
            margin-left: 20px;
        }
        .note {
            background: #eef5ff;
            padding: 10px;
            border-left: 4px solid #003366;
            margin: 15px 0;
        }
    </style>
</head>

<body>

<h1>🚌 Khulna University of Engineering and Technology<br>
Bus 3D Visualization</h1>

<p>
A <strong>C++ / Modern OpenGL (3.3+)</strong> application that renders a detailed
<strong>3D bus model</strong> using <strong>GLM</strong>. This project demonstrates
procedural geometry, indexed & non-indexed rendering, shader management,
camera transformations, and interactive keyboard controls.
</p>

<hr>

<h2>✨ Features</h2>
<ul>
    <li>Composite 3D bus model built from cubes and cylinders</li>
    <li>Indexed rendering (EBO) for cubes and cylinders</li>
    <li>Procedural cylinder and wheel spoke generation</li>
    <li>Toggleable headlights and taillights</li>
    <li>Bus movement along X-axis with synchronized wheel rotation</li>
    <li>Multiple camera modes with perspective projection</li>
    <li>Interior, exterior, and driver view support</li>
</ul>

<hr>

<h2>🛠 Prerequisites</h2>
<ul>
    <li><strong>Operating System:</strong> Windows (tested), macOS/Linux (may work)</li>
    <li><strong>IDE:</strong> Visual Studio 2022 (recommended)</li>
    <li><strong>Graphics:</strong> OpenGL 3.3+ compatible GPU</li>
</ul>

<h3>📚 Libraries Used</h3>
<ul>
    <li><strong>GLAD</strong> – OpenGL function loader</li>
    <li><strong>GLFW</strong> – Window creation and input handling</li>
    <li><strong>GLM</strong> – Mathematics library</li>
</ul>

<p>Libraries can be installed using <strong>vcpkg</strong> or manually.</p>

<hr>

<h2>📁 Project Structure</h2>
<ul>
    <li><code>FileName.cpp</code> — Main application and input handling</li>
    <li><code>Class.h</code> — Geometry classes (Cube, Cylinder, WheelSpokes)</li>
    <li><code>BusModel.h</code> — Bus composition and rendering logic</li>
    <li><code>Camera.h</code> — Camera and projection utilities</li>
    <li><code>Shader.h</code> — Shader compilation and uniform helpers</li>
    <li><code>Vertices.h</code> — Geometry helper functions</li>
    <li><code>BusInterior.h</code> — Optional interior components</li>
    <li><code>vertex.glsl</code> — Vertex shader</li>
    <li><code>fragment.glsl</code> — Fragment shader</li>
    <li><code>README.md</code> — Project documentation</li>
</ul>

<div class="note">
    Adjust file names and paths according to your Visual Studio project setup.
</div>

<hr>

<h2>🎮 Controls</h2>

<h3>General</h3>
<ul>
    <li><strong>ESC</strong> — Exit application</li>
    <li><strong>F11</strong> — Toggle fullscreen mode</li>
</ul>

<h3>Bus Controls</h3>
<ul>
    <li><strong>F</strong> — Move bus forward (−X direction)</li>
    <li><strong>B</strong> — Move bus backward (+X direction)</li>
    <li><strong>R</strong> — Rotate wheels manually</li>
    <li><strong>O</strong> — Toggle headlights / taillights</li>
</ul>

<p><strong>Note:</strong> Wheel rotation automatically syncs with bus movement.</p>

<h3>Camera & Modes</h3>
<ul>
    <li><strong>L</strong> — Rotate camera slightly</li>
    <li><strong>M</strong> — Toggle ORBIT / FREE-FLIGHT mode</li>
</ul>

<hr>

<h2>🚀 FREE-FLIGHT Mode (Default)</h2>

<h3>Movement</h3>
<ul>
    <li><strong>W / S</strong> — Move Forward / Backward</li>
    <li><strong>A / D</strong> — Move Left / Right</li>
    <li><strong>E / Q</strong> — Move Up / Down</li>
</ul>

<h3>Rotation</h3>
<ul>
    <li><strong>X / Shift+X</strong> — Pitch (Look Up / Down)</li>
    <li><strong>Y / Shift+Y</strong> — Yaw (Look Left / Right)</li>
    <li><strong>Z / Shift+Z</strong> — Roll (Rotate Left / Right)</li>
</ul>

<h3>Zoom</h3>
<ul>
    <li><strong>Mouse Scroll</strong> — Zoom In / Out (FOV)</li>
</ul>

<hr>

<h2>👁 View Modes</h2>
<ul>
    <li><strong>3</strong> — Interior View (rear of bus)</li>
    <li><strong>4</strong> — Exit Interior View</li>
    <li><strong>5</strong> — Driver View</li>
    <li><strong>6</strong> — Exit Driver View</li>
</ul>

<hr>

<h2>🚪 Door Controls</h2>
<ul>
    <li><strong>1</strong> — Open doors</li>
    <li><strong>2</strong> — Close doors</li>
</ul>

<hr>

<h2>📌 Summary</h2>
<p>
This project demonstrates key <strong>modern OpenGL concepts</strong> including
hierarchical modeling, procedural geometry, camera systems, and real-time
interaction. It is suitable for graphics coursework, lab assignments, and
OpenGL learning projects.
</p>

<p><strong>Developed for KUET – CSE OpenGL / Graphics Lab</strong></p>

</body>
</html>
