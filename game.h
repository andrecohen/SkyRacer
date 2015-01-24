#ifndef __GAME_H__
#define __GAME_H__

class Map;

class Game {

public:

	Game();

	void draw();
	void keyDown(unsigned char);
	void keyUp(unsigned char);

	void move();

private:

	Map *map;

	float playerPosition[3];
	
	float playerAcceleration[3];
	float playerVelocity[3];
	
};

#endif