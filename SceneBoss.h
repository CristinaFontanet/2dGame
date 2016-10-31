#ifndef _SCENE_BOSS_INCLUDE
#define _SCENE_BOSS_INCLUDE

#include "Scene.h"
#include "Boss.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class SceneBoss: public Scene {

public:
	SceneBoss();
	~SceneBoss();

	void init(MainPlayer* mPlayer);
	void render();
	void update(int deltaTime);

	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	//void killOgre(EnOgre * ogre);

protected:
	
	Boss* boss;
	int playerXtiles, playerYtiles;
};

#endif // _SCENE_INCLUDE

