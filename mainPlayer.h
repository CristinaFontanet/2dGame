#ifndef _MAINPLAYER_INCLUDE
#define _MAINPLAYER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class MainPlayer {

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int playerState;

};


#endif // _P_BOSS_INCLUDE