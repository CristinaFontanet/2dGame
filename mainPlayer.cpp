#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 2
#define JUMP_HEIGHT 90
#define FALL_STEP 4
#define HEIGHTWALK 64
#define WIDTHWALK 32
#define SPRITEMARGIN 32
#define ANIMATION_SPEED 8
#define ALLEGRO_PI        3.14159265358979323846
#define RANGE 2

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ARM1_LEFT,ARM1_LEFT_BOT, ARM1_RIGHT, ARM1_RIGHT_BOT, ATAC_LEFT
};


void MainPlayer::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, CEGUI::Window* inventoryWindow) {
	animationInProgress = false;
	setUpInventory(inventoryWindow);
	heightProp = 1.f / 32.f;
	widhtProp = 1.f / 48.f;
	double yoffset = 1.f /32.f;
	bJumping = false;
	lastDeltaTime = 2;
	bLeft = true;
	live = 6;
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
	sprite->setAnimationSpeed(ARM1_LEFT_BOT, ANIMATION_SPEED*1.5);
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

	sprite->setAnimationSpeed(ARM1_LEFT, ANIMATION_SPEED*1.5);
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
	sprite->setAnimationSpeed(ARM1_RIGHT_BOT, ANIMATION_SPEED*1.5);
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

	sprite->setAnimationSpeed(ARM1_RIGHT, ANIMATION_SPEED*1.5);
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 8, height));

	spritesheetAtac.loadFromFile("images/main_atac.png", TEXTURE_PIXEL_FORMAT_RGBA);
	widhtProp = 1.0 / 59.f;
	heightProp = 1.0 / 10.f;
	spriteAtac = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widhtProp * 6, heightProp * 4), &spritesheetAtac, &shaderProgram);
	spriteAtac->setAnimationSpeed(ATAC_LEFT, ANIMATION_SPEED*1.5);
	spriteAtac->addKeyframe(ATAC_LEFT, glm::vec2(0.f, 0.f));
	spriteAtac->changeAnimation(ATAC_LEFT);


	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteAtac->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	height = HEIGHTWALK;
	spriteWidth = WIDTHWALK;
}

void MainPlayer::equipItem(int num) {
	equipedItem->setSelected(false);
	equipedItem = &inventory[num];
	equipedItem->setSelected(true);
}

bool MainPlayer::isDiggingLateral() {
	if (sprite->animation() == ARM1_LEFT || sprite->animation() == ARM1_RIGHT ) return true;
	else return false;
}
bool MainPlayer::isDiggingBottom() {
	if (sprite->animation() == ARM1_LEFT_BOT ||  sprite->animation() == ARM1_RIGHT_BOT) return true;
	else return false;
}

void MainPlayer::mouseClick(int x, int y) {
	pair<int, int> offset = Game::instance().getOffsetCamera();
	lastXclick = x + offset.first;
	lastYclick = y + offset.second;
	if (equipedItem->type == PICKAXE) digAnimation();
	if (equipedItem->type == MATERIAL) putMaterial();
}

