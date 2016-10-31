#ifndef _ANASTASIO_INCLUDE
#define _ANASTASIO_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"
#include "mainPlayer.h"


using namespace std;

class Anastasio {
public:

	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);

	void setTileMap(TileMap * tileMap);

	void setPosition(const glm::vec2 & pos);

	void setTarget(MainPlayer * player);

	void render();

	void update(int deltaTime);

private:


	OwnTexture spritesheet;
	Sprite *sprite;
	TileMap *map;
	MainPlayer *player;
	double heightProp;
	double widhtProp;
	glm::ivec2 tileMapDispl, posEnemy;


};


#endif