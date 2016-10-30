#ifndef _SCENE_MAIN_INCLUDE
#define _SCENE_MAIN_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "P_conillet.h"
#include "P_boss.h"
#include "MainPlayer.h"
#include "Enemy.h"
#include "Ogre.h"
#include "GUI.h"
#include "MenuGUI.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
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
	EnOgre *ogre1;
	Enemy *enemy;
	Enemy *pony;
	vector<EnOgre*> ogres;
	vector<EnOgre*> ogresToDelete;

};

#endif // _SCENE_INCLUDE

