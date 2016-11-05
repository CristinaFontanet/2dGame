#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "SceneMain.h"
#include "SceneTutorial.h"
#include "SceneBoss.h"
#include "fmod.hpp"
#include "Constants.h"


// Game is a singleton (a class with a single instance) that represents our whole application


class Game {

public:
	Game() {}
	
	static Game &instance() {
		static Game G;
	
		return G;
	}
	
	void init();
	void initBackground();
	bool update(int deltaTime);
	void render();
	
	/** Input callback methods */
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int x, int y);
	void mouseRelease(int x, int y);
	
	/** Getters */
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	std::pair<int, int> getMousePosition();
	std::pair<float, float> getOffsetCamera();
	int getPressedKey();
	bool isBossScene();
	bool isTutorialScene();

	/** Sound */
	void loopSound();
	void playBossLoop();
	void playMainLoop();
	FMOD::System* getSoundSystem();
	
	/** Flux */
	void proceedToBoss();
	void proceedToGame();
	void helpGetOut();

	/** Actions */
	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void killOgre(EnOgre * ogre);
	void alertYesClicked();
	void alertNoClicked();
	void playerOut(bool resetPlayer);
	void noHP();
	void gg();

private:

	void  background();
	OwnTexture backgroundTexture;

	bool bPlay;                       // Continue to play game?
	bool loading;
	bool keys[256], specialKeys[256]; // Store key states so that  we can have access at any time
	int pressedKey;
	int mouseX, mouseY;

	FMOD::System *system;
	FMOD::Sound *mainLoop;
	FMOD::Sound *bossLoop;
	FMOD::Channel *channel1 = 0;
	FMOD::Channel *channel2 = 0;

	Scene* scene;                      // Scene to render
	SceneMain sceneMain;
	SceneMain sceneMainAux;
	SceneTutorial sceneTutorial;
	SceneBoss sceneBoss;

};

#endif // _GAME_INCLUDE