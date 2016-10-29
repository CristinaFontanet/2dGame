#ifndef _MAINPLAYER_INCLUDE
#define _MAINPLAYER_INCLUDE

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Item.h"
#include "fmod.hpp"
#include "Text.h"

using namespace std;

class MainPlayer {

public:
	Text t;
	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, CEGUI::Window * inventoryWindow, CEGUI::Window * livesWindow);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPlayerPosition();
	void setLives(int numLives);
	void digAnimation();
	void attackAnimation();
	void putMaterial();
	void bellAnimation();
	void reciveDMG(int dmg);
	void configSounds();
	void mouseClick(int x, int y);
	void equipItem(int num);
	Item* getSword();
	Item* getPeak();
	Item* getRock();
	Item* getGold();
	Item* getDiamond();
	Item* getBell();

	enum playerState {
		WALKING, WEAPON1, WEAPON2, BYPET
	};

	enum SpriteState {
		NORMAL, ATTACKING
	};

private:
	void setUpInventory(CEGUI::Window* inventoryWindow);
	void setUpLives(CEGUI::Window * livesWindowP);
	void materialDigged(int material);
	void spriteStandLeft();
	bool isDiggingLateral();
	bool isDiggingBottom();
	bool isAttacking();
	bool isBellAnimationInProgress();
	bool bJumping;
	bool bLeft;
	bool bDamage;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	int live;
	OwnTexture spritesheet;
	OwnTexture spritesheetAtac;
	OwnTexture spritesheetInvincible;
	Sprite *sprite;
	Sprite *spriteAtac;
	Sprite *spriteInvincible;
	TileMap *map;
	int spriteState;
	CEGUI::Window* windHeart1;
	CEGUI::Window* windHeart2;
	CEGUI::Window* windHeart3;
	CEGUI::Window* livesWindow;
	double heightProp;
	double widhtProp;
	FMOD::System *system;
	FMOD::Channel   *playerChannel = 0;
	FMOD::Sound     *dmgSound;
	FMOD::Sound     *digSound;
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
	vector<pair<Item*, vector<pair<Item*, int>>*>> items;
	vector<pair<Item*, int>> evolutionTuskSword;

};


#endif // _P_BOSS_INCLUDE