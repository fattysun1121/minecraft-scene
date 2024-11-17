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
#include <string>
#include <assert.h>
#include "textfile.h"
#include "Angel.h"

 //
 // Definitions
 //
#define WIDTH 600
#define HEIGHT 600

#define GRASS_WIDTH 10

typedef struct {
	unsigned char x, y, z, w;
} uchar4;
typedef unsigned char uchar;

// BMP loader
void LoadBMPFile(uchar4** dst, int* width, int* height, const char* name);


// Shader programs
GLuint p;

// Texture
GLuint grassTex, steveTex, slimeTex, stoneTex;

mat4 viewMat = LookAt(
	vec4(0.0, 0.0, 8.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(0.0, 1.0, 0.0, 0.0));

mat4 projMat = Ortho(-10, 10, -10, 10, 0, 20);
mat4 steveMat = Translate(vec3(0.0, 1.5, -7.0)) * RotateY(-90) * Scale(0.085) * mat4(1.0);
mat4 slimeMat = Translate(vec3(2.0, 0.9, -2.0)) * RotateZ(90) * mat4(1.0);
unsigned int grassVAO, steveVAO, slimeVAO, stoneVAO;

float steveVertices[] = {
	-2.0, 0.0, 4.0, 0.625, 0.004,
	-2.0, 12.0, 4.0, 0.625, 0.373,
	-2.0, 12.0, -4.0, 0.5, 0.373,
	-2.0, 12.0, -4.0, 0.5, 0.373,
	-2.0, 0.0, -4.0, 0.5, 0.004,
	-2.0, 0.0, 4.0, 0.625, 0.004,
	-2.0, 0.0, -4.0, 0.5, 0.003,
	-2.0, 12.0, -4.0, 0.5, 0.371,
	2.0, 12.0, -4.0, 0.438, 0.371,
	2.0, 12.0, -4.0, 0.438, 0.371,
	2.0, 0.0, -4.0, 0.438, 0.003,
	-2.0, 0.0, -4.0, 0.5, 0.003,
	2.0, 0.0, -4.0, 0.437, 0.004,
	2.0, 12.0, -4.0, 0.437, 0.373,
	2.0, 12.0, 4.0, 0.312, 0.373,
	2.0, 12.0, 4.0, 0.312, 0.373,
	2.0, 0.0, 4.0, 0.312, 0.004,
	2.0, 0.0, -4.0, 0.437, 0.004,
	2.0, 0.0, 4.0, 0.312, 0.001,
	2.0, 12.0, 4.0, 0.312, 0.373,
	-2.0, 12.0, 4.0, 0.25, 0.373,
	-2.0, 12.0, 4.0, 0.25, 0.373,
	-2.0, 0.0, 4.0, 0.25, 0.001,
	2.0, 0.0, 4.0, 0.312, 0.001,
	-2.0, 0.0, -4.0, 0.439, 0.5,
	2.0, 0.0, -4.0, 0.439, 0.377,
	2.0, 0.0, 4.0, 0.562, 0.377,
	2.0, 0.0, 4.0, 0.562, 0.377,
	-2.0, 0.0, 4.0, 0.562, 0.5,
	-2.0, 0.0, -4.0, 0.439, 0.5,
	2.0, 12.0, -4.0, 0.437, 0.376,
	-2.0, 12.0, -4.0, 0.437, 0.499,
	-2.0, 12.0, 4.0, 0.314, 0.499,
	-2.0, 12.0, 4.0, 0.314, 0.499,
	2.0, 12.0, 4.0, 0.314, 0.376,
	2.0, 12.0, -4.0, 0.437, 0.376,
	-2.0, -12.0, 0.0, 0.25, 0.0,
	-2.0, 0.0, 0.0, 0.25, 0.375,
	-2.0, 0.0, -4.0, 0.187, 0.375,
	-2.0, 0.0, -4.0, 0.187, 0.375,
	-2.0, -12.0, -4.0, 0.187, 0.0,
	-2.0, -12.0, 0.0, 0.25, 0.0,
	-2.0, -12.0, -4.0, 0.187, 0.0,
	-2.0, 0.0, -4.0, 0.187, 0.375,
	2.0, 0.0, -4.0, 0.125, 0.375,
	2.0, 0.0, -4.0, 0.125, 0.375,
	2.0, -12.0, -4.0, 0.125, 0.0,
	-2.0, -12.0, -4.0, 0.187, 0.0,
	2.0, -12.0, -4.0, 0.125, 0.0,
	2.0, 0.0, -4.0, 0.125, 0.375,
	2.0, 0.0, 0.0, 0.062, 0.375,
	2.0, 0.0, 0.0, 0.062, 0.375,
	2.0, -12.0, 0.0, 0.062, 0.0,
	2.0, -12.0, -4.0, 0.125, 0.0,
	2.0, -12.0, 0.0, 0.062, 0.0,
	2.0, 0.0, 0.0, 0.062, 0.375,
	-2.0, 0.0, 0.0, -0.0, 0.375,
	-2.0, 0.0, 0.0, -0.0, 0.375,
	-2.0, -12.0, 0.0, -0.0, 0.0,
	2.0, -12.0, 0.0, 0.062, 0.0,
	-2.0, -12.0, -4.0, 0.125, 0.5,
	2.0, -12.0, -4.0, 0.125, 0.375,
	2.0, -12.0, 0.0, 0.187, 0.375,
	2.0, -12.0, 0.0, 0.187, 0.375,
	-2.0, -12.0, 0.0, 0.187, 0.5,
	-2.0, -12.0, -4.0, 0.125, 0.5,
	2.0, 0.0, -4.0, 0.125, 0.375,
	-2.0, 0.0, -4.0, 0.125, 0.5,
	-2.0, 0.0, 0.0, 0.062, 0.5,
	-2.0, 0.0, 0.0, 0.062, 0.5,
	2.0, 0.0, 0.0, 0.062, 0.375,
	2.0, 0.0, -4.0, 0.125, 0.375,
	-4.0, 12.0, 4.0, 0.5, 0.5,
	-4.0, 20.0, 4.0, 0.5, 0.75,
	-4.0, 20.0, -4.0, 0.375, 0.75,
	-4.0, 20.0, -4.0, 0.375, 0.75,
	-4.0, 12.0, -4.0, 0.375, 0.5,
	-4.0, 12.0, 4.0, 0.5, 0.5,
	-4.0, 12.0, -4.0, 0.375, 0.5,
	-4.0, 20.0, -4.0, 0.375, 0.75,
	4.0, 20.0, -4.0, 0.25, 0.75,
	4.0, 20.0, -4.0, 0.25, 0.75,
	4.0, 12.0, -4.0, 0.25, 0.5,
	-4.0, 12.0, -4.0, 0.375, 0.5,
	4.0, 12.0, -4.0, 0.25, 0.5,
	4.0, 20.0, -4.0, 0.25, 0.75,
	4.0, 20.0, 4.0, 0.125, 0.75,
	4.0, 20.0, 4.0, 0.125, 0.75,
	4.0, 12.0, 4.0, 0.125, 0.5,
	4.0, 12.0, -4.0, 0.25, 0.5,
	4.0, 12.0, 4.0, 0.125, 0.5,
	4.0, 20.0, 4.0, 0.125, 0.75,
	-4.0, 20.0, 4.0, 0.0, 0.75,
	-4.0, 20.0, 4.0, 0.0, 0.75,
	-4.0, 12.0, 4.0, 0.0, 0.5,
	4.0, 12.0, 4.0, 0.125, 0.5,
	-4.0, 12.0, -4.0, 0.375, 0.75,
	4.0, 12.0, -4.0, 0.375, 1.0,
	4.0, 12.0, 4.0, 0.25, 1.0,
	4.0, 12.0, 4.0, 0.25, 1.0,
	-4.0, 12.0, 4.0, 0.25, 0.75,
	-4.0, 12.0, -4.0, 0.375, 0.75,
	4.0, 20.0, -4.0, 0.25, 0.75,
	-4.0, 20.0, -4.0, 0.25, 1.0,
	-4.0, 20.0, 4.0, 0.125, 1.0,
	-4.0, 20.0, 4.0, 0.125, 1.0,
	4.0, 20.0, 4.0, 0.125, 0.75,
	4.0, 20.0, -4.0, 0.25, 0.75,
	-2.0, -12.0, 4.0, 0.25, 0.0,
	-2.0, 0.0, 4.0, 0.25, 0.375,
	-2.0, 0.0, 0.0, 0.187, 0.375,
	-2.0, 0.0, 0.0, 0.187, 0.375,
	-2.0, -12.0, 0.0, 0.187, 0.0,
	-2.0, -12.0, 4.0, 0.25, 0.0,
	-2.0, -12.0, 0.0, 0.187, 0.0,
	-2.0, 0.0, 0.0, 0.187, 0.375,
	2.0, 0.0, 0.0, 0.125, 0.375,
	2.0, 0.0, 0.0, 0.125, 0.375,
	2.0, -12.0, 0.0, 0.125, 0.0,
	-2.0, -12.0, 0.0, 0.187, 0.0,
	2.0, -12.0, 0.0, 0.125, 0.0,
	2.0, 0.0, 0.0, 0.125, 0.375,
	2.0, 0.0, 4.0, 0.062, 0.375,
	2.0, 0.0, 4.0, 0.062, 0.375,
	2.0, -12.0, 4.0, 0.062, 0.0,
	2.0, -12.0, 0.0, 0.125, 0.0,
	2.0, -12.0, 4.0, 0.062, 0.0,
	2.0, 0.0, 4.0, 0.062, 0.375,
	-2.0, 0.0, 4.0, -0.0, 0.375,
	-2.0, 0.0, 4.0, -0.0, 0.375,
	-2.0, -12.0, 4.0, -0.0, 0.0,
	2.0, -12.0, 4.0, 0.062, 0.0,
	-2.0, -12.0, 0.0, 0.125, 0.5,
	2.0, -12.0, 0.0, 0.125, 0.375,
	2.0, -12.0, 4.0, 0.187, 0.375,
	2.0, -12.0, 4.0, 0.187, 0.375,
	-2.0, -12.0, 4.0, 0.187, 0.5,
	-2.0, -12.0, 0.0, 0.125, 0.5,
	2.0, 0.0, 0.0, 0.125, 0.375,
	-2.0, 0.0, 0.0, 0.125, 0.5,
	-2.0, 0.0, 4.0, 0.062, 0.5,
	-2.0, 0.0, 4.0, 0.062, 0.5,
	2.0, 0.0, 4.0, 0.062, 0.375,
	2.0, 0.0, 0.0, 0.125, 0.375,
	-2.0, 0.0, -4.0, 0.875, 0.0,
	-2.0, 12.0, -4.0, 0.875, 0.375,
	-2.0, 12.0, -8.0, 0.812, 0.375,
	-2.0, 12.0, -8.0, 0.812, 0.375,
	-2.0, 0.0, -8.0, 0.812, 0.0,
	-2.0, 0.0, -4.0, 0.875, 0.0,
	-2.0, 0.0, -8.0, 0.812, 0.0,
	-2.0, 12.0, -8.0, 0.812, 0.375,
	2.0, 12.0, -8.0, 0.75, 0.375,
	2.0, 12.0, -8.0, 0.75, 0.375,
	2.0, 0.0, -8.0, 0.75, 0.0,
	-2.0, 0.0, -8.0, 0.812, 0.0,
	2.0, 0.0, -8.0, 0.75, 0.0,
	2.0, 12.0, -8.0, 0.75, 0.375,
	2.0, 12.0, -4.0, 0.688, 0.375,
	2.0, 12.0, -4.0, 0.688, 0.375,
	2.0, 0.0, -4.0, 0.688, 0.0,
	2.0, 0.0, -8.0, 0.75, 0.0,
	2.0, 0.0, -4.0, 0.688, 0.0,
	2.0, 12.0, -4.0, 0.688, 0.375,
	-2.0, 12.0, -4.0, 0.625, 0.375,
	-2.0, 12.0, -4.0, 0.625, 0.375,
	-2.0, 0.0, -4.0, 0.625, 0.0,
	2.0, 0.0, -4.0, 0.688, 0.0,
	-2.0, 0.0, -8.0, 0.75, 0.5,
	2.0, 0.0, -8.0, 0.75, 0.375,
	2.0, 0.0, -4.0, 0.813, 0.375,
	2.0, 0.0, -4.0, 0.813, 0.375,
	-2.0, 0.0, -4.0, 0.813, 0.5,
	-2.0, 0.0, -8.0, 0.75, 0.5,
	2.0, 12.0, -8.0, 0.75, 0.375,
	-2.0, 12.0, -8.0, 0.75, 0.5,
	-2.0, 12.0, -4.0, 0.688, 0.5,
	-2.0, 12.0, -4.0, 0.688, 0.5,
	2.0, 12.0, -4.0, 0.688, 0.375,
	2.0, 12.0, -8.0, 0.75, 0.375,
	-2.0, 0.0, 8.0, 0.875, 0.0,
	-2.0, 12.0, 8.0, 0.875, 0.375,
	-2.0, 12.0, 4.0, 0.812, 0.375,
	-2.0, 12.0, 4.0, 0.812, 0.375,
	-2.0, 0.0, 4.0, 0.812, 0.0,
	-2.0, 0.0, 8.0, 0.875, 0.0,
	-2.0, 0.0, 4.0, 0.812, 0.0,
	-2.0, 12.0, 4.0, 0.812, 0.375,
	2.0, 12.0, 4.0, 0.75, 0.375,
	2.0, 12.0, 4.0, 0.75, 0.375,
	2.0, 0.0, 4.0, 0.75, 0.0,
	-2.0, 0.0, 4.0, 0.812, 0.0,
	2.0, 0.0, 4.0, 0.75, 0.0,
	2.0, 12.0, 4.0, 0.75, 0.375,
	2.0, 12.0, 8.0, 0.688, 0.375,
	2.0, 12.0, 8.0, 0.688, 0.375,
	2.0, 0.0, 8.0, 0.688, 0.0,
	2.0, 0.0, 4.0, 0.75, 0.0,
	2.0, 0.0, 8.0, 0.688, 0.0,
	2.0, 12.0, 8.0, 0.688, 0.375,
	-2.0, 12.0, 8.0, 0.625, 0.375,
	-2.0, 12.0, 8.0, 0.625, 0.375,
	-2.0, 0.0, 8.0, 0.625, 0.0,
	2.0, 0.0, 8.0, 0.688, 0.0,
	-2.0, 0.0, 4.0, 0.75, 0.5,
	2.0, 0.0, 4.0, 0.75, 0.375,
	2.0, 0.0, 8.0, 0.813, 0.375,
	2.0, 0.0, 8.0, 0.813, 0.375,
	-2.0, 0.0, 8.0, 0.813, 0.5,
	-2.0, 0.0, 4.0, 0.75, 0.5,
	2.0, 12.0, 4.0, 0.75, 0.375,
	-2.0, 12.0, 4.0, 0.75, 0.5,
	-2.0, 12.0, 8.0, 0.688, 0.5,
	-2.0, 12.0, 8.0, 0.688, 0.5,
	2.0, 12.0, 8.0, 0.688, 0.375,
	2.0, 12.0, 4.0, 0.75, 0.375,
};
float slimeVertices[] = {
	0.5, 0.5, -0.5, 0.665, 0.499,
	-0.5, 0.5, -0.5, 1.001, 0.499,
	-0.5, 0.5, 0.5, 1.001, 0.749,
	-0.5, 0.5, 0.5, 1.001, 0.749,
	0.5, 0.5, 0.5, 0.665, 0.749,
	0.5, 0.5, -0.5, 0.665, 0.499,
	0.5, -0.5, 0.5, 0.335, 0.749,
	0.5, 0.5, 0.5, 0.665, 0.749,
	-0.5, 0.5, 0.5, 0.665, 0.997,
	-0.5, 0.5, 0.5, 0.665, 0.997,
	-0.5, -0.5, 0.5, 0.335, 0.999,
	0.5, -0.5, 0.5, 0.335, 0.749,
	-0.5, -0.5, 0.5, 0.335, -0.001,
	-0.5, 0.5, 0.5, 0.665, -0.001,
	-0.5, 0.5, -0.5, 0.665, 0.249,
	-0.5, 0.5, -0.5, 0.665, 0.249,
	-0.5, -0.5, -0.5, 0.335, 0.249,
	-0.5, -0.5, 0.5, 0.335, -0.001,
	-0.5, -0.5, -0.5, 0.002, 0.5,
	0.5, -0.5, -0.5, 0.335, 0.499,
	0.5, -0.5, 0.5, 0.335, 0.749,
	0.5, -0.5, 0.5, 0.335, 0.749,
	-0.5, -0.5, 0.5, 0.002, 0.75,
	-0.5, -0.5, -0.5, 0.002, 0.5,
	0.5, -0.5, -0.5, 0.335, 0.499,
	0.5, 0.5, -0.5, 0.665, 0.499,
	0.5, 0.5, 0.5, 0.665, 0.749,
	0.5, 0.5, 0.5, 0.665, 0.749,
	0.5, -0.5, 0.5, 0.335, 0.749,
	0.5, -0.5, -0.5, 0.335, 0.499,
	-0.5, -0.5, -0.5, 0.335, 0.249,
	-0.5, 0.5, -0.5, 0.665, 0.249,
	0.5, 0.5, -0.5, 0.665, 0.499,
	0.5, 0.5, -0.5, 0.665, 0.499,
	0.5, -0.5, -0.5, 0.335, 0.499,
	-0.5, -0.5, -0.5, 0.335, 0.249,

};
float grassVertices[] = {
	-0.5, -0.5, -0.5, 0.506, 0.327,
	0.5, -0.5, -0.5, 0.506, -0.005,
	0.5, -0.5, 0.5, 0.748, -0.003,
	0.5, -0.5, 0.5, 0.748, -0.003,
	-0.5, -0.5, 0.5, 0.749, 0.329,
	-0.5, -0.5, -0.5, 0.506, 0.327,
	-0.5, 0.5, 0.5, 0.749, 0.661,
	-0.5, -0.5, 0.5, 0.749, 0.329,
	0.5, -0.5, 0.5, 0.998, 0.328,
	0.5, -0.5, 0.5, 0.998, 0.328,
	0.5, 0.5, 0.5, 0.999, 0.661,
	-0.5, 0.5, 0.5, 0.749, 0.661,
	0.5, 0.5, 0.5, 0.004, 0.665,
	0.5, -0.5, 0.5, 0.003, 0.333,
	0.5, -0.5, -0.5, 0.252, 0.332,
	0.5, -0.5, -0.5, 0.252, 0.332,
	0.5, 0.5, -0.5, 0.253, 0.664,
	0.5, 0.5, 0.5, 0.004, 0.665,
	0.5, 0.5, -0.5, 0.507, 0.992,
	-0.5, 0.5, -0.5, 0.507, 0.659,
	-0.5, 0.5, 0.5, 0.749, 0.661,
	-0.5, 0.5, 0.5, 0.749, 0.661,
	0.5, 0.5, 0.5, 0.75, 0.993,
	0.5, 0.5, -0.5, 0.507, 0.992,
	-0.5, 0.5, -0.5, 0.507, 0.659,
	-0.5, -0.5, -0.5, 0.506, 0.327,
	-0.5, -0.5, 0.5, 0.749, 0.329,
	-0.5, -0.5, 0.5, 0.749, 0.329,
	-0.5, 0.5, 0.5, 0.749, 0.661,
	-0.5, 0.5, -0.5, 0.507, 0.659,
	0.5, 0.5, -0.5, 0.253, 0.664,
	0.5, -0.5, -0.5, 0.252, 0.332,
	-0.5, -0.5, -0.5, 0.506, 0.327,
	-0.5, -0.5, -0.5, 0.506, 0.327,
	-0.5, 0.5, -0.5, 0.507, 0.659,
	0.5, 0.5, -0.5, 0.253, 0.664,
};
float stoneVertices[] = { -0.5, -0.5, -0.5, 0.501, 0.333,
	0.5, -0.5, -0.5, 0.501, -0.001,
	0.5, -0.5, 0.5, 0.749, -0.0,
	0.5, -0.5, 0.5, 0.749, -0.0,
	-0.5, -0.5, 0.5, 0.749, 0.334,
	-0.5, -0.5, -0.5, 0.501, 0.333,
	-0.5, 0.5, 0.5, 0.749, 0.666,
	-0.5, -0.5, 0.5, 0.749, 0.334,
	0.5, -0.5, 0.5, 0.999, 0.332,
	0.5, -0.5, 0.5, 0.999, 0.332,
	0.5, 0.5, 0.5, 0.999, 0.667,
	-0.5, 0.5, 0.5, 0.749, 0.666,
	0.5, 0.5, 0.5, 0.004, 0.665,
	0.5, -0.5, 0.5, 0.003, 0.333,
	0.5, -0.5, -0.5, 0.252, 0.332,
	0.5, -0.5, -0.5, 0.252, 0.332,
	0.5, 0.5, -0.5, 0.251, 0.664,
	0.5, 0.5, 0.5, 0.004, 0.665,
	0.5, 0.5, -0.5, 0.5, 0.997,
	-0.5, 0.5, -0.5, 0.501, 0.665,
	-0.5, 0.5, 0.5, 0.749, 0.666,
	-0.5, 0.5, 0.5, 0.749, 0.666,
	0.5, 0.5, 0.5, 0.75, 0.996,
	0.5, 0.5, -0.5, 0.5, 0.997,
	-0.5, 0.5, -0.5, 0.501, 0.665,
	-0.5, -0.5, -0.5, 0.501, 0.333,
	-0.5, -0.5, 0.5, 0.749, 0.334,
	-0.5, -0.5, 0.5, 0.749, 0.334,
	-0.5, 0.5, 0.5, 0.749, 0.666,
	-0.5, 0.5, -0.5, 0.501, 0.665,
	0.5, 0.5, -0.5, 0.251, 0.664,
	0.5, -0.5, -0.5, 0.252, 0.332,
	-0.5, -0.5, -0.5, 0.501, 0.333,
	-0.5, -0.5, -0.5, 0.501, 0.333,
	-0.5, 0.5, -0.5, 0.501, 0.665,
	0.5, 0.5, -0.5, 0.251, 0.664, 
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

// I need a grass model matrix array to store and keep track of the model matrix per grass block
mat4 grassModelMats[GRASS_WIDTH][GRASS_WIDTH];


void drawGrass() {

	// draw a 3 by 3 grass terrain
		
	for (int x = 0; x < GRASS_WIDTH; x++) {
		for (int z = 0; z < GRASS_WIDTH; z++) {
			
			mat4 mv = viewMat;
			grassModelMats[x][z] = Translate(viewMat[0][3], viewMat[1][3], viewMat[2][3]) *
				RotateAroundAxis(angle, axis[0], axis[1], axis[2]) * 
				Translate(-viewMat[0][3], -viewMat[1][3], -viewMat[2][3]) * 
				grassModelMats[x][z];

			mat4 modelViewProj = projMat * grassModelMats[x][z] * viewMat;
			int mvpIdx = glGetUniformLocation(p, "Mvp");
			glUniformMatrix4fv(mvpIdx, 1, GL_TRUE, modelViewProj);

			glBindTexture(GL_TEXTURE_2D, grassTex);
			glBindVertexArray(grassVAO);

			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
	}
}

void drawSlime() {
	mat4 mv = viewMat;
	slimeMat = Translate(viewMat[0][3], viewMat[1][3], viewMat[2][3]) *
		RotateAroundAxis(angle, axis[0], axis[1], axis[2]) *
		Translate(-viewMat[0][3], -viewMat[1][3], -viewMat[2][3]) *
		slimeMat;

	mat4 modelViewProj = projMat * slimeMat * viewMat;
	int mvpIdx = glGetUniformLocation(p, "Mvp");
	glUniformMatrix4fv(mvpIdx, 1, GL_TRUE, modelViewProj);

	glBindTexture(GL_TEXTURE_2D, slimeTex);
	glBindVertexArray(slimeVAO);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(slimeVertices) / (5 * sizeof(float)));

}
void drawSteve() {

	mat4 mv = viewMat;
	steveMat = Translate(viewMat[0][3], viewMat[1][3], viewMat[2][3]) *
		RotateAroundAxis(angle, axis[0], axis[1], axis[2]) *
		Translate(-viewMat[0][3], -viewMat[1][3], -viewMat[2][3]) *
		steveMat;

	mat4 modelViewProj = projMat * steveMat * viewMat;
	int mvpIdx = glGetUniformLocation(p, "Mvp");
	glUniformMatrix4fv(mvpIdx, 1, GL_TRUE, modelViewProj);

	glBindTexture(GL_TEXTURE_2D, steveTex);
	glBindVertexArray(steveVAO);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(steveVertices) / (5 * sizeof(float)));
}
void renderScene(void)
{
	// ToDo
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawGrass();
	drawSteve();
	drawSlime();

	angle = 0.0;
	glutSwapBuffers();
}


void idle()
{
	// do something for animation here b/c this will be called when idling


	glutPostRedisplay();
}



void loadAllTextures() {
	// Load image for texture -- change this code to load different images
	int width, height;
	uchar4* dst;
	LoadBMPFile(&dst, &width, &height, "../grass.bmp");

	// Create an RGBA8 2D texture, 24 bit depth texture, 256x256
	glGenTextures(1, &grassTex);
	glBindTexture(GL_TEXTURE_2D, grassTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);


	// Load Steve texture
	LoadBMPFile(&dst, &width, &height, "../steve.bmp");

	// Create an RGBA8 2D texture, 24 bit depth texture, 256x256
	glGenTextures(1, &steveTex);
	glBindTexture(GL_TEXTURE_2D, steveTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);

	// Load slime texture
	LoadBMPFile(&dst, &width, &height, "../mob.bmp");

	// Create an RGBA8 2D texture, 24 bit depth texture, 256x256
	glGenTextures(1, &slimeTex);
	glBindTexture(GL_TEXTURE_2D, slimeTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);

	// Load stone texture
	LoadBMPFile(&dst, &width, &height, "../stone.bmp");

	// Create an RGBA8 2D texture, 24 bit depth texture, 256x256
	glGenTextures(1, &stoneTex);
	glBindTexture(GL_TEXTURE_2D, stoneTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);

}

void initAllVAOs() {
	// Initiate VAO, VBO, IBO
	unsigned int VBO;

	glGenVertexArrays(1, &grassVAO);
	glBindVertexArray(grassVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, grassVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grassVertices), grassVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	glGenVertexArrays(1, &steveVAO);
	glBindVertexArray(steveVAO);
	glBindBuffer(GL_ARRAY_BUFFER, steveVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(steveVertices), steveVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	glGenVertexArrays(1, &slimeVAO);
	glBindVertexArray(slimeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, slimeVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(slimeVertices), slimeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	glGenVertexArrays(1, &stoneVAO);
	glBindVertexArray(stoneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, stoneVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stoneVertices), stoneVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

}
void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Create shader program
	p = createGLSLProgram("../vshader.vert", NULL, "../fshader.frag");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	loadAllTextures();
	initAllVAOs();
	// For grass blocks

	vec3 firstPos(0.0, 0.0, 0.0);
	if (GRASS_WIDTH % 2) {
		// odd
		float offset = round(GRASS_WIDTH / 2) * 1.0;
		firstPos[0] -= offset;
		firstPos[2] -= offset;
	}

	else {
		// even
		firstPos[0] = -0.5;
		firstPos[2] = -0.5;
		int offset = GRASS_WIDTH / 2 - 1;
		firstPos[0] -= offset;
		firstPos[2] -= offset;
	}
	vec3 trans = firstPos;
	for (int x = 0; x < GRASS_WIDTH; x++) {
		trans[0] = firstPos[0] + x * 1.0;
		for (int z = 0; z < GRASS_WIDTH; z++) {
			
			trans[2] = firstPos[2] + z * 1.0;
			grassModelMats[x][z] = Translate(trans);
		}
	}
	
	glEnable(GL_DEPTH_TEST);
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
	// Detect mouse click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		trackingMouse = true; // Set boolean so that future mouse movements are tracked

		float d, norm;
		lastPos[0] = (2.0f * x - WIDTH) / WIDTH; // Calculate the x and y components of the initial movement vector
		lastPos[1] = (HEIGHT - 2.0f * y) / HEIGHT;
		d = sqrtf(lastPos[0] * lastPos[0] + lastPos[1] * lastPos[1]); // Calculate the z component of the vector using pythagorean theorem
		d = (d < 1.0f) ? d : 1.0f; // If the z component is not on the surface of the trackball, set it to 1: the radius of the trackball
		lastPos[2] = sqrtf(1.001f - d * d);
		norm = 1.0 / sqrt(lastPos[0] * lastPos[0] + lastPos[1] * lastPos[1] + lastPos[2] * lastPos[2]); // Calculate vector length
		lastPos[0] *= norm; // Normalize vector
		lastPos[1] *= norm;
		lastPos[2] *= norm;
	}
	else
		trackingMouse = false; // If button not clicked, set boolean so that no mouse movement is tracked
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