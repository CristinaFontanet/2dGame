#include "Boss.h"
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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ATTACKING_RIGHT, ATTACKING_LEFT, TAIL_RIGHT, TAIL_LEFT,
	START_BALL_LEFT, START_BALL_RIGHT, BALL,EXH_LEFT, EXH_RIGHT, START_SECOND_LEFT, START_SECOND_RIGHT, SECOND_RIGHT, SECOND_LEFT
};

void Boss::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	heightProp = 1.f / 10.f;
	widhtProp = 1.f / 4.f;
	double yoffset = 1.f / 32.f;
	fase = 1;
	numAtF2 = 0;
	live = 100;
	bLeft = true;
	bJumping = false;
	attacking = false;
	spritesheet.loadFromFile("images/dragonBoss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(widhtProp, heightProp), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(20);
	
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f , heightProp*2));

	sprite->setAnimationSpeed(MOVE_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 1, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 1, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, heightProp * 2));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 1, heightProp * 2));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, heightProp * 2));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 1, heightProp * 2));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, heightProp * 2));

	sprite->setAnimationSpeed(ATTACKING_LEFT, ANIMATION_SPEED/2);
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(widhtProp * 2, 0.f));
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(widhtProp * 3, 0.f));
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(widhtProp * 3, 0.f));
	sprite->addKeyframe(ATTACKING_LEFT, glm::vec2(widhtProp * 3, 0.f));


	sprite->setAnimationSpeed(ATTACKING_RIGHT, ANIMATION_SPEED/2);
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 2, heightProp*2));
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 3, heightProp*2));
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 3, heightProp * 2));
	sprite->addKeyframe(ATTACKING_RIGHT, glm::vec2(widhtProp * 3, heightProp * 2));

	sprite->setAnimationSpeed(TAIL_LEFT, ANIMATION_SPEED / 2);
	sprite->addKeyframe(TAIL_LEFT, glm::vec2(widhtProp * 2, heightProp * 1));
	sprite->addKeyframe(TAIL_LEFT, glm::vec2(widhtProp * 3, heightProp * 1));
	sprite->addKeyframe(TAIL_LEFT, glm::vec2(widhtProp * 3, heightProp * 1));
	sprite->addKeyframe(TAIL_LEFT, glm::vec2(widhtProp * 2, heightProp * 1));

	sprite->setAnimationSpeed(TAIL_RIGHT, ANIMATION_SPEED / 2);
	sprite->addKeyframe(TAIL_RIGHT, glm::vec2(widhtProp * 0, heightProp * 3));
	sprite->addKeyframe(TAIL_RIGHT, glm::vec2(widhtProp * 1, heightProp * 3));
	sprite->addKeyframe(TAIL_RIGHT, glm::vec2(widhtProp * 1, heightProp * 3));
	sprite->addKeyframe(TAIL_RIGHT, glm::vec2(widhtProp * 0, heightProp * 3));
	sprite->addKeyframe(TAIL_RIGHT, glm::vec2(widhtProp * 1, heightProp * 3));


	
	sprite->setAnimationSpeed(EXH_LEFT, ANIMATION_SPEED/2);
	sprite->addKeyframe(EXH_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(EXH_LEFT, glm::vec2(widhtProp * 1, 0.f));
	sprite->addKeyframe(EXH_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(EXH_LEFT, glm::vec2(widhtProp * 1, 0.f));
	sprite->addKeyframe(EXH_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(EXH_RIGHT, ANIMATION_SPEED/2);
	sprite->addKeyframe(EXH_RIGHT, glm::vec2(0.f, heightProp * 2));
	sprite->addKeyframe(EXH_RIGHT, glm::vec2(widhtProp * 1, heightProp * 2));
	sprite->addKeyframe(EXH_RIGHT, glm::vec2(0.f, heightProp * 2));
	sprite->addKeyframe(EXH_RIGHT, glm::vec2(widhtProp * 1, heightProp * 2));
	sprite->addKeyframe(EXH_RIGHT, glm::vec2(0.f, heightProp * 2));

	sprite->setAnimationSpeed(START_BALL_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(START_BALL_LEFT, glm::vec2(widhtProp*3, heightProp*4));
	sprite->addKeyframe(START_BALL_LEFT, glm::vec2(widhtProp*2, heightProp*4));
	sprite->addKeyframe(START_BALL_LEFT, glm::vec2(widhtProp*1, heightProp*4));
	sprite->addKeyframe(START_BALL_LEFT, glm::vec2(widhtProp*0, heightProp*4));


	sprite->setAnimationSpeed(START_BALL_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(START_BALL_RIGHT, glm::vec2(widhtProp * 0, heightProp * 5));
	sprite->addKeyframe(START_BALL_RIGHT, glm::vec2(widhtProp * 1, heightProp * 5));
	sprite->addKeyframe(START_BALL_RIGHT, glm::vec2(widhtProp * 2, heightProp * 5));
	sprite->addKeyframe(START_BALL_RIGHT, glm::vec2(widhtProp * 3, heightProp * 5));

	sprite->setAnimationSpeed(BALL, ANIMATION_SPEED);
	sprite->addKeyframe(BALL, glm::vec2(widhtProp * 0, heightProp * 6));
	sprite->addKeyframe(BALL, glm::vec2(widhtProp * 1, heightProp * 6));
	sprite->addKeyframe(BALL, glm::vec2(widhtProp * 2, heightProp * 6));
	sprite->addKeyframe(BALL, glm::vec2(widhtProp * 3, heightProp * 6));

	sprite->setAnimationSpeed(START_SECOND_LEFT, ANIMATION_SPEED/3);
	sprite->addKeyframe(START_SECOND_LEFT, glm::vec2(widhtProp * 3, heightProp * 8));
	sprite->addKeyframe(START_SECOND_LEFT, glm::vec2(widhtProp * 2, heightProp * 8));
	sprite->addKeyframe(START_SECOND_LEFT, glm::vec2(widhtProp * 1, heightProp * 8));
	sprite->addKeyframe(START_SECOND_LEFT, glm::vec2(widhtProp * 0, heightProp * 8));


	sprite->setAnimationSpeed(START_SECOND_RIGHT, ANIMATION_SPEED/3);
	sprite->addKeyframe(START_SECOND_RIGHT, glm::vec2(widhtProp * 0, heightProp * 7));
	sprite->addKeyframe(START_SECOND_RIGHT, glm::vec2(widhtProp * 1, heightProp * 7));
	sprite->addKeyframe(START_SECOND_RIGHT, glm::vec2(widhtProp * 2, heightProp * 7));
	sprite->addKeyframe(START_SECOND_RIGHT, glm::vec2(widhtProp * 3, heightProp * 7));

	sprite->setAnimationSpeed(SECOND_LEFT, ANIMATION_SPEED/3);
	sprite->addKeyframe(SECOND_LEFT, glm::vec2(widhtProp * 3, heightProp * 9));
	sprite->addKeyframe(SECOND_LEFT, glm::vec2(widhtProp * 2, heightProp * 9));
	sprite->addKeyframe(SECOND_LEFT, glm::vec2(widhtProp * 2, heightProp * 9));
	sprite->addKeyframe(SECOND_LEFT, glm::vec2(widhtProp * 2, heightProp * 9));


	sprite->setAnimationSpeed(SECOND_RIGHT, ANIMATION_SPEED/3);
	sprite->addKeyframe(SECOND_RIGHT, glm::vec2(widhtProp * 0, heightProp * 9));
	sprite->addKeyframe(SECOND_RIGHT, glm::vec2(widhtProp * 1, heightProp * 9));
	sprite->addKeyframe(SECOND_RIGHT, glm::vec2(widhtProp * 1, heightProp * 9));
	sprite->addKeyframe(SECOND_RIGHT, glm::vec2(widhtProp * 1, heightProp * 9));


	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpriteEnemy.x - 32  ), float(tileMapDispl.y + posSpriteEnemy.y -64)));

}

void Boss::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Boss::setPosition(const glm::vec2 &pos)
{
	posSpriteEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpriteEnemy.x - 32), float(tileMapDispl.y + posSpriteEnemy.y -64)));
}

