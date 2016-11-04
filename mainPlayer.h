#ifndef _MAINPLAYER_INCLUDE
#define _MAINPLAYER_INCLUDE

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Item.h"
#include "fmod.hpp"

using namespace std;

class MainPlayer {

public:
	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, CEGUI::Window * inventoryWindow, CEGUI::Window * livesWindow);
	void update(int deltaTime);
	void render();
	void digAnimation();
	void attackAnimation();
	void putMaterial();
	void bellAnimation();
	void reciveDMG(int dmg);
	void heal(int heal);
	void configSounds();
	void mouseClick(int x, int y);

	enum playerState {
		WALKING, WEAPON1, WEAPON2, BYPET
	};

	enum SpriteState {
		NORMAL, ATTACKING
	};

	/** Setters */
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setLives(int numLives);
	void setHealth(int l);
	void setTutorialPause(bool pause);
	void combineInventory(MainPlayer* mPlayer);
	void equipItem(int num);
	void setJumpMod(int mod);

	/**  Getters */
	Item* getSword();
	Item* getPeak();
	Item* getRock();
	Item* getGold();
	Item* getDiamond();
	Item* getBell();
	Item* getSpecialItem();
	int getAmountItem(int i);
	int getLives();
	glm::vec2 getPlayerPosition();

private:
	void setUpInventory(CEGUI::Window* inventoryWindow);
	void setUpLives(CEGUI::Window * livesWindowP);
	void materialDigged(int material);
	void spriteStandLeft();
	bool isDiggingLateral();
	bool isDiggingBottom();
	bool isAttacking();
	bool isBellAnimationInProgress();

	bool bJumping, bLeft, bDamage;
	bool animationInProgress;
	double heightProp, widhtProp;
	int live;
	int jumpAngle, startY;
	int spriteState, spriteSize;
	int marg;
	int height, spriteWidth;
	int digCount;
	int lastDeltaTime;
	int currentAnimation;
	int lastXclick, lastYclick;
	int jumpMod;
	glm::ivec2 tileMapDispl, posPlayer;
	OwnTexture spritesheet;
	OwnTexture spritesheetAtac;
	OwnTexture spritesheetInvincible;
	Sprite *sprite;
	Sprite *spriteAtac;
	Sprite *spriteInvincible;
	TileMap *map;
	CEGUI::Window* windHeart1;
	CEGUI::Window* windHeart2;
	CEGUI::Window* windHeart3;
	CEGUI::Window* livesWindow;
	FMOD::System *system;
	FMOD::Channel *playerChannel = 0;
	FMOD::Sound *dmgSound;
	FMOD::Sound *digSound;
	FMOD::Sound *bellSound;
	Item* equipedItem; 
	vector<Item> inventory;

};


#endif // _P_BOSS_INCLUDE