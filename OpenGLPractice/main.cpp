
//Include GLEW  
#include <GL/glew.h>  
  
//Include GLFW  
#include <GLFW/glfw3.h>  
  
//Include the standard C++ headers  
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>

#include "branch.h"
#include "tree.h"
#include <ctime>

#include <math.h>
#include <GL/glut.h>

GLFWwindow* window;

int drawTrees();
void glTest();


float gwindow;
float t = 0.0f;


void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric)
{
   float vx = x2-x1;
   float vy = y2-y1;
   float vz = z2-z1;

   //handle the degenerate case of z1 == z2 with an approximation
   if(vz == 0)
       vz = .00000001;

   float v = sqrt( vx*vx + vy*vy + vz*vz );
   float ax = 57.2957795*acos( vz/v );
   if ( vz < 0.0 )
       ax = -ax;
   float rx = -vy*vz;
   float ry = vx*vz;
   glPushMatrix();

   //draw the cylinder body
   glTranslatef( x1,y1,z1 );
   glRotatef(ax, rx, ry, 0.0);
   gluQuadricOrientation(quadric,GLU_OUTSIDE);
   gluCylinder(quadric, radius, radius, v, subdivisions, 1);

   //draw the first cap
   gluQuadricOrientation(quadric,GLU_INSIDE);
   gluDisk( quadric, 0.0, radius, subdivisions, 1);
   glTranslatef( 0,0,v );

   //draw the second cap
   gluQuadricOrientation(quadric,GLU_OUTSIDE);
   gluDisk( quadric, 0.0, radius, subdivisions, 1);
   glPopMatrix();
}

void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
   //the same quadric can be re-used for drawing many cylinders
   GLUquadricObj *quadric=gluNewQuadric();
   gluQuadricNormals(quadric, GLU_SMOOTH);
   renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
   gluDeleteQuadric(quadric);
}

void drawSolidCylinder(vec4 point1, vec4 point2, float radius, int divisions) {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
   
    float xDist = point2.x-point1.x;
    float yDist = point2.y-point1.y;
    float zDist = point2.z-point1.z;
    float dist = sqrt(xDist*xDist + yDist*yDist + zDist*zDist);

    float radToDeg = 57.2957795;
    float ax = radToDeg * acos(zDist/dist);
    if (zDist < 0.0)
        ax = -ax;
    float rx = -yDist*zDist;
    float ry =  xDist*zDist;
    
    glPushMatrix();

    //draw the cylinder body
    glTranslatef(point1.x, point1.y, point1.z);
    glRotatef(ax, rx, ry, 0.0);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluCylinder(quadric, radius, radius, dist, divisions, 1);

    //draw the first cap
    gluQuadricOrientation(quadric, GLU_INSIDE);
    gluDisk(quadric, 0.0, radius, divisions, 1);
    glTranslatef(0, 0, dist);

    //draw the second cap
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluDisk(quadric, 0.0, radius, divisions, 1);
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   glTranslatef(0,0,-7);

   drawSolidCylinder(vec4(0, -4, 0, 0), vec4(1, -2, 1, 0), 1, 20);
   
   t=0.53;
   glutSwapBuffers();
} 

void InitGL(int Width, int Height) {
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(3.0);
   glDepthFunc(GL_LESS);
   glEnable(GL_DEPTH_TEST);

   glShadeModel(GL_SMOOTH);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
   glMatrixMode(GL_MODELVIEW);

   glEnable(GL_LIGHTING);
   GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
   GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };
   glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
   glEnable(GL_LIGHT1);
}


int glTest(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(640, 480);
   gwindow = glutCreateWindow("");
   glutDisplayFunc(&display);
   //glutKeyboardFunc(&keyPressed);
   //glutFullScreen();
   glutIdleFunc(&display);
   InitGL(640, 480);
   glutMainLoop();
   return 0;
}



int main(int argc, char** argv) {
    //drawTrees();
    glTest(argc, argv);
}


void startGlfw() {
	// Initialise GLFW
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return;
	}
    
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
	if( window == NULL ) {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
    
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

int drawTrees () {
    srand(time(0));
    startGlfw();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(0,0,20), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

    vec4 root(0, -10, 0, 0);
    vec4 point(0, -5, 0, 0);
    Branch branch(root, point, 2.0f);

    
    Tree tree(branch, 6);


    vec4 a(0, 0, 0, 0);
    vec4 b(3, 3, -3, 0);
    int radius = 10;
    int pieces = 10;

    vec4 dir = normalize(b-a);

    vector<float> vertices = tree.getVertices();
    const int size = tree.getSize();
    
	static const GLushort g_element_buffer_data[] = { 0, 1, 2 };

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, size*3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}