void Boss::setTarget(MainPlayer *target){
	player = target;
}

void Boss::render()
{
	sprite->render();
}

void Boss::update(int deltaTime) {
	if (live > 0) {
		sprite->update(deltaTime);
		int spriteWidth = 64;
		int tileSize = map->getTileSize();
		int tileXPlayer = player->getPlayerPosition().x / tileSize;
		int tileYPlayer = player->getPlayerPosition().y / tileSize;
		int tileXEnemy = posSpriteEnemy.x / tileSize;
		int tileYEnemy = posSpriteEnemy.y / tileSize;
		bool playerInRange = (abs(tileXEnemy - tileXPlayer) < 10);

		//si estamos en progreso de atacar hacemos daño en nujestra area
		

		if (live < 40) fase3();
		else if (live < 70) {
			if (attacking) {
				if (sprite->getCurrentNumKeyFrame() == 3) {
					attacking = false;
					if (bLeft) sprite->changeAnimation(STAND_LEFT);
					else sprite->changeAnimation(STAND_LEFT);
				}

				if (bLeft) {
					for (int x = 0; x < 2; ++x) {
						for (int y = -1; y < 2; ++y) {
							int xDmgOgre = tileXEnemy - x;
							int yDmgOgre = tileYEnemy + y;
							if (tileXPlayer == xDmgOgre && tileYPlayer == yDmgOgre) player->reciveDMG(5);
						}
					}
				}
				else {
					for (int x = 0; x < 2; ++x) {
						for (int y = -1; y < 2; ++y) {
							int xDmgOgre = tileXEnemy + x;
							int yDmgOgre = tileYEnemy + y;
							if (tileXPlayer == xDmgOgre && tileYPlayer == yDmgOgre) player->reciveDMG(5);
						}
					}
				}
			}
			else if (playerInRange) fase2();
		}
		else { 
			if (attacking) {
				if (sprite->getCurrentNumKeyFrame() == 3) {
					attacking = false;
					if (bLeft) sprite->changeAnimation(STAND_LEFT);
					else sprite->changeAnimation(STAND_LEFT);
				}

				if (bLeft) {
					for (int x = 0; x < 2; ++x) {
						for (int y = -1; y < 2; ++y) {
							int xDmgOgre = tileXEnemy - x;
							int yDmgOgre = tileYEnemy + y;
							if (tileXPlayer == xDmgOgre && tileYPlayer == yDmgOgre) player->reciveDMG(5);
						}
					}
				}
				else {
					for (int x = 0; x < 2; ++x) {
						for (int y = -1; y < 2; ++y) {
							int xDmgOgre = tileXEnemy + x;
							int yDmgOgre = tileYEnemy + y;
							if (tileXPlayer == xDmgOgre && tileYPlayer == yDmgOgre) player->reciveDMG(5);
						}
					}
				}
			}
			else if (playerInRange) followAndAttckPlayer();
		}  
		
		glm::ivec2 spritePos = posSpriteEnemy;
		if (!map->collisionMoveDown(spritePos + 5, glm::ivec2(spriteWidth, 64), &posSpriteEnemy.y, bLeft, 0)) {
			posSpriteEnemy.y += 2;
		}
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posSpriteEnemy.x - 32), float(tileMapDispl.y + posSpriteEnemy.y - 64)));
	}
}


