#ifndef _SCENE_TUTORIAL_INCLUDE
#define _SCENE_TUTORIAL_INCLUDE

#include "Scene.h"
#include "Ogre.h"
#include "Anastasio.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class SceneTutorial: public Scene {

public:
	SceneTutorial();
	~SceneTutorial();

	void init();
	bool render();
	void update(int deltaTime);
	bool mouseClicked(int x, int y);
	void alertYesClicked();
	void alertNoClicked();
	void showMenu() {};
	void showAnastasio() {};
	void anyOtherKeyPressed();
	bool isTutorialScene() { return true; }

protected:

	int playerXtiles, playerYtiles;
	Anastasio *anastasio;
};

#endif // _SCENE_INCLUDE

