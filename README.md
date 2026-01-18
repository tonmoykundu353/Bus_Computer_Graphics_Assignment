<h1>🚌 Khulna University of Engineering and Technology<br>
Bus 3D Visualization</h1>

<p>
A <strong>C++ / Modern OpenGL (3.3+)</strong> application that renders a detailed
<strong>3D bus model</strong> using <strong>GLM</strong>. This project demonstrates
procedural geometry, indexed & non-indexed rendering, shader management,
camera transformations, and interactive keyboard controls.
</p>

<img width="792" height="632" alt="Screenshot 2026-01-18 220158" src="https://github.com/user-attachments/assets/5a90adc9-2d92-4dbc-826b-e7d12a84913c" />
<img width="793" height="638" alt="Screenshot 2026-01-18 220121" src="https://github.com/user-attachments/assets/d5b1b672-75c8-45cc-aef2-50e17f7ef8d4" />
<img width="796" height="636" alt="Screenshot 2026-01-18 220045" src="https://github.com/user-attachments/assets/eefde1e7-a9aa-454a-a850-880f8eabca00" />
<img width="799" height="635" alt="Screenshot 2026-01-18 220017" src="https://github.com/user-attachments/assets/235a96c7-5d3a-417e-914e-e39c7ebdbb0f" />
<img width="795" height="635" alt="Screenshot 2026-01-18 215942" src="https://github.com/user-attachments/assets/c15431af-c20c-4dd2-b364-5dab52880fea" />
<img width="796" height="630" alt="Screenshot 2026-01-18 215859" src="https://github.com/user-attachments/assets/b44bfd00-56da-4905-93df-ed7b1b5f7792" />
<img width="796" height="631" alt="Screenshot 2026-01-18 215831" src="https://github.com/user-attachments/assets/08d48653-6f7d-4ea4-ac54-d45e55ef55aa" />
<img width="798" height="634" alt="Screenshot 2026-01-18 215741" src="https://github.com/user-attachments/assets/c904b4f5-2486-42ff-af04-8057c1dbfc1d" />
<img width="797" height="631" alt="Screenshot 2026-01-18 215717" src="https://github.com/user-attachments/assets/f2c07917-3942-4166-aff7-f72ff729bc20" />
<img width="798" height="631" alt="Screenshot 2026-01-18 221054" src="https://github.com/user-attachments/assets/4450ced3-99c9-4f34-8489-7278b065f9d9" />
<img width="794" height="632" alt="Screenshot 2026-01-18 221012" src="https://github.com/user-attachments/assets/60bbcb50-a56a-4200-a9c8-a178d1a34470" />
<img width="797" height="636" alt="Screenshot 2026-01-18 220654" src="https://github.com/user-attachments/assets/079f8860-e9ea-46d8-9355-51d6f02c2163" />
<img width="797" height="628" alt="Screenshot 2026-01-18 220641" src="https://github.com/user-attachments/assets/507382b7-ec51-48b0-b823-a66fe00e4103" />
<img width="795" height="641" alt="Screenshot 2026-01-18 220318" src="https://github.com/user-attachments/assets/dab469b0-624a-4682-8a24-8ec876fdd164" />


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
