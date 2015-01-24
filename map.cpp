#include <OpenGL/gl.h>
#include <Glut/glut.h>
#include <iostream>
#include <math.h>

#include "map.h"




Map::Map() {
	height = 100;
	width = 5;

	heights = (char *)calloc(sizeof(char), height*width);
	tileTypes = (char *)calloc(sizeof(char), height*width);

	srand(0);
	for(int x=0; x<width; x++) {
		for(int y=0; y<height; y++) {
			// char h = ((rand()%100)/100.0>.8 && y>5)?1:0;
			char h = 0;
			char t = TileSolid;

			heights[y*width+x] = h;
			if((y+5)%10==0)
				t = TileSingleTunnel;
			tileTypes[y*width+x] = t;
		}
	}
}

void Map::draw() {
	srand(0);
	for(int x=0; x<width; x++) {
		for(int y=0; y<height; y++) {

			float h = getTileHeight(x,y);
			float t = getTileType(x,y);

			
			float c = (rand()%100)/600.0;

			glPushMatrix();

			if(t == TileSolid) {
				glColor3f(243/255.+c,243/255.+c,243/255.+c);
				glTranslatef(x, h-1, -y);
				glutSolidCube(1);
			}else if(t==TileSingleTunnel) {
				glColor3f(115/255.+c,111/255.+c,102/255.+c);
				
				glTranslatef(x, h-1, -y);
				glutSolidCube(1);

				glTranslatef(0,.5,-.5);
				
				float radius = .5;
				float innerRadius = .45;
				int segments = 6;
				for(int segment=0; segment<segments; segment++) {
					float r1 = 3.141/segments*segment;
					float r2 = 3.141/segments*(segment+1);
					glBegin(GL_QUADS);
					glVertex3f(cos(r1)*radius, sin(r1)*radius, 0);
					glVertex3f(cos(r1)*radius, sin(r1)*radius, 1);
					glVertex3f(cos(r2)*radius, sin(r2)*radius, 1);
					glVertex3f(cos(r2)*radius, sin(r2)*radius, 0);
					glEnd();

					glBegin(GL_QUADS);
					glVertex3f(cos(r1)*innerRadius, sin(r1)*innerRadius, 0);
					glVertex3f(cos(r1)*innerRadius, sin(r1)*innerRadius, 1);
					glVertex3f(cos(r2)*innerRadius, sin(r2)*innerRadius, 1);
					glVertex3f(cos(r2)*innerRadius, sin(r2)*innerRadius, 0);
					glEnd();


					glBegin(GL_QUADS);
					glVertex3f(cos(r1)*radius, sin(r1)*radius, 1);
					glVertex3f(cos(r2)*radius, sin(r2)*radius, 1);
					glVertex3f(cos(r2)*innerRadius, sin(r2)*innerRadius, 1);
					glVertex3f(cos(r1)*innerRadius, sin(r1)*innerRadius, 1);				
					glEnd();

						
				}

			
			}
			glPopMatrix();
		}
	}
}


char Map::getTileHeight(int x, int y) {
	if(x>width || y>height || x<0 || y<0 || y*width+x>width*height) {
		return -1;
	}
	return heights[y*width+x];
}

char Map::getTileType(int x, int y) {
	if(x>width || y>height || x<0 || y<0 || y*width+x>width*height) {
		return TileEmpty;
	}
	return tileTypes[y*width+x];
}