void Boss::followAndAttckPlayer() {
	int spriteWidth = 64;
	int tileSize = map->getTileSize();
	int tileXPlayer = player->getPlayerPosition().x / tileSize;
	int tileYPlayer = player->getPlayerPosition().y / tileSize;
	int tileXEnemy = posSpriteEnemy.x / tileSize;
	int tileYEnemy = posSpriteEnemy.y / tileSize;
	int xDist = tileXPlayer - tileXEnemy;
	if ((abs(xDist) < 2) || (!bLeft && abs(xDist) < 2)) {
		attacking = true;
		if (bLeft) {
			if(nextBool(0.6))sprite->changeAnimation(ATTACKING_LEFT);
			else sprite->changeAnimation(TAIL_LEFT);
		}
		else {
			if (nextBool(0.6))sprite->changeAnimation(ATTACKING_RIGHT);
			else sprite->changeAnimation(TAIL_RIGHT);
		}
	}
	else if (xDist < 0) {
		bLeft = true;
		if (!map->collisionMoveLeft(posSpriteEnemy, glm::ivec2(spriteWidth, 64))) {
			if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			posSpriteEnemy.x -= 2;
		}
		else  sprite->changeAnimation(STAND_LEFT);
	}
	else {
		bLeft = false;
		if (!map->collisionMoveRight(posSpriteEnemy, glm::ivec2(spriteWidth, 64))) {
			if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			posSpriteEnemy.x += 2;
		}
		else sprite->changeAnimation(STAND_RIGHT);
	}
}

