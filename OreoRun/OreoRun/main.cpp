// Oreo race
// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"
#include "Model.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

GLuint projectionLocation, viewLocation;

float width = 800, height = 600, znear = 1, fov = 30;

float alpha = 0.0f, beta = 0.0f, dist = 30.f;
float Obsx = 100.f, Obsy = -38, Obsz = 50.f;
float Refx = Obsx, Refy = Obsy, Refz = 0.0f;
float Vx = 0.0f, Vy = 0.0f, Vz = -1.0f;
float incr_alpha1 = 0.01f, incr_alpha2 = 0.01f;

void Initialize(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.0f); // culoarea de fond a ecranului
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);       

	Shader shader("example.vert", "example.frag");
	projectionLocation = shader.getUniformLocation("projection");
	viewLocation = shader.getUniformLocation("view");

	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);   // se schimba pozitia observatorului	
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz); // pozitia punctului de referinta
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz); // verticala din planul de vizualizare 
	glm::mat4 view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	Model oreo("models/oreo_1/oreo.obj");
	oreo.Draw(shader);

	 glutSwapBuffers();
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50); // pozitia initiala a ferestrei
	glutInitWindowSize(1280, 720); //dimensiunile ferestrei
	glutCreateWindow("Oreo Run"); // titlul ferestrei
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	Initialize(); // apelam functia de initializare
	glutDisplayFunc(RenderFunction);
	glutMainLoop();
	
}

