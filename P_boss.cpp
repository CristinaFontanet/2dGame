#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "P_boss.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 5
#define JUMP_HEIGHT 90
#define FALL_STEP 4
#define HEIGHT 128
#define WIDTH 64


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void P_boss::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	double heightProp = 1.f / 11.f;
	bJumping = false;
	spritesheet.loadFromFile("images/NPC_506duo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(WIDTH, HEIGHT), glm::vec2(0.5, heightProp), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(7);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 2));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 3));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 4));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 5));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 6));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 7));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 8));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 9));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 10));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 2));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 3));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 4));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 5));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 6));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 7));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 8));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 9));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, heightProp * 10));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void P_boss::update(int deltaTime) {
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
		if (map->collisionMoveRight(posPlayer, glm::ivec2(WIDTH, HEIGHT)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else {
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

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
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(WIDTH, HEIGHT), &posPlayer.y, 0, 0);
		}
	}
	else {
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(WIDTH, HEIGHT), &posPlayer.y, 0, 0))
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

void P_boss::render()
{
	sprite->render();
}

void P_boss::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void P_boss::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




