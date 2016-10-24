#ifndef _MAINPLAYER_INCLUDE
#define _MAINPLAYER_INCLUDE

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Item.h"

using namespace std;

class MainPlayer {

public:
	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, CEGUI::Window * inventoryWindow, CEGUI::Window * livesWindow);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec3 getPlayerPosition();
	void setLives(int numLives);
	void digAnimation();
	void atacAnimation();
	void putMaterial();
	void reciveDMG(int dmg);
	void mouseClick(int x, int y);
	void equipItem(int num);

	enum playerState {
		WALKING, WEAPON1, WEAPON2, BYPET
	};


private:
	void setUpInventory(CEGUI::Window* inventoryWindow);
	void setUpLives(CEGUI::Window * livesWindowP);
	void materialDigged(int material);
	void spriteStandLeft();
	bool isDiggingLateral();
	bool isDiggingBottom();
	bool isAttacking();
	bool bJumping;
	bool bLeft;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	int live;
	Texture spritesheet;
	Texture spritesheetAtac;
	Sprite *sprite;
	Sprite *spriteAtac;
	Sprite *currentSprite;
	TileMap *map;
	CEGUI::Window* windHeart1;
	CEGUI::Window* windHeart2;
	CEGUI::Window* windHeart3;
	CEGUI::Window* livesWindow;
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
	Item* equipedItem; 
	vector<Item> inventory;
};


#endif // _P_BOSS_INCLUDE