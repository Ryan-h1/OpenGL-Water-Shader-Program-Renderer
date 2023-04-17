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
 * @file main.cpp
 * 
 * @author Ryan Hecht
 * 
 * @brief OpenGL C++ program that renders a patch of water from a plane mesh using a shader 
 * program with tessellation and geometry shaders. The program leverages the GLEW (OpenGL
 * Extension Wrangler Library) to manage OpenGL extensions and the GLM (OpenGL Mathematics)
 * library for mathematical operations. The rendered water patch is created by generating
 * a quad grid of vertices, which is then tessellated and transformed by the shader program.
 * 
 * @note How to Run
 * To run the program, run the make file by typing make (if using Ubuntu 22.04.2) or compile 
 * it with the appropriate libraries if on a different system, and provide command line arguments
 * for screen width, screen height, stepsize, xmin, xmax.
 * For example: ./assign6 1920 1080 1.0 -10 10
 * Will run the program with 1920 x 1080 pixel window, step size of 1.0, and with a planemesh
 * from -10 to 10 - standard size.
 * 
 * @note Constants
 * Constants affecting tessellation levels and the appearance of the water can be changed in
 * Constants.hpp
 * 
 * @note Camera Controls
 * The camera can be controlled using the mouse and arrow keys to change the view of the scene.
 * Click and drag to rotate the scene, use the up and down arrow keys to zoom in and out.
 */


#include "Headers.hpp"


//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{

	///////////////////////////////////////////////////////
	float screenW = 1000;
	float screenH = 1000;
	float stepsize = 1.0f;

	float xmin = -10;
	float xmax = 10;

	if (argc > 1 ) {
		screenW = atoi(argv[1]);
	}
	if (argc > 2) {
		screenH = atoi(argv[2]);
	}
	if (argc > 3) {
		stepsize = atof(argv[3]);
	}
	if (argc > 4) {
		xmin = atof(argv[4]);
	}
	if (argc > 5) {
		xmax = atof(argv[5]);
	}


	///////////////////////////////////////////////////////

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( screenW, screenH, "Ryan Hecht Assignment 6", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	

	PlaneMesh plane(xmin, xmax, stepsize);
	
	//TexturedMesh boat("Assets/boat.ply", "Assets/boat.bmp");
	//TextureMesh head("Assets/head.ply", "Assets/head.bmp", 1);
	//TextureMesh eyes("Assets/eyes.ply", "Assets/eyes.bmp", 1);


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glDisable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// Projection = glm::mat4(1.0f);
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);
	glLoadMatrixf(glm::value_ptr(Projection));

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glm::vec3 eye = {0.0f, 5.0f, 8.0f};
	// glm::vec3 eye = {-5.0f, 2.0f, -5.0f};
	glm::vec3 up = {0.0f, 1.0f, 0.0f};
	glm::vec3 center = {0.0f, 0.0f, 0.0f};
	//glm::mat4 V;

	glm::mat4 V = glm::lookAt(eye, center, up);
	glLoadMatrixf(glm::value_ptr(V));

	glm::vec3 lightpos(5.0f, 30.0f, 5.0f);
	glm::vec4 color1(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cameraControlsGlobe(V, 5);
		
		plane.draw(lightpos, V, Projection);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

