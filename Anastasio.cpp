#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Anastasio.h"
#include "Constants.h"
#include "MenuGUI.h"


#define ANIMATION_SPEED 8
#define SPRITE_SIZE_BIG 512
#define SPRITE_SIZE_SMALL 64

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void Anastasio::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, bool big) {
	bigSprite = big;
	tutorialEnded = false;
	showingDialog = false;
	currentText = 0;
	heightProp = 1.f / 4.f;
	widhtProp = 1.f / 11.f;
	spritesheet.loadFromFile("images/Anastasio.png", TEXTURE_PIXEL_FORMAT_RGBA);
	if (bigSprite)  sprite = Sprite::createSprite(glm::ivec2(SPRITE_SIZE_BIG, SPRITE_SIZE_BIG), glm::vec2(widhtProp*8, heightProp *4), &spritesheet, &shaderProgram);
	else sprite = Sprite::createSprite(glm::ivec2(SPRITE_SIZE_SMALL, SPRITE_SIZE_SMALL), glm::vec2(widhtProp, heightProp), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(8);
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	if (bigSprite) {
		sprite->addKeyframe(STAND_LEFT, glm::vec2(widhtProp*3.f, 0.f));
	}
	else {
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
	}

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(SCREEN_WIDTH- SPRITE_SIZE_BIG), float(SCREEN_HEIGHT - SPRITE_SIZE_BIG)));
	sprite->changeAnimation(STAND_LEFT);

	dialogGUI.init("../GUI", MenuGUI::instance().getRenderer());
	dialogGUI.setText(texts[0]);
}

void Anastasio::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Anastasio::setPosition(const glm::vec2 &pos) {
	if (!bigSprite) {
		posEnemy = pos;    
		sprite->setPosition(glm::vec2(float(posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	}
	else {
		sprite->setPosition(glm::vec2(float(SCREEN_WIDTH - SPRITE_SIZE_BIG), float(SCREEN_HEIGHT - SPRITE_SIZE_BIG)));
	}
}

void Anastasio::setTarget(MainPlayer *target){
	player = target;
}

void Anastasio::render() {
	sprite->render();
	if(showingDialog)dialogGUI.draw();
}

void Anastasio::update(int deltaTime) {
	sprite->update(deltaTime);
	//if(!bigSprite)	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	if (!tutorialEnded) {
		if (player->getPlayerPosition().x > 1070) {
			showingDialog = true;
			player->setTutorialPause(true);
		}
	}
}

bool Anastasio::nextText() {
	currentText++;
	if (currentText < SIZE_TUT) {
		dialogGUI.setText(texts[currentText]);
		return true;
	}
	else {
		player->setTutorialPause(false);
		tutorialEnded = true;
		showingDialog = false;
		return false;
	}
}
