# 🌲 Floating Forest 3D

A 3D graphics project made in C++ with OpenGL and the [CGP library](https://github.com/drohmer/cgp).  
Explore a mysterious floating island, remnants of a catastrophic event. The forest may appear beautiful - but it can also be deadly.  
Animated snakes, flying mosquitoes, procedural terrain, and shader-powered vegetation create an immersive 3D world.

---

## 📁 Project Structure

```
/floating-forest-3D/
├── Project/
│   ├── assets/               # Textures, models, and other visual resources
│   ├── includes/             # Header files for scene objects and utilities
│   ├── shaders/              # Custom GLSL shaders (animated grass, trees, snakes, etc.)
│   ├── scripts/              # Utility scripts if any (e.g. for asset processing)
│   ├── src/                  # Main C++ source files (object creation, animation, logic)
│   │   ├── main.cpp          # Entry point of the application
│   │   ├── *.cpp / *.hpp     # Object-specific logic (tree, snake, mosquito, etc.)
│   ├── build/                # Build output folder (excluded from git)
│   ├── cmake-build-debug/    # VS Code / CLion specific CMake output
│   ├── CMakeLists.txt        # CMake build configuration
│   ├── Makefile              # Optional manual build script
│   ├── .vscode/              # VS Code configuration files
├── cgp/                      # External CGP library by Damien Rohmer (submodule or copy)
├── .gitignore
├── README.md
```

---

## 🛠 How to Build & Run

Make sure you have **CMake** (≥3.12) and a compiler with **C++17** support. The CGP library should be placed under `cgp/`, or properly linked in your CMake config.

```bash
# Clone the repository
git clone git@github.com:akochergina/floating-forest-3D.git
cd floating-forest-3D

# Create a build directory
mkdir build
cd build

# Generate build files with CMake
cmake ../Project

# Compile the project
make

# Run the executable
./main
```

> ✅ If you use **VS Code**, simply open the workspace and use the CMake Tools extension to configure and run the project.
