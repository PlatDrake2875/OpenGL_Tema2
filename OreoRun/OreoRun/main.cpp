// Oreo race
// Codul sursa este adaptat dupa OpenGLBook.com


#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "PlayerInteraction.h"
#include "Camera.h"
#include "LevelLoader.h"
#include "loadShaders.h"
#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "WindowInfo.h"
#include <stdio.h>
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "PlayerMovement.h"

GLuint projectionLocation, modelLocation,
matrUmbraLocation,
viewLocation,
projLocation,
matrRotlLocation,
lightColorLocation,
lightPosLocation,
viewPosLocation,
codColLocation;

int nbFrames = 0;
double lastTime;

Shader* shader;
LevelLoader lloader;
Camera* camera;
Model* skybox;
PlayerMovement* playerMov = new PlayerMovement();

void displayFPS(int value) {
	double currentTime = glutGet(GLUT_ELAPSED_TIME);
	nbFrames++;
	if (currentTime - lastTime >= 1000.0) { // If last print was more than 1 sec ago
		std::cout << nbFrames << " FPS\n";
		nbFrames = 0;
		lastTime += 1000.0;
	}
	glutTimerFunc(100, displayFPS, 0); // Re-register the timer for the next call
}


// sursa de lumina
float xL = -2500.f, yL = 0.f, zL = -1400.f;

// matricea umbrei
float matrUmbra[4][4];

void Initialize(void)
{
	shader = new Shader("example.vert", "example.frag");
	shader->use(); // pentru desenare se va folosi acest shader

	// se obtin locatiile matricilor relativ la shaderul curent
	projectionLocation = shader->getUniformLocation("projection");
	viewLocation = shader->getUniformLocation("view");
	modelLocation = shader->getUniformLocation("model");

	matrUmbraLocation = shader->getUniformLocation("matrUmbra");
	lightColorLocation = shader->getUniformLocation("lightColor");
	lightPosLocation = shader->getUniformLocation("lightPos");
	viewPosLocation = shader->getUniformLocation( "viewPos");

	glClearColor(0.15f, 0.f, 0.5f, 1.f); // culoarea de fundal a ecranului
	
	lloader.loadModels(shader);

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

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	PlayerInteraction::ProcessNormalKeys(key, x, y);
	if(PlayerInteraction::isPlayerInteracting)
		playerMov->ProcessNormalKeys(key, x, y);
}

void Cleanup(void)
{
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

	glm::vec3 dir(1.0f, 1.0f, 1.0f);

	// Sandbox
	playerMov->setPlayer(lloader.getModel(0));
	lloader.setModel(0, playerMov->getPlayer());
	//lloader.rotateModel(0, 10, glm::vec3(1.0f, 0.0f, 0.0f)); 
	//lloader.translateModel(0, dir);
	//lloader.scaleModel(1, 1.01f);
	lloader.drawModels(shader);
	camera->updateCamera();

	// matricea pentru umbra
	float D = -0.5f;
	matrUmbra[0][0] = zL + D; matrUmbra[0][1] = 0; matrUmbra[0][2] = 0; matrUmbra[0][3] = 0;
	matrUmbra[1][0] = 0; matrUmbra[1][1] = zL + D; matrUmbra[1][2] = 0; matrUmbra[1][3] = 0;
	matrUmbra[2][0] = -xL; matrUmbra[2][1] = -yL; matrUmbra[2][2] = D; matrUmbra[2][3] = -1;
	matrUmbra[3][0] = -D * xL; matrUmbra[3][1] = -D * yL; matrUmbra[3][2] = -D * zL; matrUmbra[3][3] = zL;
	glUniformMatrix4fv(matrUmbraLocation, 1, GL_FALSE, &matrUmbra[0][0]);

	// Variabile uniforme pentru iluminare
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 0.9f);
	glUniform3f(lightPosLocation, xL, yL, zL);

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
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(100, displayFPS, 0); // Register the timer callback
	glutReshapeFunc(PlayerInteraction::ReshapeWindowFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutMouseFunc(PlayerInteraction::HandleMouseClick);
	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(PlayerInteraction::ProcessSpecialKeys);
	glutMouseWheelFunc(PlayerInteraction::MouseWheelFunction);
	glutPassiveMotionFunc(PlayerInteraction::MouseMotionFunction);
	glutMotionFunc(PlayerInteraction::MouseMotionFunction);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutCloseFunc(Cleanup);
	glutMainLoop();

	return 0;
}

