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
 * @file PlaneMesh.hpp
 * 
 * @author Ryan Hecht
 * 
 * @brief This file defines the PlaneMesh class, which is responsible for creating,
 *        rendering, and updating a tessellated water patch with displacement mapping
 *        in the program.
 * 
 * This class uses the constants defined in the
 * Constants.hpp file for configuring the appearance and behavior of the rendered
 * water patch.
 * 
 */

#ifndef PLANEMESH_HPP
#define PLANEMESH_HPP


#include "Shader.hpp"

class PlaneMesh {
	
	std::vector<float> verts;
	std::vector<int> indices;

	float min, max;

	GLuint vertexbuffer, elementbuffer;
	GLuint TextureID, DispID;
	GLuint ProgramID;


	/**
	 * @brief Generates the vertex and index data for the plane mesh using quads.
	 * 
	 * @param min The minimum coordinate value for the x and z axes.
	 * @param max The maximum coordinate value for the x and z axes.
	 * @param stepsize The distance between adjacent vertices in the mesh.
	 */
	void planeMeshQuads(float min, float max, float stepsize) {

		// The following coordinate system works as if (min, 0, min) is the origin
		// And then builds up the mesh from that origin down (in z)
		// and then to the right (in x).
		// So, one "row" of the mesh's vertices have a fixed x and increasing z

		//manually create a first column of vertices
		float x = min;
		float y = 0;
        int nCols = (max - min) / stepsize + 1;

        for (float x = min; x <= max; x += stepsize) {
            for (float z = min; z <= max; z += stepsize) {
                verts.push_back(x);
                verts.push_back(0);
                verts.push_back(z);
            }
        }

		// Quad indices
        for (int i = 0; i < nCols - 1; ++i) {
            for (int j = 0; j < nCols - 1; ++j) {
                int topLeft = i * nCols + j;
                int bottomLeft = (i + 1) * nCols + j;
                int topRight = i * nCols + j + 1;
                int bottomRight = (i + 1) * nCols + j + 1;

                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
                indices.push_back(topRight);
            }
        }
    }

public:


	/**
	 * @brief Constructs a PlaneMesh object, generating the plane mesh, loading shaders
	 *        and textures, and setting up OpenGL buffers.
	 * 
	 * @param min The minimum coordinate value for the x and z axes.
	 * @param max The maximum coordinate value for the x and z axes.
	 * @param stepsize The distance between adjacent vertices in the mesh.
	 */
	PlaneMesh(float min, float max, float stepsize) {
		this->min = min;
		this->max = max;

		planeMeshQuads(min, max, stepsize);
		
		// Load shaders
		ProgramID = LoadShaders("../Shaders/WaterShader.vertexshader", 
			"../Shaders/WaterShader.tcs", 
			"../Shaders/WaterShader.tes", 
			"../Shaders/WaterShader.geoshader", 
			"../Shaders/WaterShader.fragmentshader");

		// Load texture
		unsigned char* texture_data;
		unsigned int texture_width, texture_height;
		loadBMP("../Assets/water.bmp", &texture_data, &texture_width, &texture_height);

		// Create texture
		glGenTextures(1, &TextureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Load displacement map
		unsigned char* disp_data;
		unsigned int disp_width, disp_height;
		loadBMP("../Assets/water.bmp", &disp_data, &disp_width, &disp_height);

		// Create displacement map
		glGenTextures(1, &DispID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, DispID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, disp_width, disp_height, 0, GL_BGR, GL_UNSIGNED_BYTE, disp_data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		

		// Set constant uniforms
		glUseProgram(ProgramID);

		glUniform1i(glGetUniformLocation(ProgramID, "tex"), 0);
		glUniform1i(glGetUniformLocation(ProgramID, "heighTex"), 1);

        auto setUniform1f = [&](const char* name, float value) {
            GLuint uniformID = glGetUniformLocation(ProgramID, name);
			glUniform1f(uniformID, value);
    	};

		setUniform1f("texOffset", TEX_OFFSET);
		setUniform1f("texScale", TEX_SCALE);
		setUniform1f("displacementHeight", DISPLACEMENT_HEIGHT);
		setUniform1f("displacementCloseness", DISPLACEMENT_CLOSENESS);
		setUniform1f("outerTess", OUTER_TESS);
		setUniform1f("innerTess", INNER_TESS);
		setUniform1f("alpha", SHININESS);

		glUseProgram(0);

		// Generate buffers
		glGenBuffers(1, &vertexbuffer);
		glGenBuffers(1, &elementbuffer);

		// Fill buffers
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
	}


	/**
	 * @brief Renders the plane mesh using the shader program.
	 * 
	 * @param lightPos The position of the light source in world space.
	 * @param V The view matrix for the scene.
	 * @param P The projection matrix for the scene.
	 */
	void draw(glm::vec3 lightPos, glm::mat4 V, glm::mat4 P) {
		
		glUseProgram(ProgramID);

		glm::mat4 M = glm::mat4(1.0f);
		glm::mat4 MVP = P * V * M;

		// Set new uniforms
		GLuint MatrixID = glGetUniformLocation(ProgramID, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		GLuint ViewMatrixID = glGetUniformLocation(ProgramID, "V");
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &V[0][0]);
		
		GLuint ModelMatrixID = glGetUniformLocation(ProgramID, "M");
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

		GLuint LightID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
		
		GLuint timeID = glGetUniformLocation(ProgramID, "time");
		glUniform1f(timeID, glfwGetTime());

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Activate textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, DispID);

		// Set the patch size
		glPatchParameteri(GL_PATCH_VERTICES, 4);

		// Draw the patches
		glDrawElements(GL_PATCHES, indices.size(), GL_UNSIGNED_INT, (void*)0);

		// Deactivate textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Disable the vertex attribute arrays
		glDisableVertexAttribArray(0);

		glUseProgram(0);

	}

};

#endif
