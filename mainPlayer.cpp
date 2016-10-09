#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 90
#define FALL_STEP 4
#define HEIGHTWALK 64
#define WIDTHWALK 32
#define SPRITEMARGIN 32
#define ANIMATION_SPEED 8

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ARM1_LEFT,ARM1_LEFT_BOT, ARM1_RIGHT, ARM1_RIGHT_BOT
};

void MainPlayer::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	digCount = 0;
	heightProp = 1.f / 32.f;
	widhtProp = 1.f / 48.f;
	double yoffset = 1.f /32.f;
	bJumping = false;
	bLeft = true;
	spritesheet.loadFromFile("images/Especials_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widhtProp * 4, heightProp * 4), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	double widht = 4 * widhtProp;
	//caminar
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widht, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widht * 2, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widht * 3, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widht * 4, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widht * 5, 0.f));

	double height = 4 * heightProp;
	sprite->setAnimationSpeed(STAND_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(widht * 5, height));

	sprite->setAnimationSpeed(MOVE_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, height));	//Corrent    
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widht, height));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widht * 5, height));

	//WEAPON1 (11*2)
	height = 8 * heightProp;
	sprite->setAnimationSpeed(ARM1_LEFT_BOT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 8, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 9, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 10, height));

	sprite->setAnimationSpeed(ARM1_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 8, height));

	height = 12 * heightProp;
	sprite->setAnimationSpeed(ARM1_RIGHT_BOT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 8, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 9, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 10, height));

	sprite->setAnimationSpeed(ARM1_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 8, height));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	height = HEIGHTWALK;
	spriteWidth = WIDTHWALK;
}

bool MainPlayer::isDiggingLateral() {
	if (sprite->animation() == ARM1_LEFT || sprite->animation() == ARM1_RIGHT ) return true;
	else return false;
}
bool MainPlayer::isDiggingBottom() {
	if (sprite->animation() == ARM1_LEFT_BOT ||  sprite->animation() == ARM1_RIGHT_BOT) return true;
	else return false;
}

void MainPlayer::update(int deltaTime) {

	sprite->update(deltaTime);
	if (isDiggingLateral()) { 
		if (sprite->getNumKeyFrameMissing() != 8) {
			
		}
		else {
			++digCount;
		}
	}
	else if (isDiggingBottom()) {
		if (sprite->getNumKeyFrameMissing() != 11) {
			
		}
		else {
			++digCount;
		}
	}
	//SPRITE
	if (Game::instance().getKey('p')) {
		pair<int,int> mousePos = Game::instance().getMousePosition();
		
		map->addMaterial(posPlayer.x, posPlayer.y, DIAMOND);	//bloque
	}
	if (Game::instance().getKey('c')) {	//PICAR
		//TODO: recolocar sprite si es troba en colisio
		map->dig(posPlayer.x, posPlayer.y);
		spriteWidth = 64;
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			if (bLeft && sprite->animation() != ARM1_LEFT_BOT) sprite->changeAnimation(ARM1_LEFT_BOT);
			else if (!bLeft && sprite->animation() != ARM1_RIGHT_BOT) sprite->changeAnimation(ARM1_RIGHT_BOT);
		}
		else {
			if (bLeft && sprite->animation() != ARM1_LEFT) sprite->changeAnimation(ARM1_LEFT);
			else if (!bLeft && sprite->animation() != ARM1_RIGHT) sprite->changeAnimation(ARM1_RIGHT);
		}
	}
	else {
		spriteWidth = 32;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) { //Moure dreta
			bLeft = true;
			if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(spriteWidth, 64))) {
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) { //Moure esquerre
			bLeft = false;
			if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(spriteWidth, 64))) { 	//si hi ha colisio, ens parem
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else {	//aturat
			if (sprite->animation() == MOVE_RIGHT) {
				sprite->changeAnimation(STAND_RIGHT);
			}
			else if (sprite->animation() != STAND_RIGHT) spriteStandLeft();
		}
	}
	
	marg = 0;
	//POSICIO Y
	if (bJumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180) {
			bJumping = false;
		}
		else {
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				glm::ivec2 spritePos = posPlayer;
				bJumping = !map->collisionMoveDown(spritePos, glm::ivec2(spriteWidth, 64), &posPlayer.y, bLeft, marg);
			}
		}
	}
	else {
		posPlayer.y += FALL_STEP;
		glm::ivec2 spritePos = posPlayer;
		if (map->collisionMoveDown(spritePos, glm::ivec2(spriteWidth,64), &posPlayer.y, bLeft, marg)) {
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void MainPlayer::spriteStandLeft() {
		sprite->changeAnimation(STAND_LEFT);
}

void MainPlayer::render()
{
	sprite->render();
}

void MainPlayer::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void MainPlayer::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec3 MainPlayer::getPlayerPosition() {
	return glm::vec3(posPlayer.x, posPlayer.y, 0.f);
}
