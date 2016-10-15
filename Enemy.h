#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"


using namespace std;

class Enemy {
public:

	enum enemyState {
		WALKING, ATTACKING
	};
	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram);

	void setTileMap(TileMap * tileMap);

	void setPosition(const glm::vec2 & pos);

	void render();

	void update(int deltaTime);

private:

	bool nextBool(double probability);

	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	double heightProp;
	double widhtProp;
	glm::ivec2 tileMapDispl, posEnemy;
	bool bLeft;
	bool bJumping;
	int jumpAngle, startY;

};


#endif