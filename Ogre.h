#ifndef _ENOGRE_INCLUDE
#define _ENOGRE_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"
#include "MainPlayer.h"


using namespace std;

class EnOgre {
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

	bool reciveDmg(int dmg, glm::ivec2 dmgAt);

private:

	bool nextBool(double probability);

	OwnTexture spritesheet;
	OwnTexture spritesheetFruit;
	Sprite *sprite;
	Sprite *fruitMode;
	TileMap *map;
	MainPlayer *player;
	double heightProp;
	double widhtProp;
	glm::ivec2 tileMapDispl, posEnemy;
	bool bLeft, bJumping;
	bool attacking;
	bool curative;
	int jumpAngle, startY;
	int live;
};

#endif