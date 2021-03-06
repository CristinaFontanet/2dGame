
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MainPlayer.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 45
#define FALL_STEP 4
#define HEIGHTWALK 64
#define WIDTHWALK 32
#define SPRITEMARGIN 32
#define ANIMATION_SPEED 8
#define ALLEGRO_PI        3.14159265358979323846
#define RANGE 2
#define ATTACKLEFTOFFSITE 32

enum SpriteMoves {
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ARM1_LEFT,ARM1_LEFT_BOT, ARM1_RIGHT, ARM1_RIGHT_BOT, BELL_LEFT,BELL_RIGHT
};
enum AttackSprites {
	ATTACK_LEFT, ATTACK_RIGHT, QUIET
};

void MainPlayer::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, CEGUI::Window* inventoryWindow, CEGUI::Window* livesWindiowP) {
	live = 100;
	jumpMod = 1;
	animationInProgress = false;
	bDamage = false;
	setUpInventory(inventoryWindow);
	setUpLives(livesWindiowP);
	heightProp = 1.f / 32.f;
	widhtProp = 1.f / 48.f;
	double yoffset = 1.f /32.f;
	bJumping = false;
	lastDeltaTime = 2;
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
	sprite->setAnimationSpeed(ARM1_LEFT_BOT, ANIMATION_SPEED*1.5);
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 8, height));
	sprite->addKeyframe(ARM1_LEFT_BOT, glm::vec2(widht * 8, height));

	sprite->setAnimationSpeed(ARM1_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_LEFT, glm::vec2(widht * 6, height));

	height = 12 * heightProp;
	sprite->setAnimationSpeed(ARM1_RIGHT_BOT, ANIMATION_SPEED*1.5);
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 8, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(widht, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(0.f, height));
	sprite->addKeyframe(ARM1_RIGHT_BOT, glm::vec2(0.f, height));

	sprite->setAnimationSpeed(ARM1_RIGHT, ANIMATION_SPEED*1.5);
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 8, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 7, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 6, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 5, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 4, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 3, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 2, height));
	sprite->addKeyframe(ARM1_RIGHT, glm::vec2(widht * 2, height));

	height = heightProp * 6*4;
	sprite->setAnimationSpeed(BELL_LEFT, ANIMATION_SPEED);
	sprite->addKeyframe(BELL_LEFT, glm::vec2(0.f, height));
	sprite->addKeyframe(BELL_LEFT, glm::vec2(widht, height));
	sprite->addKeyframe(BELL_LEFT, glm::vec2(0.f, height));
	sprite->addKeyframe(BELL_LEFT, glm::vec2(widht, height));
	sprite->addKeyframe(BELL_LEFT, glm::vec2(0.f, height));
	sprite->addKeyframe(BELL_LEFT, glm::vec2(widht, height));

	height = heightProp * 7*4;
	sprite->setAnimationSpeed(BELL_RIGHT, ANIMATION_SPEED);
	sprite->addKeyframe(BELL_RIGHT, glm::vec2(0.f, height));
	sprite->addKeyframe(BELL_RIGHT, glm::vec2(widht, height));
	sprite->addKeyframe(BELL_RIGHT, glm::vec2(0.f, height));
	sprite->addKeyframe(BELL_RIGHT, glm::vec2(widht, height));
	sprite->addKeyframe(BELL_RIGHT, glm::vec2(0.f, height));
	sprite->addKeyframe(BELL_RIGHT, glm::vec2(widht, height));

////////////////////////////////////////////////////////////////////////////
	spritesheetInvincible.loadFromFile("images/Especials_1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteInvincible = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widhtProp * 4, heightProp * 4), &spritesheet, &shaderProgram);
	spriteInvincible->setNumberAnimations(1);
	spriteInvincible->setAnimationSpeed(0, ANIMATION_SPEED);
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	spriteInvincible->addKeyframe(0, glm::vec2(widht * 6, 0.f));
	
	spritesheetAtac.loadFromFile("images/main_atac.png", TEXTURE_PIXEL_FORMAT_RGBA);
	widhtProp = 1.0 / 48.f;
	heightProp = 1.0 / 10.f;
	widht = widhtProp * 6;
	spriteAtac = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widhtProp * 6, heightProp * 4), &spritesheetAtac, &shaderProgram);
	spriteAtac->setNumberAnimations(10);
	spriteAtac->setAnimationSpeed(ATTACK_LEFT, ANIMATION_SPEED);
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 6, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 5, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 4, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 3, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 2, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(0.f, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 7, 0.f));
	spriteAtac->addKeyframe(ATTACK_LEFT, glm::vec2(widht * 7, 0.f));

	height = heightProp * 5;
	spriteAtac->setAnimationSpeed(ATTACK_RIGHT, ANIMATION_SPEED);
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(0.f, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 2, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 3, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 4, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 5, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 6, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 7, height));
	spriteAtac->addKeyframe(ATTACK_RIGHT, glm::vec2(widht * 7, height));

	spriteAtac->setAnimationSpeed(QUIET, ANIMATION_SPEED);
	spriteAtac->addKeyframe(QUIET, glm::vec2(0.f, height));

	spriteState = NORMAL;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteAtac->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	height = HEIGHTWALK;
	spriteWidth = WIDTHWALK;
	configSounds();
}

