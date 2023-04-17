/***
 * Ryan Hecht
 * Professor Brandt
 * CS 3388 Computer Graphics I
 * Due Date: 10 April 2023
 * 
 * Created: 6 April 2023
 * Last Edited: 8 April 2023
 * 
 * Assignment 6
 * 
 * @file Shader.hpp
 * 
 * @author Ryan Hecht
 * 
 * @brief Utility header file for loading and compiling the vertex, tessellation control,
 * tessellation evaluation, geometry, and fragment shaders for the program.
 * 
 */
#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <GL/glew.h>

#include <stdlib.h>
#include <string.h>


/***
 * 
 * @brief Takes file paths for five different shaders (vertex, tessellation control,
 * tessellation evaluation, geometry, and fragment shaders) as input arguments,
 * compiles them, and links them into a single shader program.
 *
 * @param vertex_file_path: The file path of the vertex shader.
 * @param tessellation_control_file_path: The file path of the tessellation control shader.
 * @param tessellation_evaluation_file_path: The file path of the tessellation evaluation shader.
 * @param geo_file_path: The file path of the geometry shader.
 * @param fragment_file_path: The file path of the fragment shader.
 * @return: The shader program's ID.
 */
GLuint LoadShaders(const char * vertex_file_path, const char * tessellation_control_file_path, const char * tessellation_evaluation_file_path, const char * geo_file_path, const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint TessellationControlShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
    GLuint TessellationEvaluationShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
    GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Init shader code to be read
    std::string VertexShaderCode, TessellationControlShaderCode, TessellationEvaluationShaderCode, GeometryShaderCode, FragmentShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    std::ifstream TessellationControlShaderStream(tessellation_control_file_path, std::ios::in);
    std::ifstream TessellationEvaluationShaderStream(tessellation_evaluation_file_path, std::ios::in);
    std::ifstream GeometryShaderStream(geo_file_path, std::ios::in);
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

    // Read function
    auto readShaderCode = [](std::ifstream &shaderStream, std::string &shaderCode, const char *file_path) {
        if (shaderStream.is_open()) {
            std::stringstream sstr;
            sstr << shaderStream.rdbuf();
            shaderCode = sstr.str();
            shaderStream.close();
        } else {
            printf("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ!\n", file_path);
            getchar();
            return 0;
        }
        return 1;
    };

    // Read shader code from files
    readShaderCode(VertexShaderStream, VertexShaderCode, vertex_file_path);
    readShaderCode(TessellationControlShaderStream, TessellationControlShaderCode, tessellation_control_file_path);
    readShaderCode(TessellationEvaluationShaderStream, TessellationEvaluationShaderCode, tessellation_evaluation_file_path);
    readShaderCode(GeometryShaderStream, GeometryShaderCode, geo_file_path);
    readShaderCode(FragmentShaderStream, FragmentShaderCode, fragment_file_path);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile shader function
    auto compileShader = [](GLuint shaderID, const char *source, const char *file_path) {
        printf("Compiling shader: %s\n", file_path);
        glShaderSource(shaderID, 1, &source, NULL);
        glCompileShader(shaderID);
    };

    // Check shader for errors function
    auto checkShader = [](GLuint shaderID) {
        GLint Result, InfoLogLength;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ErrorMessage[0]);
            printf("%s\n", &ErrorMessage[0]);
        }
    };

    // Compile and check shaders
    compileShader(VertexShaderID, VertexShaderCode.c_str(), vertex_file_path);
    checkShader(VertexShaderID);

    compileShader(TessellationControlShaderID, TessellationControlShaderCode.c_str(), tessellation_control_file_path);
    checkShader(TessellationControlShaderID);

    compileShader(TessellationEvaluationShaderID, TessellationEvaluationShaderCode.c_str(), tessellation_evaluation_file_path);
    checkShader(TessellationEvaluationShaderID);

    compileShader(GeometryShaderID, GeometryShaderCode.c_str(), geo_file_path);
    checkShader(GeometryShaderID);

    compileShader(FragmentShaderID, FragmentShaderCode.c_str(), fragment_file_path);
    checkShader(FragmentShaderID);

    // Link program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, TessellationControlShaderID);
    glAttachShader(ProgramID, TessellationEvaluationShaderID);
    glAttachShader(ProgramID, GeometryShaderID);
    glAttachShader(ProgramID, FragmentShaderID);

    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    // Detach shaders
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, TessellationControlShaderID);
    glDetachShader(ProgramID, TessellationEvaluationShaderID);
    glDetachShader(ProgramID, GeometryShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    // Delete shaders
    glDeleteShader(VertexShaderID);
    glDeleteShader(TessellationControlShaderID);
    glDeleteShader(TessellationEvaluationShaderID);
    glDeleteShader(GeometryShaderID);
    glDeleteShader(FragmentShaderID);

    // Return completed shader program
    return ProgramID;

}

#endif