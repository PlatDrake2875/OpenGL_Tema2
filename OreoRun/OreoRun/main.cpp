// Oreo race
// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"
#include "Model.h"


void Initialize(void)
{
	glClearColor(1.f, 1.f, 1.f, 1.0f); // culoarea de fond a ecranului
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);       

	Shader shader("example.vert", "example.frag");
	Model oreo("models/oreo.glb");
	oreo.Draw(shader);

	// glutSwapBuffers();
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(600, 600); //dimensiunile ferestrei
	glutCreateWindow("Oreo Run"); // titlul ferestrei
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	Initialize(); // apelam functia de initializare
	glutDisplayFunc(RenderFunction);
	glutMainLoop();
	
}

