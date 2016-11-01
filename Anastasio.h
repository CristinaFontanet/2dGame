#ifndef _ANASTASIO_INCLUDE
#define _ANASTASIO_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"
#include "mainPlayer.h"
#include "DialogGUI.h"

#define SIZE_TUT 5

using namespace std;

class Anastasio {
public:

	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, bool big);

	void setTileMap(TileMap * tileMap);

	void setPosition(const glm::vec2 & pos);

	void setTarget(MainPlayer * player);

	void render();

	void update(int deltaTime);
	bool nextText();

private:
	bool bigSprite;
	OwnTexture spritesheet;
	Sprite *sprite;
	Sprite *spriteReady;
	TileMap *map;
	MainPlayer *player;
	double heightProp;
	double widhtProp;
	glm::ivec2 tileMapDispl, posEnemy;
	DialogGUI dialogGUI;

	bool tutorialEnded;
	bool showingDialog;
	int currentText;
	string texts[SIZE_TUT] = {"Welcome to WondeRand, you must be the new sacrifice. \n I mean the new HERO! Nice to meet you, my name is Anastasio and I will guide you through this wonderful world.",
	"First of all you are a noob and noobs don't survive too much and the developers don't stop to send me people like you so your name don't really care until you help us. \n Oh true I haven't told you your mission yet.",
	"A few days ago some kind of drake without fire transform our lovely unicorns into crazy horses and invade WondeRand with ugly Ogres. \n Please help us HERO, you are the only one that can do it or the only one who decide to play this kind of game.",
	"Now listen carefully: \n 1. You CAN'T kill the unicorns so don't try it \n 2. You can select your items with the numbers (1-9) or clicking them \n 3. You can use your selected item with right click \n 4. You can upgrade your items in the craft submenu (press Esc) \n 5. If u need help with what to do just press L and I will be there",
	"Oh! I allways forget that you can move with WAD or with the arrows, also you can jump with space but if u don't imagine it maybe you are so... \n To end the tutorial remember this, if you die in WondeRand I can revive you. Also I have limited power and I can only do this if u are in WonderRand so be careful. \n		Good luck in your travel!"};

};


#endif