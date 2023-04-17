# OpenGL-Water-Shader-Program-Renderer
This is a repository for a C++ OpenGL application I made for my CS 3388 Computer Graphics I class at Western University. It constitutes my work for the sixth assignment.

## Assignment 6 Header

Ryan Hecht

Professor Brandt

CS 3388 Computer Graphics I

Due Date: 10 April 2023

Created: 6 April 2023

Last Edited: 8 April 2023

Assignment 6

## Description

    This OpenGL C++ program renders a patch of water from a plane mesh using a shader 
    program with tessellation and geometry shaders. The program leverages the GLEW 
    (OpenGL Extension Wrangler Library) to manage OpenGL extensions and the GLM 
    (OpenGL Mathematics) library for mathematical operations. The rendered water 
    patch is created by generating a quad grid of vertices, which is then tessellated 
    and transformed by the shader program.

## Requirements

    1. C++ Standard Library
    2. OpenGL
    3. GLEW (OpenGL Extension Wrangler Library)
    4. GLFW (OpenGL Graphics Library Framework)
    5. GLM (OpenGL Mathematics)
    6. Support for GLSL 4.50.

## Known Bugs and Idiosyncrasies

    Note that high step sizes and tessellation levels can cause unexpected
    behaviour with the number of vertices generated. Also, the tessellation level
    is currently set to 15.0 because a higher level causes instability with my
    personal machine. I can run 16.0 only if I increase the step size to 1.2 or more.
    You can change the tessellation level to 16.0 by going into the Constants.hpp
    and changing it there.

## Program Structure

### "ExampleScreenshots" Folder
    Contains screenshots of the rendered waves

### "Assets" Folder
    Contains the water.bmp texture and displacement-map1.bmp displacement map used
    for rendering the water.

### "Shaders" Folder
    Contains the Phong-like shaders, geoshader, and tesselation shaders used in 
    the shader program.

### "SourceCode" Folder
    Headers.hpp: Central header file including:
    Constants.hpp: General constants used throughout the program
    CameraControls.hpp: Manages camera controls
    Shader.hpp: Shader loading and management functions
    LoadBMP.hpp: Loads BMP files
    PlaneMesh.hpp: Class definition for the PlaneMesh that is transformed into water

## How to Run the Program

    Compile the program using the provided makefile (if using Ubuntu 22.04.2) with the 
    appropriate libraries on your system. Use your own form of compilation if using an
    alternative operating system. Provide command line arguments for the
    screen width, screen height, stepsize, xmin, xmax.

    For Example: './assign6 1920 1080 1.0 -10 10'

    1920 x 1080 pixel window, a step size of 1.0, and with a plane mesh 
    from -10 to 10 (standard size).

## A Note on Compatibility

    This program uses the standard dev tools from the OpenGL library. It also uses GLEW and GLM. 
    This program was made on Ubuntu 22.04.2, with an Intel CPU and Nvidia GPU. Please note 
    there may be compatibility issues with different operating systems and hardware, 
    particularly Apple Silicone and Intel GPUs. There may also be compatibility issues 
    with high retina displays.

## Acknowledgments
    
    This program was completed as an assignment for CS 3388 Computer Graphics I at 
    Western University and uses some files provided by Professor Alexandar Brandt, such
    as CamControls.hpp and LoadBMP.hpp.

## Example Screenshots
![Alt text](/ExampleScreenshots/wavess1.png?raw=true "Waves")

![Alt text](/ExampleScreenshots/wavess2.png?raw=true "Waves")

![Alt text](/ExampleScreenshots/wavess3.png?raw=true "Waves")
