#ifndef _SCENE_MAIN_INCLUDE
#define _SCENE_MAIN_INCLUDE

#include "Scene.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class SceneMain: public Scene {

public:
	SceneMain();
	~SceneMain();

	void init(MainPlayer* mPlayer);
	void init();
	bool render();
	void update(int deltaTime);

	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void killOgre(EnOgre * ogre);
	void playerOut();
	void alertYesClicked();
	void alertNoClicked();
	void showCraftingMenu();

protected:
	void createOgres();
	void renderOgres();
	void updateOgres(int deltaTime);
	void updateArrayOgres(EnOgre * ogre);
	void updateOgres(EnOgre * ogre);

	EnOgre *ogre1;
	vector<EnOgre*> ogres;
	Enemy *enemy;
	Enemy *pony;
	vector<EnOgre*> ogresToDelete;
	vector<glm::vec2> posOgres;

	int playerXtiles, playerYtiles;
};

#endif // _SCENE_INCLUDE

