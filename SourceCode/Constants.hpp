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
 * @file Constants.hpp
 * 
 * @author Ryan Hecht
 * 
 * @brief This file contains constant values used throughout this program.
 * 
 * The constants defined in this file include values related to the plane mesh, such as
 * moving texture modifiers, tessellation values, displacement modifiers, and graphical
 * constants. These values are used to control the appearance and behavior of the rendered
 * water patch.
 * 
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// ========================================
// Plane Mesh Constants
// ========================================

// Moving Texture modifiers
const float TEX_OFFSET = 0.0; // Offset of the water texture on the plane
const float TEX_SCALE = 5.0; // Scale of the water texture; higher means a more zoomed in texture, too low can result in tiling

// Tessellation values
const float OUTER_TESS = 15.0;
const float INNER_TESS = 15.0;

// Displacement modifers
const float DISPLACEMENT_HEIGHT = 0.4; // Higher value => Taller displacement height
const float DISPLACEMENT_CLOSENESS = 0.05; // Lower value => Displacement map becomes effectively wider and more spread out

// Graphical constants
const float SHININESS = 64.0;

// ========================================
// 
// ========================================


#endif // CONSTANTS_HPP