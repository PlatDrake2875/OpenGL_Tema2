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
#include "Camera.h"

int winWidth = 1280, winHeight = 720;
GLuint projectionLocation, viewLocation;

Shader* shader;
Model* oreo;
Camera* camera;

void ReshapeWindowFunction(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	camera->setViewWidthAndHeight(newWidth, newHeight);
}

void ProcessSpecialKeys(int key, int xx, int yy)
{
	camera->ProcessSpecialKeys(key, xx, yy);
}

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	camera->ProcessNormalKeys(key, x, y);
}

void CreateModels() {
	oreo = new Model("models/oreo_4/oreo_4.gltf");
}

void DestroyModels() {
	delete oreo;
}

void Initialize(void)
{
	shader = new Shader("example.vert", "example.frag");
	shader->use(); // pentru desenare se va folosi acest shader

	// se obtin locatiile matricilor relativ la shaderul curent
	projectionLocation = shader->getUniformLocation("projection");
	viewLocation = shader->getUniformLocation("view");

	glClearColor(0.15f, 0.f, 0.5f, 1.0f); // culoarea de funal a ecranului

	CreateModels(); // initializam modelele 3d
	
	// initiem camera
	camera = new Camera(glm::vec3(0.f, 0.f, 300.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, -1.f), winWidth, winHeight);
}

void Cleanup(void)
{
	DestroyModels();	// distruge modelele incarcate
	delete shader;		// sterge obiectul shader
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glEnable(GL_DEPTH_TEST);

	glm::mat4 view = camera->getViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = camera->getProjectionMatrix();
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	oreo->Draw(*shader);
	camera->updateCamera();

	glutSwapBuffers();
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(winWidth, winHeight); 
	glutCreateWindow("Oreo Run"); 
	glewInit(); // FUNCTIA ASTA TREBUIE APELATA INAINTEA FOLOSIRII ORICAREI ALTA FUNCTIE DIN GLEW (SAU GL)
	Initialize(); 
	glutReshapeFunc(ReshapeWindowFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(ProcessSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();

	return 0;
}

