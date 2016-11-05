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
		TUTORIAL, INSTRUCTIONS
	};

	void startInstructions();
	void showHelp();
	void startTutorial();
	void showCred();

	void helpOut();

private:
	int anastasioType;
	int currentText;
	int isHelp;
	double prop;
	glm::ivec2 tileMapDispl, posEnemy;

	OwnTexture bigSpritesheet;
	Sprite *sprite;
	TileMap *map;
	MainPlayer *player;


};

#endif