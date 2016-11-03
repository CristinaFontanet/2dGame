#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Anastasio.h"
#include "Constants.h"
#include "MenuGUI.h"
#include "Game.h"


#define ANIMATION_SPEED 8
#define SPRITE_SIZE_BIG 500
#define SPRITE_SIZE_SMALL 300

enum BigSpriteMoves {
	INSTR1_1,INSTR1_2, INSTR1_3, INSTR1_4, INSTR1, INSTR2, INSTR3, INSTR4, INSTR5, HELP1, HELP2, HELP3, HELP4, HELP5
};


void Anastasio::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int type) {
	anastasioType = type;
	tutorialEnded = false;
	showingDialog = false;
	asking = false;
	currentText = 0;
	prop = 1.f / 4.f;
	bigSpritesheet.loadFromFile("images/AnastasioTexto.png", TEXTURE_PIXEL_FORMAT_RGBA);

	if(anastasioType ==TUTORIAL) sprite = Sprite::createSprite(glm::ivec2(SPRITE_SIZE_BIG, SPRITE_SIZE_BIG), glm::vec2(prop, prop), &bigSpritesheet, &shaderProgram);
	else sprite = Sprite::createSprite(glm::ivec2(SPRITE_SIZE_SMALL, SPRITE_SIZE_SMALL), glm::vec2(prop, prop), &bigSpritesheet, &shaderProgram);
	sprite->setNumberAnimations(18);
	sprite->setAnimationSpeed(INSTR1_1, ANIMATION_SPEED);
	sprite->setAnimationSpeed(INSTR1_2, ANIMATION_SPEED);
	sprite->setAnimationSpeed(INSTR1_3, ANIMATION_SPEED);
	sprite->setAnimationSpeed(INSTR1_4, ANIMATION_SPEED);
	sprite->setAnimationSpeed(INSTR1, ANIMATION_SPEED);
	sprite->setAnimationSpeed(INSTR2, ANIMATION_SPEED);
	sprite->setAnimationSpeed(INSTR3, ANIMATION_SPEED);
	sprite->setAnimationSpeed(HELP1, ANIMATION_SPEED);
	sprite->setAnimationSpeed(HELP2, ANIMATION_SPEED);
	sprite->setAnimationSpeed(HELP3, ANIMATION_SPEED);
	sprite->setAnimationSpeed(HELP4, ANIMATION_SPEED);
	sprite->setAnimationSpeed(HELP5, ANIMATION_SPEED);
		sprite->addKeyframe(INSTR1_1, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(INSTR1_2, glm::vec2(prop, 0.f));
		sprite->addKeyframe(INSTR1_3, glm::vec2(prop * 2, 0.f));
		sprite->addKeyframe(INSTR1_4, glm::vec2(prop * 3, 0.f));
		sprite->addKeyframe(INSTR1, glm::vec2(0.f, prop));
		sprite->addKeyframe(INSTR2, glm::vec2(prop, prop));
		sprite->addKeyframe(INSTR3, glm::vec2(prop * 2, prop));
		sprite->addKeyframe(INSTR4, glm::vec2(prop * 3, prop));
		sprite->addKeyframe(INSTR5, glm::vec2(0.f, prop *2));
		sprite->addKeyframe(HELP1, glm::vec2(prop * 2, prop * 2));
		sprite->addKeyframe(HELP2, glm::vec2(prop, prop * 2));//ja pic d
		sprite->addKeyframe(HELP3, glm::vec2(prop * 3, prop * 2));	//ja esp d
		sprite->addKeyframe(HELP4, glm::vec2(prop, prop * 2));	//ja bell
		sprite->addKeyframe(HELP5, glm::vec2(0.f, prop * 3));	//castell


	tileMapDispl = tileMapPos;
}

void Anastasio::startInstructions() {
	currentText = 4;
	isHelp = false;
	sprite->changeAnimation(currentText);
}

void Anastasio::startTutorial() {
	currentText = 0;
	isHelp = false;
	sprite->changeAnimation(currentText);
}

void Anastasio::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Anastasio::setPosition(const glm::vec2 &pos) {
	int tilS = map->getTileSize();
	posEnemy = pos;
	if(anastasioType == TUTORIAL) sprite->setPosition(glm::vec2(float((map->getMapSize().x-5)*tilS - SPRITE_SIZE_BIG), float((map->getMapSize().y-23)*tilS-SPRITE_SIZE_BIG)));
	else sprite->setPosition(glm::vec2(float(pos.x+ SCREEN_WIDTH - SPRITE_SIZE_SMALL), float(pos.y+ SCREEN_HEIGHT - SPRITE_SIZE_SMALL) ));
}

void Anastasio::setTarget(MainPlayer *target){
	player = target;
}

void Anastasio::render() {
	sprite->render();
}

bool Anastasio::update(int deltaTime) {
	sprite->update(deltaTime);

	return false;
}

void Anastasio::showHelp() {
	isHelp = true;
	if (!Game::instance().isBossScene()) {
		if (player->getPeak()->getElement() == WOOD) {
			sprite->changeAnimation(HELP1);
		}
		else if (player->getSword()->getElement() == TUSK || player->getSword()->getElement() == ROCK) {
			sprite->changeAnimation(HELP2);
		}
		else if (player->getBell()->getAmount() == 0) {
			sprite->changeAnimation(HELP3);
		}
		else {
			sprite->changeAnimation(HELP4);
		}
	}
	else {
		sprite->changeAnimation(HELP5);
	}
}

bool Anastasio::nextText() {
	currentText++;
	cout << "cT: " << currentText << endl;
	if (isHelp) {
		return false;
	}
	else {
		if (currentText < 9) {
			sprite->changeAnimation(currentText);
			return true;
		}
		else return false;
	}
}
