/*
 * Skeleton code for COSE436 Fall 2024 Assignment 3
 *
 * Won-Ki Jeong, wkjeong@korea.ac.kr
 *
 */

#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <assert.h>
#include "textfile.h"
#include "Angel.h"

 //
 // Definitions
 //
#define WIDTH 600
#define HEIGHT 600
typedef struct {
	unsigned char x, y, z, w;
} uchar4;
typedef unsigned char uchar;

// BMP loader
void LoadBMPFile(uchar4** dst, int* width, int* height, const char* name);


// Shader programs
GLuint p;

// Texture
GLuint color_tex;

mat4 viewMat = LookAt(
	vec4(0.0, 0.0, 3.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(0.0, 1.0, 0.0, 0.0));

mat4 projMat = Ortho(-5, 5, -5, 5, 0, 10);
mat4 modelMat = mat4(1.0);

unsigned int VAO;

// 578 769
float vertices[] = {
	//// positive z
	//0.5, 0.5, 0.5, 0.666, 0.499,		// top right  385 384
	//-0.5, 0.5, 0.5, 0.334, 0.499,		// top left  192 384
	//-0.5, -0.5, 0.5, 0.334, 1 - 0.748,		// bottom left  192 575
	//0.5, -0.5, 0.5, 0.666, 1 - 0.748,		// bottom right  385 575

	-0.5f,-0.5f,-0.5f, // triangle 1 : begin
	-0.5f,-0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f, // triangle 1 : end
	0.5f, 0.5f,-0.5f, // triangle 2 : begin
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f, // triangle 2 : end
	0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f,-0.5f, 0.5f,
	0.5f,-0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f,-0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f,-0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f,-0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f,-0.5f, 0.5f
};
// Trackball parameters initialization 
float angle = 0.0, axis[3], trans[3];

bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;

float lastPos[3] = { 0.0, 0.0, 0.0 };
int curx, cury;
int startX, startY;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;

	float ratio = 1.0f * (float)w / (float)h;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

}


void keyboard(unsigned char key, int x, int y)
{
	// ToDo
	if (key == 'p') {
		// ToDo
	}

	glutPostRedisplay();
}

mat4 RotateAroundAxis(float ang, float x, float y, float z)
{
	if (ang == 0) {
		return mat4(1.0);
	}

	vec3 naxis = normalize(vec3(x, y, z));
	mat4 result = mat4(1.0);
	result[0][0] = pow(naxis[0], 2) * (1 - cos(ang)) + cos(ang);
	result[0][1] = naxis[0] * naxis[1] * (1 - cos(ang)) - naxis[2] * sin(ang);
	result[0][2] = naxis[0] * naxis[2] * (1 - cos(ang)) + naxis[1] * sin(ang);

	result[1][0] = naxis[0] * naxis[1] * (1 - cos(ang)) + naxis[2] * sin(ang);
	result[1][1] = pow(naxis[1], 2) * (1 - cos(ang)) + cos(ang);
	result[1][2] = naxis[1] * naxis[2] * (1 - cos(ang)) - naxis[0] * sin(ang);

	result[2][0] = naxis[0] * naxis[2] * (1 - cos(ang)) - naxis[1] * sin(ang);
	result[2][1] = naxis[1] * naxis[2] * (1 - cos(ang)) + naxis[0] * sin(ang);
	result[2][2] = pow(naxis[2], 2) * (1 - cos(ang)) + cos(ang);

	return result;
}
void renderScene(void)
{
	// ToDo

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	modelMat = Translate(vec3(0, 0, -3)) * RotateAroundAxis(angle, axis[0], axis[1], axis[2])* Translate(vec3(0, 0, 3)) * modelMat;

	mat4 modelViewProj = projMat * modelMat * viewMat;
	int mvpIdx = glGetUniformLocation(p, "Mvp");
	glUniformMatrix4fv(mvpIdx, 1, GL_TRUE, modelViewProj);
	glColor3f(1, 0, 0);

	glBindTexture(GL_TEXTURE_2D, color_tex);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	angle = 0.0;
	glutSwapBuffers();
}


