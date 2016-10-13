#ifndef _MAINPLAYER_INCLUDE
#define _MAINPLAYER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Item.h"

class MainPlayer {
#define PICKAXE 1

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec3 getPlayerPosition();
	void digAnimation();
	void setPlayerState(int state);
	void mouseClick(int x, int y);

	enum playerState {
		WALKING, WEAPON1, WEAPON2, BYPET
	};


private:
	void spriteStandLeft();
	bool isDiggingLateral();
	bool isDiggingBottom();
	bool bJumping;
	bool bLeft;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	double heightProp;
	double widhtProp;

	int spriteSize;
	int marg;
	int height, spriteWidth;
	int digCount;
	int lastDeltaTime;
	bool animationInProgress;
	int currentAnimation;
	int lastXclick, lastYclick;
	int equipedItem; 
	vector<Item> inventory;

};


#endif // _P_BOSS_INCLUDE