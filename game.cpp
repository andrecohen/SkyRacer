#include <OpenGL/gl.h>
#include <Glut/glut.h>
#include <iostream>
#include <math.h>

#include "game.h"
#include "map.h"

Game::Game() {
	map = new Map();

	playerPosition[0] = 0;
	playerPosition[1] = 0;
	playerPosition[2] = 0;

	playerAcceleration[0] = 0;
	playerVelocity[0] = 0;
	playerAcceleration[1] = 0;
	playerVelocity[1] = 0;
	playerAcceleration[2] = 0;
	playerVelocity[2] = 0;

}


void Game::draw() {

	move();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	float ambientLight[] = { 0, 0, 0, 1};
	float diffuseLight[] = { 1, 1, 1, 1};
	float specularLight[] = { 1, 1, 1, 1};
	float position[] = { playerPosition[0], playerPosition[1]+5, 10};
	 

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 10, 0, 0, 0, 0.0, 2, 0);

	glTranslatef(playerPosition[0], playerPosition[1]/5.0, playerPosition[2]);
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	map->draw();


	glTranslatef(-playerPosition[0], playerPosition[1]-.25, -playerPosition[2]);
	glColor3f(34/255.,173/255.,194/255.);
	glutSolidCube(.25);

	glutSwapBuffers();

}

void Game::keyDown(unsigned char key) {

	static float acceleration[] = {20, 10, 10};


	if(key=='w') 
		playerAcceleration[2] = acceleration[2];
	if(key=='s')
		playerAcceleration[2] = -acceleration[2];
	if(key=='a')
		playerAcceleration[0] = acceleration[0];
	if(key=='d')
		playerAcceleration[0] = -acceleration[0];
	
	if(key==' ' && playerAcceleration[1] == 0)
		playerAcceleration[1] = acceleration[1];

}
void Game::keyUp(unsigned char key) {
	if(key=='a' || key=='d'){
		playerAcceleration[0] = 0;
		playerVelocity[0] = 0;
	}
	if(key=='w' || key=='s'){
		playerAcceleration[2] = 0;
	}

}

void Game::move() {
	float nextPosition[3];

	nextPosition[0] = playerPosition[0];
	nextPosition[1] = playerPosition[1];
	nextPosition[2] = playerPosition[2];


	if(playerAcceleration[1] != 0) {
		playerAcceleration[1] -= 20.8*(1/30.0);
		playerVelocity[1] += playerAcceleration[1]*(1/30.0);
		nextPosition[1] += playerVelocity[1] * (1/30.0);
	}


	playerVelocity[0] = fmin(fmax(playerVelocity[0] + playerAcceleration[0]*(1/30.0), -10), 10);
	nextPosition[0] += playerVelocity[0] * (1/30.0);
	playerVelocity[2] = fmin(fmax(playerVelocity[2] + playerAcceleration[2]*(1/30.0), 0), 10);
	nextPosition[2] += playerVelocity[2] * (1/30.0);



	float heightLeft = map->getTileHeight(-nextPosition[0], nextPosition[2]);
	float heightRight = map->getTileHeight(-nextPosition[0]+.5, nextPosition[2]);
	
	float height = (heightLeft>heightRight)?heightLeft:heightRight;


	if(nextPosition[1]<height && playerAcceleration[1]<0) {
		nextPosition[1] = height;
		playerAcceleration[1] = 0;
		playerVelocity[1] = 0;
	}
	// }else if(nextPosition[1]>height && playerAcceleration[1]==0) {
	// 	playerAcceleration[1] = -.25;
	// }


	playerPosition[0] = nextPosition[0];
	playerPosition[1] = nextPosition[1];
	playerPosition[2] = nextPosition[2];


}