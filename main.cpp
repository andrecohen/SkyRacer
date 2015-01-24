#include <OpenGL/gl.h>
#include <Glut/glut.h>
#include <iostream>

#include "map.h"
#include "game.h"

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 0.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

Game game;

void timer(int) {
	glutPostRedisplay();
}

void display() {
	game.draw();
	glutTimerFunc(6, timer, 0);
}

void keyUp(unsigned char key, int x, int y) {
	game.keyUp(key);
}

void keyDown(unsigned char key, int x, int y) {
	game.keyDown(key);
}

void init() {
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 800/600.0,
    /* Z near */ 1.0, /* Z far */ 50.0);
}

int main(int argc, char **argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Sky Racer");
	
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyUp);
	glutKeyboardFunc(keyDown);

	glutReshapeWindow(800,600);
	
	init();
	glutMainLoop();
	
	return 0;             

}