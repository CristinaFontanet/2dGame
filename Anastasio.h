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

	void init(const glm::ivec2 & tileMapPos, ShaderProgram &shaderProgram, int type);

	void setTileMap(TileMap * tileMap);

	void setPosition(const glm::vec2 & pos);

	void setTarget(MainPlayer * player);

	void render();

	bool update(int deltaTime);
	bool nextText();

	enum AnastasioType {
		TUTORIAL, INSTRUCTIONS, HELP
	};

	void startInstructions();
	void showHelp();
	void helpOut();
	void startTutorial();

	void showCred();

private:
	int anastasioType;
	OwnTexture bigSpritesheet;
	Sprite *sprite;
	TileMap *map;
	MainPlayer *player;
	double prop;
	glm::ivec2 tileMapDispl, posEnemy;

	bool tutorialEnded;
	bool showingDialog;
	bool asking;
	int currentText;
	int isHelp;
	bool playerColision();

};

#endif