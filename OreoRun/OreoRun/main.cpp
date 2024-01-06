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
#include "WindowInfo.h"
#include "PlayerInteraction.h"

GLuint projectionLocation, viewLocation, modelLocation;

Shader* shader;
Model* oreo;
Camera* camera;
Model* skybox;

void CreateModels() {
	skybox = new Model("skyboxes/skybox_1/scene.gltf");
	oreo = new Model("models/oreo_4/scene.gltf");
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
	modelLocation = shader->getUniformLocation("model");

	glClearColor(0.15f, 0.f, 0.5f, 1.0f); // culoarea de funal a ecranului

	CreateModels(); // initializam modelele 3d
	
	// initiem camera
	camera = new Camera(
		glm::vec3(0.f, 0.f, 300.f), 
		glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3(0.f, 0.f, -1.f), 
		WindowInfo::winWidth, 
		WindowInfo::winHeight
	);

	// setam camera din PlayerInteraction
	PlayerInteraction::camera = camera;
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


	glm::mat4 model = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);

	oreo->Draw(*shader);

	model = glm::scale(glm::vec3(1000.f, 1000.f, 1000.f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);

	skybox->Draw(*shader);
	
	camera->updateCamera();

	glutSwapBuffers();
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(WindowInfo::winWidth, WindowInfo::winHeight);
	glutCreateWindow("Oreo Run"); 
	glewInit(); // FUNCTIA ASTA TREBUIE APELATA INAINTEA FOLOSIRII ORICAREI ALT`A FUNCTIE DIN GLEW (SAU GL)
	Initialize(); 
	glutReshapeFunc(PlayerInteraction::ReshapeWindowFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutMouseFunc(PlayerInteraction::HandleMouseClick);
	glutKeyboardFunc(PlayerInteraction::ProcessNormalKeys);
	glutSpecialFunc(PlayerInteraction::ProcessSpecialKeys);
	glutMouseWheelFunc(PlayerInteraction::MouseWheelFunction);
	glutPassiveMotionFunc(PlayerInteraction::MouseMotionFunction);
	glutMotionFunc(PlayerInteraction::MouseMotionFunction);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutCloseFunc(Cleanup);
	glutMainLoop();

	return 0;
}

