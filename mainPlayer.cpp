#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 90
#define FALL_STEP 4
#define HEIGHT 32
#define WIDTH 32
#define ANIMATION_SPEED 8


enum PlayerMoves
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ARM1_LEFT, ARM1_RIGHT, ARM2_LEFT, ARM2_RIGHT, RIDING_LEFT, RIDING_RIGHT
};



void MainPlayer::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	heightProp = 1.f / 44.f;
	widhtProp = 1.f / 65.f;
	double yoffset = 1.f /44.f;
	bJumping = false;
	spritesheet.loadFromFile("images/Especials_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	sprite = Sprite::createSprite(glm::ivec2(WIDTH, HEIGHT), glm::vec2(widhtProp*2.1, heightProp*3), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(18);
	//sprite->setScale(2.f, 2.f);
	//caminar
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 7 * heightProp));

	sprite->setAnimationSpeed(MOVE_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));	//Corrent
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));

	//ARMS
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, 7 * heightProp));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, 7 * heightProp));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, 7 * heightProp));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, 7 * heightProp));
	

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	playerState = WALKING;
}

void MainPlayer::update(int deltaTime) {
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) { //Moure dreta
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(WIDTH, HEIGHT)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) { //Moure esquerre
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(WIDTH, HEIGHT)))	//si hi ha colisio, ens parem
		{
			posPlayer.x -= 2;
			sprite->setSize(glm::vec2(widhtProp*3, heightProp * 3));
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else {	//aturat
		if (sprite->animation() == MOVE_LEFT) spriteStandLeft();
		else if (sprite->animation() == MOVE_RIGHT) {

			sprite->setSize(glm::vec2(widhtProp * 3, heightProp * 3));
			sprite->changeAnimation(STAND_RIGHT);
		}
	}

	//POSICIO
	if (bJumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(WIDTH, HEIGHT), &posPlayer.y);
		}
	}
	else {
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(WIDTH, HEIGHT), &posPlayer.y))
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void MainPlayer::spriteStandLeft() {
	switch (playerState) {
	case WALKING:
		sprite->changeAnimation(STAND_LEFT);
		break;
	case WEAPON1:
		sprite->changeAnimation(ARM1_LEFT);
		break;
	default:
		break;
	}
}
void MainPlayer::setPlayerState(int state) {
	playerState = state;
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




