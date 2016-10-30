#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"
#include "MainPlayer.h"


using namespace std;

class Boss {
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

	void followAndAttckPlayer();

	void fase2();

	void fase3();

	void reciveDmg(int dmg, glm::ivec2 dmgAt);

private:

	bool nextBool(double probability);


	OwnTexture spritesheet;
	Sprite *sprite;
	TileMap *map;
	MainPlayer *player;
	double heightProp;
	double widhtProp;
	glm::ivec2 tileMapDispl, posSpriteEnemy, posEnemy;
	bool bLeft;
	bool bJumping;
	bool attacking;
	int jumpAngle, startY;
	int live;
	int fase,numAtF2;
};

#endif