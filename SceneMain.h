#ifndef _SCENE_MAIN_INCLUDE
#define _SCENE_MAIN_INCLUDE

#include "Scene.h"




// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class SceneMain: public Scene {

public:
	SceneMain();
	~SceneMain();

	void init();
	void render();
	void update(int deltaTime);


	void renderOgres();

	void updateOgres(int deltaTime);
	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void killOgre(EnOgre * ogre);
	void updateArrayOgres(EnOgre * ogre);
	void updateOgres(EnOgre * ogre);
protected:
	void createOgres();
	EnOgre *ogre1;
	Enemy *enemy;
	Enemy *pony;
	vector<EnOgre*> ogres;
	vector<EnOgre*> ogresToDelete;
	vector<glm::vec2> posOgres;

	int playerXtiles, playerYtiles;
};

#endif // _SCENE_INCLUDE