void MainPlayer::equipItem(int num) {
	equipedItem->setSelected(false);
	equipedItem = &inventory[num];
	equipedItem->setSelected(true);
}

bool MainPlayer::isAttacking() {
	return spriteState == ATTACKING;
}


bool MainPlayer::isBellAnimationInProgress() {
	if (sprite->animation() == BELL_LEFT || sprite->animation() == BELL_RIGHT) return true;
	else return false;
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
		else if (equipedItem->type == SWORD) attackAnimation();
		else if (equipedItem->type == MATERIAL) putMaterial();
		else if (equipedItem->type == BELLITEM && getBell()->amount > 0) bellAnimation();
	
}
void MainPlayer::update(int deltaTime) {
		spriteInvincible->update(deltaTime);
		spriteAtac->update(deltaTime);
		sprite->update(deltaTime);
		if (bDamage) {
			//	spriteInvincible->changeAnimation(INVINCIBLE);
			int i = spriteInvincible->getCurrentNumKeyFrame();
			if (spriteInvincible->getCurrentNumKeyFrame() == 8) {
				bDamage = false;
			}
		}

		if (isBellAnimationInProgress()) {
			if (sprite->getCurrentNumKeyFrame() == 5) {
				if (sprite->animation() == BELL_LEFT) sprite->changeAnimation(STAND_LEFT);
				else sprite->changeAnimation(STAND_RIGHT);
				animationInProgress = false;
				Game::instance().proceedToBoss();
			}
		}

		if (isDiggingBottom() || isDiggingLateral()) {
			if (isDiggingLateral()) {
				if (sprite->getCurrentNumKeyFrame() == 7) {
					if (sprite->animation() == ARM1_LEFT)sprite->changeAnimation(STAND_LEFT);
					else sprite->changeAnimation(STAND_RIGHT);
					int material = map->dig(lastXclick, lastYclick, posPlayer.x, posPlayer.y + spriteWidth / 2, RANGE, equipedItem->dmg);
					materialDigged(material);
					animationInProgress = false;
				}
			}
			else if (isDiggingBottom()) {
				if (sprite->getCurrentNumKeyFrame() == 8) {
					if (sprite->animation() == ARM1_LEFT_BOT)sprite->changeAnimation(STAND_LEFT);
					else sprite->changeAnimation(STAND_RIGHT);
					int material = map->dig(lastXclick, lastYclick, posPlayer.x, posPlayer.y + spriteWidth / 2, RANGE, equipedItem->dmg);
					materialDigged(material);
					animationInProgress = false;
				}
			}
		}
		else if (isAttacking() && spriteAtac->getCurrentNumKeyFrame() == 8) {
			spriteState = NORMAL;
			spriteAtac->changeAnimation(QUIET);
			if (bLeft)sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
			animationInProgress = false;
		}

		if (!animationInProgress) {
			spriteWidth = 32;
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) || Game::instance().getKey('a') || Game::instance().getKey('A')) { //Moure dreta
				bLeft = true;
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
				posPlayer.x -= 2;
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(spriteWidth, 64))) {
					posPlayer.x += 2;
					sprite->changeAnimation(STAND_LEFT);
				}
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) || Game::instance().getKey('d') || Game::instance().getKey('D')) { //Moure esquerre
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
			jumpAngle += JUMP_ANGLE_STEP - (0.5*jumpMod);
			if (jumpAngle == 180) {
				bJumping = false;
			}
			else {
				int posPlayerIniY = posPlayer.y;
				posPlayer.y = int(startY - (JUMP_HEIGHT + (32 * jumpMod)) * sin(3.14159f * jumpAngle / 180.f));
				glm::ivec2 spritePos = posPlayer;
				//48 = 64/4*3 per l'al�ada real del sprite xq no funciona 48????
				if (map->collisionMoveUp(spritePos, glm::ivec2(spriteWidth, 50), &posPlayer.y, bLeft, marg)) {
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
				if (Game::instance().getSpecialKey(GLUT_KEY_UP) || Game::instance().getKey('w') || Game::instance().getKey('W') || Game::instance().getKey(32)) {
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		if (bLeft) spriteAtac->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - ATTACKLEFTOFFSITE), float(tileMapDispl.y + posPlayer.y)));
		else spriteAtac->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

int MainPlayer::getAmountItem(int i) {
	return inventory[i].getAmount();
}


void MainPlayer::combineInventory(MainPlayer* mPlayer) {
	for (int i = 0; i < inventory.size(); ++i) {
		inventory[i].setAmount(mPlayer->getAmountItem(i));
	}
	getSword()->setElement(mPlayer->getSword()->getElement());
	getPeak()->setElement(mPlayer->getPeak()->getElement());
}


void MainPlayer::setUpInventory(CEGUI::Window* inventoryWindow) {
	inventory = vector<Item>(9);
	inventory[0] = Item(PICKAXE, WOOD, 1, 1, inventoryWindow);
	inventory[1] = Item(SWORD, TUSK, 3, 1, inventoryWindow);
	inventory[2] = Item(MATERIAL, TUSK, 0, 0, inventoryWindow);
	inventory[3] = Item(MATERIAL, ROCK, 0, 0, inventoryWindow);
	inventory[4] = Item(MATERIAL, COAL, 0, 0, inventoryWindow);
	inventory[5] = Item(MATERIAL, GOLD, 0, 0, inventoryWindow);
	inventory[6] = Item(MATERIAL, DIAMOND, 0, 0, inventoryWindow);
	inventory[7] = Item(BELLITEM, 0, 0,0, inventoryWindow);
	inventory[8] = Item(BELLSPECIAL, 0, 0, 0, inventoryWindow);

	equipedItem = &inventory[0];
	equipedItem->setSelected(true);
}

Item* MainPlayer::getSword() {
	return &inventory[1];
}

Item* MainPlayer::getBell() {
	return &inventory[7];
}

Item* MainPlayer::getPeak() {
	return &inventory[0];
}
Item* MainPlayer::getDiamond() {
	return &inventory[6];
}

Item* MainPlayer::getRock() {
	return &inventory[3];
}

Item* MainPlayer::getGold() {
	return &inventory[5];
}

Item* MainPlayer::getSpecialItem() {
	return &inventory[8];
}

void MainPlayer::materialDigged(int material) {
	switch (material) {
	case TUSK:
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
	case BELL:
		inventory[8].addItem();
		Game::instance().helpGetOut();
		break;
	default:
		break;
	}
}

void MainPlayer::spriteStandLeft() {
		sprite->changeAnimation(STAND_LEFT);
}

void MainPlayer::render() {
	if (bDamage && spriteInvincible->getCurrentNumKeyFrame() % 2 == 0) {
		spriteInvincible->render();
	}
	else {
		switch (spriteState) {
		case ATTACKING:
			spriteAtac->render();
			break;
		default:
			sprite->render();
			break;
		}
	}
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

glm::vec2 MainPlayer::getPlayerPosition() {
	return posPlayer;
}

void MainPlayer::setUpLives(CEGUI::Window *livesWindowP) {
	livesWindow = livesWindowP;
	windHeart1 = livesWindow->getChild("Image1");
	windHeart2 = livesWindow->getChild("Image2");
	windHeart3 = livesWindow->getChild("Image3");
	setLives(live);
}

void MainPlayer::setLives(int numLives) {
	if (numLives <= 33) {
		if (numLives > 16) windHeart1->setProperty("Image", "spritesheet_tiles/HeartFull");
		else if (numLives <= 16) windHeart1->setProperty("Image", "spritesheet_tiles/HeartHalf");
		else  windHeart1->setProperty("Image", "spritesheet_tiles/HeartEmpty");
		windHeart2->setProperty("Image", "spritesheet_tiles/HeartEmpty");
		windHeart3->setProperty("Image", "spritesheet_tiles/HeartEmpty");
	}
	else {
		windHeart1->setProperty("Image", "spritesheet_tiles/HeartFull");
		if (numLives <= 66) {
			if(numLives > 50 ) windHeart2->setProperty("Image", "spritesheet_tiles/HeartFull");
			else if (numLives <= 50) windHeart2->setProperty("Image", "spritesheet_tiles/HeartHalf");
			else  windHeart2->setProperty("Image", "spritesheet_tiles/HeartEmpty");
			windHeart3->setProperty("Image", "spritesheet_tiles/HeartEmpty");
		}
		else {
			windHeart2->setProperty("Image", "spritesheet_tiles/HeartFull");
			if (numLives < 100) {
				if(numLives > 83) windHeart3->setProperty("Image", "spritesheet_tiles/HeartFull");
				else if (numLives <= 83) windHeart3->setProperty("Image", "spritesheet_tiles/HeartHalf");
				else windHeart3->setProperty("Image", "spritesheet_tiles/HeartEmpty");
			}
			else  windHeart3->setProperty("Image", "spritesheet_tiles/HeartFull");
		}
	}
}

void MainPlayer::setHealth(int l) {
	live = l;
	setLives(live);
}
int MainPlayer::getLives() {
	return live;
}

void MainPlayer::attackAnimation() {
	spriteWidth = 64;
	if (!animationInProgress) {
		animationInProgress = true;
		spriteState = ATTACKING;
		glm::ivec2 auxPos = posPlayer;
		if (bLeft && spriteAtac->animation() != ATTACK_LEFT) {
			spriteAtac->changeAnimation(ATTACK_LEFT);
			for (int x = 0; x < 64; x += 32) {
				for (int y = -32; y < 32; y += 32) {
					auxPos.x = posPlayer.x - x;
					auxPos.y = posPlayer.y + y;
					if(Game::instance().dmgEnnemys(equipedItem->dmg, auxPos)) break;
				}
			}

		}
		else if (!bLeft && spriteAtac->animation() != ATTACK_RIGHT) {
			spriteAtac->changeAnimation(ATTACK_RIGHT);
			for (int x = 0; x < 64; x += 32) {
				for (int y = -32; y < 32; y += 32) {
					auxPos.x = posPlayer.x + x;
					auxPos.y = posPlayer.y + y;
					if (Game::instance().dmgEnnemys(equipedItem->dmg, auxPos)) break;
				}
			}
		}
	}
	else {
		int i;
	}

}
void MainPlayer::bellAnimation() {
	spriteWidth = 64;
	animationInProgress = true;
	system->playSound(bellSound, 0, true, &playerChannel);
	playerChannel->setPaused(false);
	if (posPlayer.x > lastXclick && sprite->animation() != BELL_LEFT) sprite->changeAnimation(BELL_LEFT);
	else if (posPlayer.x < lastXclick && sprite->animation() != BELL_RIGHT) sprite->changeAnimation(BELL_RIGHT);
	//TODO: so campana
//	system->playSound(digSound, 0, true, &playerChannel);
	playerChannel->setPaused(false);
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
	system->playSound(digSound, 0, true, &playerChannel);
	playerChannel->setPaused(false);
}

void MainPlayer::putMaterial() {
	if (equipedItem->getAmount() > 0) {
		if (map->addMaterial(lastXclick, lastYclick, posPlayer.x, posPlayer.y + spriteWidth / 2, equipedItem->element, RANGE * 2)) {
			equipedItem->reduceAmount(1);
		}
	}
	else {
		//TODO: avisar que no queda material
	}
}

void MainPlayer::reciveDMG(int dmg) {
	//afegir if animacio de "mal" no fer dmg
	if (!bDamage) {
		bDamage = true;
		spriteInvincible->changeAnimation(0);
		live -= dmg;
		setLives(live);

		system->playSound(dmgSound, 0, true, &playerChannel);
		playerChannel->setPaused(false);
		if (live <= 0) {
			Game::instance().noHP();
		}
	}
}

void MainPlayer::heal(int heal) {
	live += heal;
	setLives(live);
	cout << "Remaining: " << live << endl;
}

void MainPlayer::configSounds() {
	system = Game::instance().getSoundSystem();
	system->createSound("sounds/punched.wav", FMOD_2D, 0, &dmgSound);
	system->createSound("sounds/dig.wav", FMOD_2D, 0, &digSound);
	system->createSound("sounds/bell.wav", FMOD_2D, 0, &bellSound);

}

void MainPlayer::setJumpMod(int mod) {
	jumpMod = mod;
}