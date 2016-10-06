#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 90
#define FALL_STEP 4
#define HEIGHT 64
#define WIDTH 64
#define ANIMATION_SPEED 8
#define WALKINGSIZEVEC  glm::vec2(widhtProp*2.1, heightProp*3)
#define DIGSIZEVEC glm::vec2(widhtProp * 3 + widhtProp * 0.8, heightProp * 3 + 0.5 * heightProp)

enum SpriteSizes {
	WALKINGSIZE, DIGSIZE
};
enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ARM1_LEFT, ARM1_RIGHT
};

void MainPlayer::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	heightProp = 1.f / 31.f;
	widhtProp = 1.f / 47.f;
	double yoffset = 1.f /32.f;
	bJumping = false;
	bLeft = true;
	spritesheet.loadFromFile("images/Especials_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	sprite = Sprite::createSprite(glm::ivec2(WIDTH, HEIGHT), WALKINGSIZEVEC, &spritesheet, &shaderProgram);
	spriteSize = WALKINGSIZE;
	sprite->setNumberAnimations(8);

	//caminar
	sprite->setAnimationSpeed(STAND_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(widhtProp * 3 * 5, 3 * heightProp));

	sprite->setAnimationSpeed(MOVE_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));    
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 3, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 3 * 2, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 3 * 3, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 3 * 4, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(widhtProp * 3 * 5, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3 * heightProp));	//Corrent    
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 3 , 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 3 * 2, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 3 * 3, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 3 * 4, 3 * heightProp));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(widhtProp * 3 * 5, 3 * heightProp));

	//WEAPON1 (11*2)
	double height = 6 * heightProp + 0.5 * heightProp;
	sprite->setAnimationSpeed(ARM1_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 2, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 3, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 4, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 5, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 6, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 7, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 8, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 9, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widhtProp * 3 * 10, height));

	height = 10 * heightProp + 0.5*heightProp;
	sprite->setAnimationSpeed(ARM1_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 2, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 3, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 4, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 5, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 6, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 7, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 8, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 9, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widhtProp * 3 * 10, height));

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void MainPlayer::update(int deltaTime) {

	sprite->update(deltaTime);
	//SPRITE
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) { //Moure dreta
		checkWalkingSize();
		bLeft = true;
		if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(WIDTH, HEIGHT))) {
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) { //Moure esquerre
		checkWalkingSize();
		bLeft = false;
		if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(WIDTH, HEIGHT))) { 	//si hi ha colisio, ens parem
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getKey('c') ){
		spriteDig();
	}
	else if (Game::instance().getKey('p')) {
		map->addMaterial(posPlayer.x, posPlayer.y, DIAMOND);
	}
	else {	//aturat
		checkWalkingSize();
		if (sprite->animation() == MOVE_RIGHT) {
			sprite->changeAnimation(STAND_RIGHT);
		}
		else if(sprite->animation() != STAND_RIGHT) spriteStandLeft();
	}

	//POSICIO Y
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

void MainPlayer::checkWalkingSize() {
	if (spriteSize != WALKINGSIZE) {
		spriteSize = WALKINGSIZE;
		sprite->setSize(WALKINGSIZEVEC);
	}
}

void MainPlayer::spriteDig() {
	if (spriteSize == DIGSIZE) {
		if (bLeft) sprite->changeAnimation(ARM1_LEFT);
		else sprite->changeAnimation(ARM1_RIGHT);
	}
	else {
		spriteSize = DIGSIZE;
		sprite->setSize(DIGSIZEVEC);
		if(bLeft) sprite->changeAnimation(ARM1_LEFT);
		else sprite->changeAnimation(ARM1_RIGHT);
	}
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




