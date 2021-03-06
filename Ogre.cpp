#include "Ogre.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#define ANIMATION_SPEED 8
#define JUMP_ANGLE_STEP 2
#define JUMP_HEIGHT 45

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ATTACKING_RIGHT, ATTACKING_LEFT
};

enum Fruit {
	STRAWBERRY, BANNANA, WATERMELON, APPLE
};

void EnOgre::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	heightProp = 1.f / 2.f;
	widhtProp = 1.f / 6.f;
	double yoffset = 1.f / 32.f;
	live = 9;
	bLeft = true;
	bJumping = false;
	attacking = false;
	curative = nextBool(0.7);

	spritesheet.loadFromFile("images/ogre.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widhtProp, heightProp), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(widhtProp * 3, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 1, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 2, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp*3, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp*4, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp*5, 0.f));

	sprite->setAnimationSpeed(ATTACKING_LEFT, ANIMATION_SPEED/3);
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(0.f, heightProp));
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(widhtProp * 1, heightProp));
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(widhtProp * 2, heightProp));

	sprite->setAnimationSpeed(ATTACKING_RIGHT, ANIMATION_SPEED/3);
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 3, heightProp));
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 4, heightProp));
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 5, heightProp));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	
	heightProp = 1.f / 3.f;
	widhtProp = 1.f / 5.f;

	spritesheetFruit.loadFromFile("images/fruit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	fruitMode = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(widhtProp, heightProp), &spritesheetFruit, &shaderProgram);
	fruitMode->setNumberAnimations(8);
	fruitMode->setAnimationSpeed(STRAWBERRY, ANIMATION_SPEED);
	fruitMode->addKeyframe(STRAWBERRY, glm::vec2(widhtProp * 0, heightProp*0));

	fruitMode->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void EnOgre::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void EnOgre::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void EnOgre::setTarget(MainPlayer *target){
	player = target;
}

void EnOgre::render()
{
	if(live > 0) sprite->render();
	else if (curative) fruitMode->render();
}

void EnOgre::update(int deltaTime) {
	if (live > 0) {
		sprite->update(deltaTime);
		int spriteWidth = 64;
		int tileSize = map->getTileSize();
		int tileXPlayer = player->getPlayerPosition().x / tileSize;
		int tileYPlayer = player->getPlayerPosition().y / tileSize;
		int tileXEnemy = posEnemy.x / tileSize;
		int tileYEnemy = posEnemy.y / tileSize;
		bool playerInRange = (abs(tileXEnemy - tileXPlayer) < 5);

		//si estamos en progreso de atacar hacemos da�o en nujestra area
		if (attacking) {
			if (sprite->getCurrentNumKeyFrame() == 2) {
				attacking = false;
				if (bLeft) sprite->changeAnimation(STAND_LEFT);
				else sprite->changeAnimation(STAND_LEFT);
			}

			if (bLeft) {
				for (int x = 0; x < 2; ++x) {
					for (int y = -1; y < 2; ++y) {
						int xDmgOgre = tileXEnemy - x;
						int yDmgOgre = tileYEnemy + y;
						if (tileXPlayer == xDmgOgre && tileYPlayer == yDmgOgre) player->reciveDMG(8);
					}
				}
			}
			else {
				for (int x = 0; x < 2; ++x) {
					for (int y = -1; y < 2; ++y) {
						int xDmgOgre = tileXEnemy + x;
						int yDmgOgre = tileYEnemy + y;
						if (tileXPlayer == xDmgOgre && tileYPlayer == yDmgOgre) player->reciveDMG(8);
					}
				}
			}
		}
		else if (playerInRange) {
			int xDist = tileXPlayer - tileXEnemy;
			if ((abs(xDist) < 1) || (!bLeft && abs(xDist) < 2)) {
				attacking = true;
				if (bLeft) sprite->changeAnimation(ATTACKING_RIGHT);
				else sprite->changeAnimation(ATTACKING_LEFT);
			}
			else if (xDist < 0) {
				bLeft = true;
				if (!map->collisionMoveLeft(posEnemy, glm::ivec2(spriteWidth, 64))) {
					if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
					posEnemy.x -= 2;
				}
				else  sprite->changeAnimation(STAND_LEFT);
			}
			else {
				bLeft = false;
				if (!map->collisionMoveRight(posEnemy, glm::ivec2(spriteWidth, 64))) {
					if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
					posEnemy.x += 2;
				}
				else sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else {
			if (bLeft && !map->collisionMoveLeft(posEnemy, glm::ivec2(spriteWidth, 64))) { //Moure esquerra
				bLeft = true;
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
				posEnemy.x -= 2;
			}
			else {
				if (bLeft) {
					bLeft = false;
				}
				else {
					if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
					posEnemy.x += 2;
					if (map->collisionMoveRight(posEnemy, glm::ivec2(spriteWidth, 64)) && !bJumping) { 	//si hi ha colisio, ens parem
						posEnemy.x -= 2;
						bLeft = true;
						if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
					}
				}
			}
		}

		glm::ivec2 spritePos = posEnemy;

		if (!map->collisionMoveDown(spritePos + 5, glm::ivec2(spriteWidth, 64), &posEnemy.y, bLeft, 0)) {
			posEnemy.y += 2;
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	}
	else if (curative) {
		int spriteWidth = 64;
		int tileSize = map->getTileSize();
		int tileXPlayer = player->getPlayerPosition().x / tileSize;
		int tileYPlayer = player->getPlayerPosition().y / tileSize;
		int tileXEnemy = posEnemy.x / tileSize;
		int tileYEnemy = -1 + posEnemy.y / tileSize;
		if(fruitMode->animation() != STRAWBERRY)fruitMode->changeAnimation(STRAWBERRY);
		fruitMode->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
		if (tileXPlayer == tileXEnemy && tileYPlayer == tileYEnemy) {
			player->heal(12);
			curative = false;
		}
	}
	else {
		Game::instance().killOgre(this);
	}
}

bool EnOgre::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}

bool EnOgre::reciveDmg(int dmg , glm::ivec2 dmgAt) {
	int spriteWidth = 64;
	int tileSize = map->getTileSize();
	int dmgX = dmgAt.x / tileSize;
	int dmgY = dmgAt.y / tileSize;
	int tileXEnemy = posEnemy.x / tileSize;
	int tileYEnemy = posEnemy.y / tileSize;
	bool playerInRange = (abs(tileXEnemy - dmgX) < 5);
	if (playerInRange) {
		if (bLeft) {
			for (int x = 0; x < 2; ++x) {
				for (int y = -1; y < 2; ++y) {
					int xEn = tileXEnemy - x;
					int yEn = tileYEnemy + y;
					if (dmgX == xEn && dmgY == yEn) {
						live -= (dmg);
						return true;
					}
				}
			}
		}
		else {
			for (int x = 0; x < 2; ++x) {
				for (int y = -1; y < 2; ++y) {
					int xEn = tileXEnemy + x;
					int yEn = tileYEnemy + y;
					if (dmgX == xEn && dmgY == yEn) {
						live -= (dmg);
						return true;
					}
				}
			}

		}
	}
	return false;
}