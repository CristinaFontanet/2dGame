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
	void init();
	bool render();
	void update(int deltaTime);

	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void killOgre(EnOgre * ogre);
	void updateArrayOgres(EnOgre * ogre);
	void createOgres();
	void renderOgres();
	void updateOgres(int deltaTime);
	bool isBossScene() { return true; }

protected:
	bool bossStart;
	Boss* boss;
	int playerXtiles, playerYtiles;
	vector<EnOgre*> ogresToDelete;
	vector<glm::vec2> posOgres;
	EnOgre *ogre1;
	vector<EnOgre*> ogres;
};

#endif // _SCENE_INCLUDE

