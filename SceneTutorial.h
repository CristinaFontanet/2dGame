#ifndef _SCENE_TUTORIAL_INCLUDE
#define _SCENE_TUTORIAL_INCLUDE

#include "Scene.h"
#include "Ogre.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class SceneTutorial: public Scene {

public:
	SceneTutorial();
	~SceneTutorial();

	void init();
	void render();
	void update(int deltaTime);

	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void killOgre(EnOgre * ogre);

protected:

	EnOgre *ogre1;
	Enemy *pony;
	
};

#endif // _SCENE_INCLUDE

