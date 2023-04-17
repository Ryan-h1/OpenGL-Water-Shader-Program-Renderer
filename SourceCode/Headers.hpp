/**
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
 * @file Headers.hpp
 *
 * @author Ryan Hecht
 *
 * @brief This file includes all the required headers and libraries for the program.
 *
 */


#ifndef HEADERS_HPP
#define HEADERS_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <vector>

#include "Constants.hpp"
#include "LoadBMP.hpp"
#include "PlaneMesh.hpp"
#include "CamControls.hpp"

#endif