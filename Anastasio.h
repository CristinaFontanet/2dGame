#ifndef _ANASTASIO_INCLUDE
#define _ANASTASIO_INCLUDE

#include <vector>
#include "TileMap.h"
#include "Sprite.h"
#include "mainPlayer.h"
#include "DialogGUI.h"

#define SIZE_TUT 2

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
	"First of all you are a noob and noobs don't survive too much and the developers don't stop to send me people like you so your name don't really care until you help us. \n Oh true I haven't told you your mission yet."};

};


#endif