void idle()
{
	// do something for animation here b/c this will be called when idling


	glutPostRedisplay();
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Create shader program
	p = createGLSLProgram("../vshader.vert", NULL, "../fshader.frag");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);


	// Load image for texture -- change this code to load different images
	int width, height;
	uchar4* dst;
	LoadBMPFile(&dst, &width, &height, "../mob.bmp");

	// Create an RGBA8 2D texture, 24 bit depth texture, 256x256
	glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_2D, color_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);


	// Initiate VAO, VBO, IBO
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}



void mouseMotion(int x, int y)
{

	if (trackingMouse) //If the left button has been clicked
	{
		float curPos[3], dx, dy, dz;
		float d, norm;
		curPos[0] = (2.0f * x - WIDTH) / WIDTH; //Calculate x component for vector at mouse's current position
		curPos[1] = (HEIGHT - 2.0f * y) / HEIGHT; //Calculate y component for vector at mouse's current position
		d = sqrtf(curPos[0] * curPos[0] + curPos[1] * curPos[1]); //Calculate z component
		d = (d < 1.0f) ? d : 1.0f; //Project vector onto surface of trackball
		curPos[2] = sqrtf(1.001f - d * d); //Calculate z component
		norm = 1.0 / sqrt(curPos[0] * curPos[0] + curPos[1] * curPos[1] + curPos[2] * curPos[2]);
		curPos[0] *= norm; //Normalize vecor
		curPos[1] *= norm;
		curPos[2] *= norm;
		dx = curPos[0] - lastPos[0]; //Check if mouse has moved from last position
		dy = curPos[1] - lastPos[1];
		dz = curPos[2] - lastPos[2];
		if (dx || dy || dz) //If mouse has moved
		{
			angle = 90.0 * sqrt(dx * dx + dy * dy + dz * dz); //Calculate rotation angle
			axis[0] = lastPos[1] * curPos[2] - lastPos[2] * curPos[1]; //Calculate rotation axis
			axis[1] = lastPos[2] * curPos[0] - lastPos[0] * curPos[2];
			axis[2] = lastPos[0] * curPos[1] - lastPos[1] * curPos[0];
			lastPos[0] = curPos[0]; //Set the last position to the current
			lastPos[1] = curPos[1];
			lastPos[2] = curPos[2];
		}
	}

	glutPostRedisplay();
}




void mouseButton(int button, int state, int x, int y)
{
	//Detect mouse click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		trackingMouse = true; //Set boolean so that future mouse movements are tracked

		float d, norm;
		lastPos[0] = (2.0f * x - WIDTH) / WIDTH; //Calculate the x and y components of the initial movement vector
		lastPos[1] = (HEIGHT - 2.0f * y) / HEIGHT;
		d = sqrtf(lastPos[0] * lastPos[0] + lastPos[1] * lastPos[1]); //Calculate the z component of the vector using pythagorean theorem
		d = (d < 1.0f) ? d : 1.0f; //If the z component is not on the surface of the trackball, set it to 1: the radius of the trackball
		lastPos[2] = sqrtf(1.001f - d * d);
		norm = 1.0 / sqrt(lastPos[0] * lastPos[0] + lastPos[1] * lastPos[1] + lastPos[2] * lastPos[2]); //Calculate vector length
		lastPos[0] *= norm; //Normalize vector
		lastPos[1] *= norm;
		lastPos[2] *= norm;
	}
	else
		trackingMouse = false; //If button not clicked, set boolean so that no mouse movement is tracked
}
int main(int argc, char** argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("COSE436 - Assignment 3");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 is not supported\n");
		exit(1);
	}

	init();

	// Entering GLUT event processing cycle
	glutMainLoop();

	return 1;
}