void Boss::fase2() {
	int spriteWidth = 64;
	int tileSize = map->getTileSize();
	int tileXPlayer = player->getPlayerPosition().x / tileSize;
	int tileYPlayer = player->getPlayerPosition().y / tileSize;
	int tileXEnemy = posSpriteEnemy.x / tileSize;
	int tileYEnemy = posSpriteEnemy.y / tileSize;
	int xDist = tileXPlayer - tileXEnemy;
	if (fase < 2) {
		fase = 2;
		if (bLeft) sprite->changeAnimation(START_SECOND_LEFT);
		else sprite->changeAnimation(START_SECOND_RIGHT);
	}
	else if (sprite->animation() == START_SECOND_LEFT || sprite->animation() == START_SECOND_RIGHT) {
		if (sprite->getCurrentNumKeyFrame() == 3) {
			if (bLeft) sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (numAtF2 == 5) {
			if (bLeft) sprite->changeAnimation(EXH_LEFT);
			else sprite->changeAnimation(EXH_RIGHT);
			numAtF2 = 0;
	}
	else if (sprite->animation() == EXH_LEFT || sprite->animation() == EXH_RIGHT) {
		if (sprite->getCurrentNumKeyFrame() == 4) {
			if (bLeft) sprite->changeAnimation(START_BALL_LEFT);
			else sprite->changeAnimation(START_BALL_RIGHT);
		}
	}
	else if ((abs(xDist) < 2) || (!bLeft && abs(xDist) < 3)) {
		attacking = true;
		numAtF2++;
		if (bLeft) sprite->changeAnimation(SECOND_LEFT);
		else sprite->changeAnimation(SECOND_RIGHT);
	}
	else if (xDist < 0) {
		bLeft = true;
		if (!map->collisionMoveLeft(posSpriteEnemy, glm::ivec2(spriteWidth, 64))) {
			if (sprite->animation() != MOVE_LEFT ) sprite->changeAnimation(MOVE_LEFT);
			posSpriteEnemy.x -= 2;
		}
		else  sprite->changeAnimation(STAND_LEFT);
	}
	else {
		bLeft = false;
		if (!map->collisionMoveRight(posSpriteEnemy, glm::ivec2(spriteWidth, 64))) {
			if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			posSpriteEnemy.x += 2;
		}
		else sprite->changeAnimation(STAND_RIGHT);
	}
}

void Boss::fase3() {
	int spriteWidth = 64;
	int tileSize = map->getTileSize();
	int tileXPlayer = player->getPlayerPosition().x / tileSize;
	int tileYPlayer = player->getPlayerPosition().y / tileSize;
	int tileXEnemy = posSpriteEnemy.x / tileSize;
	int tileYEnemy = posSpriteEnemy.y / tileSize;
	bool playerInRange = (abs(tileXEnemy - tileXPlayer) < 10);

	if (fase < 3) {
		fase = 3;
		if (bLeft) sprite->changeAnimation(START_BALL_RIGHT);
		else sprite->changeAnimation(START_BALL_RIGHT);
	}
	else if (sprite->animation() == EXH_LEFT || sprite->animation() == EXH_RIGHT) {
		if (sprite->getCurrentNumKeyFrame() == 4) {
			if (bLeft) sprite->changeAnimation(START_BALL_LEFT);
			else sprite->changeAnimation(START_BALL_RIGHT);
		}
	}
	else if (sprite->animation() == START_BALL_LEFT || sprite->animation() == START_BALL_RIGHT) {
		if (sprite->getCurrentNumKeyFrame() == 3) sprite->changeAnimation(BALL);
	}
	else if (bLeft && !map->collisionMoveLeft(posSpriteEnemy, glm::ivec2(spriteWidth, 64))) { //Moure esquerra
		bLeft = true;
		posSpriteEnemy.x -= 2;
	}
	else {
		if (bLeft) {
			bLeft = false;
			if (nextBool(0.4)) sprite->changeAnimation(EXH_RIGHT);
		}
		else {
			posSpriteEnemy.x += 2;
			if (map->collisionMoveRight(posSpriteEnemy, glm::ivec2(spriteWidth, 64))) { 	//si hi ha colisio, ens parem
				posSpriteEnemy.x -= 2;
				bLeft = true;
				if (nextBool(0.4)) sprite->changeAnimation(EXH_LEFT);
			}
		}
	}

	if (sprite->animation() == BALL) {
		if (tileXPlayer == tileXEnemy && tileYPlayer == tileYEnemy) player->reciveDMG(5);
		else if (bLeft) {
			if (tileXPlayer == (tileXEnemy-1) && tileYPlayer == tileYEnemy) player->reciveDMG(5);
		}
		else{
			if (tileXPlayer == (tileXEnemy+1) && tileYPlayer == tileYEnemy) player->reciveDMG(5);
		}
	}
}


bool Boss::nextBool(double probability)
{
	return rand() <  probability * ((double)RAND_MAX + 1.0);
}

void Boss::reciveDmg(int dmg , glm::ivec2 dmgAt) {
	int spriteWidth = 64;
	int tileSize = map->getTileSize();
	int dmgX = dmgAt.x / tileSize;
	int dmgY = dmgAt.y / tileSize;
	int tileXEnemy = posSpriteEnemy.x / tileSize;
	int tileYEnemy = posSpriteEnemy.y / tileSize;
	bool playerInRange = (abs(tileXEnemy - dmgX) < 5);
	if (playerInRange && sprite->animation() != BALL) {
		if (bLeft) {
			for (int x = 0; x < 2; ++x) {
				for (int y = -1; y < 2; ++y) {
					int xEn = tileXEnemy - x;
					int yEn = tileYEnemy + y;
					if (dmgX == xEn && dmgY == yEn) live-=dmg;
				}
			}
		}
		else {
			for (int x = 0; x < 2; ++x) {
				for (int y = -1; y < 2; ++y) {
					int xEn = tileXEnemy + x;
					int yEn = tileYEnemy + y;
					if (dmgX == xEn && dmgY == yEn) live-=dmg;
				}
			}

		}
	}
	cout << "Boss liv" << live << endl;
}