void MainPlayer::update(int deltaTime) {

	sprite->update(deltaTime);
	spriteAtac->update(deltaTime);
	
	if (isDiggingBottom() || isDiggingLateral()) {
		if (isDiggingLateral()) {
			if (sprite->getNumKeyFrameMissing() == 8) {
				if (sprite->animation() == ARM1_LEFT)sprite->changeAnimation(STAND_LEFT);
				else sprite->changeAnimation(STAND_RIGHT);
				int material = map->dig(lastXclick, lastYclick, posPlayer.x, posPlayer.y + spriteWidth / 2, RANGE,equipedItem->dmg);
				materialDigged(material);
				animationInProgress = false;
			}
		}
		else if (isDiggingBottom()) {
			if (sprite->getNumKeyFrameMissing() == 10) {
				if (sprite->animation() == ARM1_LEFT_BOT)sprite->changeAnimation(STAND_LEFT);
				else sprite->changeAnimation(STAND_RIGHT);
				int material = map->dig(lastXclick, lastYclick, posPlayer.x, posPlayer.y + spriteWidth / 2, RANGE, equipedItem->dmg);
				materialDigged(material);
				animationInProgress = false;
			}
		}
	} 
	else {
		switch (Game::instance().getPressedKey()) {
		case '1':
			equipedItem = &inventory[0];
			break;
		case '2':
			equipedItem = &inventory[1];
			break;
		}
	}
	
	if(!animationInProgress) {
		spriteWidth = 32;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) || Game::instance().getKey('a')) { //Moure dreta
			bLeft = true;
			if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(spriteWidth, 64))) {
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) || Game::instance().getKey('d')) { //Moure esquerre
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
			int posPlayerIniY = posPlayer.y;
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			glm::ivec2 spritePos = posPlayer;
			//48 = 64/4*3 per l'al�ada real del sprite xq no funciona 48????
			if (map->collisionMoveUp(spritePos, glm::ivec2(spriteWidth,50), &posPlayer.y, bLeft, marg)) {
				bJumping = false;
			}
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(spritePos, glm::ivec2(spriteWidth, 64), &posPlayer.y, bLeft, marg);
			}
		}
	}
	else {
		posPlayer.y += FALL_STEP;
		glm::ivec2 spritePos = posPlayer;
		if (map->collisionMoveDown(spritePos, glm::ivec2(spriteWidth, 64), &posPlayer.y, bLeft, marg)) {
			if (Game::instance().getSpecialKey(GLUT_KEY_UP) || Game::instance().getKey('w') || Game::instance().getKey(32)) {
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteAtac->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void MainPlayer::setUpInventory(CEGUI::Window* inventoryWindow) {
	inventory = vector<Item>(20);
	inventory[0] = Item(PICKAXE, WOOD, 1, 1, inventoryWindow);
	inventory[1] = Item(MATERIAL, TUSK, 0, 0, inventoryWindow);
	inventory[2] = Item(MATERIAL, WOOD, 0, 0, inventoryWindow);
	inventory[3] = Item(MATERIAL, ROCK, 0, 0, inventoryWindow);
	inventory[4] = Item(MATERIAL, COAL, 0, 0, inventoryWindow);
	inventory[5] = Item(MATERIAL, GOLD, 0, 0, inventoryWindow);
	inventory[6] = Item(MATERIAL, DIAMOND, 0, 0, inventoryWindow);
	equipedItem = &inventory[0];
	equipedItem->setSelected(true);
}

void MainPlayer::materialDigged(int material) {
	switch (material) {
	case TUSK:
		inventory[1].addItem();
		break;
	case WOOD:
		inventory[2].addItem();
		break;
	case ROCK:
		inventory[3].addItem();
		break;
	case COAL:
		inventory[4].addItem();
		break;
	case GOLD:
		inventory[5].addItem();
		break;
	case DIAMOND:
		inventory[6].addItem();
		break;
	default:
		int i = 2;
		break;
	}
}

void MainPlayer::spriteStandLeft() {
		sprite->changeAnimation(STAND_LEFT);
}

void MainPlayer::render()
{
	//sprite->render();
	spriteAtac->render();
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


void MainPlayer::digAnimation() {
	spriteWidth = 64;
	animationInProgress = true;
	if ((posPlayer.y + spriteWidth) < lastYclick) {
		if (posPlayer.x  > lastXclick && sprite->animation() != ARM1_LEFT_BOT) sprite->changeAnimation(ARM1_LEFT_BOT);
		else if (posPlayer.x < lastXclick && sprite->animation() != ARM1_RIGHT_BOT) sprite->changeAnimation(ARM1_RIGHT_BOT);
	}
	else {
		if (posPlayer.x > lastXclick && sprite->animation() != ARM1_LEFT) sprite->changeAnimation(ARM1_LEFT);
		else if (posPlayer.x < lastXclick && sprite->animation() != ARM1_RIGHT) sprite->changeAnimation(ARM1_RIGHT);

	}
}

void MainPlayer::putMaterial() {
	if (equipedItem->getAmount() > 0) {
		if (map->addMaterial(lastXclick, lastYclick, posPlayer.x, posPlayer.y + spriteWidth / 2, equipedItem->element, RANGE * 2)) {
			equipedItem->reduceAmount();
		}
	}
	else {
		//TODO: avisar que no queda material
	}
}