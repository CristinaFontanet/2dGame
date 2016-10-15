#include "Enemy.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"

#define ANIMATION_SPEED 8
#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 90

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	heightProp = 1.f / 16.f;
	widhtProp = 1.f / 2.f;
	double yoffset = 1.f / 32.f;
	bLeft = true;
	bJumping = false;
	spritesheet.loadFromFile("images/unicorn.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widhtProp, heightProp), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(widhtProp, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp *1));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp *2));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp *3));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp *4));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp *5));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 6));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 7));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, heightProp * 8));


	sprite->setAnimationSpeed(MOVE_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 1));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 2));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 3));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 4));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 5));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 6));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 7));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp, heightProp * 8));


	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::update(int deltaTime) {
	sprite->update(deltaTime);
	int spriteWidth = 64;
	if (bLeft && !map->collisionMoveLeft(posEnemy, glm::ivec2(spriteWidth, 64))) { //Moure esquerra
		bLeft = true;
		if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
		posEnemy.x -= 2;
	}
	else {
		bLeft = false;
		if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
		posEnemy.x += 2;
		if (map->collisionMoveRight(posEnemy, glm::ivec2(spriteWidth, 64)) && !bJumping) { 	//si hi ha colisio, ens parem
			if (nextBool(0.7)) {
				posEnemy.x -= 2;
				bLeft = true;
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			}
			else {
				bJumping = true;
				jumpAngle = 0;
				startY = posEnemy.y;
			}

		}
	}

	if (bJumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180) {
			bJumping = false;
		}
		else {
			int posPlayerIniY = posEnemy.y;
			posEnemy.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			glm::ivec2 spritePos = posEnemy;
			if (map->collisionMoveUp(spritePos, glm::ivec2(spriteWidth, 64), &posEnemy.y, bLeft, 0)) {
				bJumping = false;
			}
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(spritePos, glm::ivec2(spriteWidth, 64), &posEnemy.y, bLeft, 0);
			}
		}
	}
	else {
		posEnemy.y += 2;
	}

	/*if(!map->collisionMoveDown(posEnemy, glm::ivec2(64, 64), &posEnemy.y, bLeft, 0)){
		posEnemy.y += 1;
	}	*/


	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

bool Enemy::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}