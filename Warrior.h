#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"
#include "MainPlayer.h"


using namespace std;

class Warrior {
public:

	enum enemyState {
		WALKING, ATTACKING
	};
	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);

	void setTileMap(TileMap * tileMap);

	void setPosition(const glm::vec2 & pos);

	void setTarget(MainPlayer * player);

	void render();

	void update(int deltaTime);

private:

	bool nextBool(double probability);

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	MainPlayer *player;
	double heightProp;
	double widhtProp;
	glm::ivec2 tileMapDispl, posEnemy;
	bool bLeft;
	bool bJumping;
	int jumpAngle, startY;


};


#endif