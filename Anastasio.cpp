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
#define SPRITE_SIZE_BIG 300
#define SPRITE_SIZE_SMALL 64
#define SPRITE_READY_HEIGHT 90
#define SPRITE_READY_WIDHT 140

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

enum BigSpriteMoves {
	INSTR1, INSTR2, INSTR3, INSTR4, INSTR5, HELP1, HELP2, HELP3, HELP4, HELP5
};


void Anastasio::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int type) {
	anastasioType = type;
	tutorialEnded = false;
	showingDialog = false;
	asking = false;
	currentText = 0;
	heightProp = 1.f / 4.f;
	widhtProp = 1.f / 11.f;
	spritesheet.loadFromFile("images/Anastasio.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bigSpritesheet.loadFromFile("images/AnastasioTexto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	if (anastasioType == TUTORIAL) sprite = Sprite::createSprite(glm::ivec2(SPRITE_SIZE_SMALL, SPRITE_SIZE_SMALL), glm::vec2(widhtProp, heightProp), &spritesheet, &shaderProgram);
	else sprite = Sprite::createSprite(glm::ivec2(SPRITE_SIZE_BIG, SPRITE_SIZE_BIG), glm::vec2(heightProp, heightProp), &bigSpritesheet, &shaderProgram);
	spriteReady = Sprite::createSprite(glm::ivec2(SPRITE_READY_WIDHT, SPRITE_READY_HEIGHT), glm::vec2(widhtProp*2.25, heightProp*1.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	spriteReady->setNumberAnimations(1);
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	spriteReady->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	if (anastasioType == TUTORIAL) {
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		spriteReady->addKeyframe(STAND_LEFT, glm::vec2(0.f, 2.5*heightProp));
		spriteReady->changeAnimation(STAND_LEFT);
		sprite->changeAnimation(STAND_LEFT);
	}
	else {
		sprite->setAnimationSpeed(HELP1, ANIMATION_SPEED);
		sprite->setAnimationSpeed(HELP2, ANIMATION_SPEED);
		sprite->setAnimationSpeed(HELP3, ANIMATION_SPEED);
		sprite->setAnimationSpeed(HELP4, ANIMATION_SPEED);
		sprite->setAnimationSpeed(HELP5, ANIMATION_SPEED);
		sprite->setAnimationSpeed(INSTR1, ANIMATION_SPEED);
		sprite->setAnimationSpeed(INSTR2, ANIMATION_SPEED);
		sprite->setAnimationSpeed(INSTR3, ANIMATION_SPEED);
		sprite->addKeyframe(HELP1, glm::vec2(heightProp * 2, heightProp * 2));
		sprite->addKeyframe(HELP2, glm::vec2(heightProp, heightProp*2));//ja pic d
		sprite->addKeyframe(HELP3, glm::vec2(heightProp*3, heightProp * 2));	//ja esp d
		sprite->addKeyframe(HELP4, glm::vec2(heightProp, heightProp * 2));	//ja bell
		sprite->addKeyframe(HELP5, glm::vec2(heightProp, heightProp * 2));	//castell
		sprite->addKeyframe(INSTR1, glm::vec2(0.f, heightProp));
		sprite->addKeyframe(INSTR2, glm::vec2(heightProp, heightProp));
		sprite->addKeyframe(INSTR3, glm::vec2(heightProp * 2, heightProp ));
		sprite->addKeyframe(INSTR4, glm::vec2(heightProp * 3, heightProp ));
		sprite->addKeyframe(INSTR5, glm::vec2(0.f, heightProp*2));
	}

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(SCREEN_WIDTH- SPRITE_SIZE_BIG), float(SCREEN_HEIGHT - SPRITE_SIZE_BIG)));

	dialogGUI.init("../GUI", MenuGUI::instance().getRenderer());
	dialogGUI.setText(texts[0]);
}

void Anastasio::startInstructions() {
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
	if (anastasioType == TUTORIAL) {
		sprite->setPosition(glm::vec2(float(posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
		spriteReady->setPosition(glm::vec2(float(posEnemy.x-(SPRITE_READY_WIDHT-SPRITE_SIZE_SMALL)), float(tileMapDispl.y + posEnemy.y-(SPRITE_READY_HEIGHT- SPRITE_SIZE_SMALL))));
	}
	else {
		sprite->setPosition(glm::vec2(float(pos.x+ SCREEN_WIDTH - SPRITE_SIZE_BIG), float(pos.y+ SCREEN_HEIGHT - SPRITE_SIZE_BIG) ));
	}
}

void Anastasio::setTarget(MainPlayer *target){
	player = target;
}

void Anastasio::render() {
	if (anastasioType == TUTORIAL && tutorialEnded) spriteReady->render();
	else sprite->render();
	
}

void Anastasio::renderGUI() {
	if (showingDialog) {
		dialogGUI.draw();
	}
}

bool Anastasio::update(int deltaTime) {
	sprite->update(deltaTime);
	//if(!bigSprite)	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	if (!tutorialEnded) {
		if (player->getPlayerPosition().x > 1070) {
			showingDialog = true;
			player->setTutorialPause(true);
		}
	}
	else if (!asking) return playerColision();
	return false;
}

bool Anastasio::playerColision() {
	int tileSize = map->getTileSize();
	int tileXPlayer = player->getPlayerPosition().x / tileSize;
	int tileYPlayer = player->getPlayerPosition().y / tileSize;
	int tileXEnemy = (posEnemy.x - (SPRITE_READY_WIDHT - SPRITE_SIZE_SMALL)) / tileSize;
	int tileYEnemy = posEnemy.y / tileSize;
	if (tileXPlayer == tileXEnemy && tileYPlayer == tileYEnemy) {
		asking = true;
		return true;
	}
	else return false;
}

void Anastasio::showHelp() {
	isHelp = true;
	if (!Game::instance().isBossScene()) {
		if (player->getPeak()->getElement() != DIAMOND) {
			sprite->changeAnimation(HELP1);
		}
		else if (player->getSword()->getElement() != SWORD) {
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
	if (anastasioType == TUTORIAL) {
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
	else if (isHelp) {
		return false;
	}
	else {
		if (currentText < 5) {
			sprite->changeAnimation(currentText);
			return true;
		}
		else return false;
	}
}
