# Release Build Instructions

This document explains how to create a distributable release build of the Asteroids game.

## Prerequisites

- CMake installed
- Visual Studio 2022 (or compatible C++ compiler)
- vcpkg configured with SFML installed

## Steps to Build Release Version

### 1. Navigate to Build Directory

```powershell
cd e:\opengl\asteroids_sfml\build
```

### 2. Reconfigure CMake (if needed)

If you made changes to CMakeLists.txt or it's your first time building:

```powershell
cmake ..
```

### 3. Build Release Configuration

```powershell
cmake --build . --config Release
```

This will:
- Compile the game with optimizations enabled
- Create `Asteroids.exe` in `build\Release\`
- Automatically copy the `assets` folder to `build\Release\assets\`
- Copy all required SFML DLLs to `build\Release\`

### 4. Create Distribution Package

```powershell
cd e:\opengl\asteroids_sfml

# Remove old release folder if it exists
if (Test-Path "Asteroids_Release") { Remove-Item -Recurse -Force "Asteroids_Release" }

# Create new release folder
New-Item -ItemType Directory -Path "Asteroids_Release"

# Copy all release files
Copy-Item "build\Release\*" -Destination "Asteroids_Release\" -Recurse
```

### 5. Verify the Build

Test the release build:

```powershell
cd Asteroids_Release
.\Asteroids.exe
```

### 6. Package for Distribution

The `Asteroids_Release` folder now contains everything needed:
- `Asteroids.exe` - The game executable
- `assets/` - All fonts and sounds
- All required DLL files

**To distribute:**
1. Zip the entire `Asteroids_Release` folder
2. Share the zip file
3. Users simply extract and run `Asteroids.exe`

## Quick Release Script

You can run all steps at once:

```powershell
cd e:\opengl\asteroids_sfml\build
cmake ..
cmake --build . --config Release
cd ..
if (Test-Path "Asteroids_Release") { Remove-Item -Recurse -Force "Asteroids_Release" }
New-Item -ItemType Directory -Path "Asteroids_Release"
Copy-Item "build\Release\*" -Destination "Asteroids_Release\" -Recurse
```

## Troubleshooting

### Assets Not Found
If the game can't find assets, make sure:
- The `assets` folder is in the same directory as `Asteroids.exe`
- CMake's post-build command ran successfully (check CMakeLists.txt)

### Missing DLLs
If DLLs are missing:
- Rebuild with `cmake --build . --config Release` 
- vcpkg should automatically copy DLLs to the output directory

### Build Fails
- Ensure vcpkg is properly configured
- Run `cmake ..` again to reconfigure
- Check that all dependencies are installed via vcpkg

## File Structure

After building, your release should look like this:

```
Asteroids_Release/
├── Asteroids.exe
├── assets/
│   ├── fonts/
│   │   └── arial.ttf
│   └── sounds/
│       └── shoot.mp3
├── sfml-graphics-3.dll
├── sfml-audio-3.dll
├── sfml-system-3.dll
├── sfml-window-3.dll
└── [other dependency DLLs]
```
