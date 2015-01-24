#ifndef __MAP_H__
#define __MAP_H__


static const int TileEmpty = 0;
static const int TileSolid = 10;
static const int TileSingleTunnel = 20;
static const int TileSingleSolidTunnel = 21;


class Map {

public:

	Map();

	void draw();

	char getTileHeight(int, int);
	char getTileType(int, int);
private:

	char *heights;
	char *tileTypes;

	int width, height;
};

#endif