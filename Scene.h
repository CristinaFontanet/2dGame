#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "P_conillet.h"
#include "P_boss.h"
#include "MainPlayer.h"
#include "Enemy.h"
#include "Ogre.h"
#include "GUI.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
using namespace TextureC;
class Scene {

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void mouseClicked(int x, int y);
	void background();
	void dmgEnnemys(int dmg, glm::ivec2 dmgAt);
	void selectItem(int num);
	void showMenu();
	std::pair<float, float> getOffsetCamera();
	Bengine::GUI m_gui;

private:
	void initShaders();

private:
	TileMap *map;
	MainPlayer *mainPlayer;
	EnOgre *ogre1;
	Enemy *enemy;
	Enemy *pony;
	P_conillet *player;
	P_boss *boss;
	ShaderProgram texProgram;
	float currentTime;
	TextureC::Texture backgroundTexture;
	glm::vec2 playerPos;
	glm::mat4 projection;
	float offsetXCamera, offsetYCamera;
	vector<EnOgre*> ogres;
};


#endif // _SCENE_INCLUDE

