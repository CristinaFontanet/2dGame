#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "P_conillet.h"
#include "P_boss.h"
#include "MainPlayer.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void mouseClicked(int x, int y);
	std::pair<float, float> getOffsetCamera();
	Bengine::GUI m_gui;

private:
	void initShaders();


private:
	TileMap *map;
	MainPlayer *mainPlayer;
	P_conillet *player;
	P_boss *boss;
	ShaderProgram texProgram;
	float currentTime;
	glm::vec3 playerPos;
	glm::mat4 projection;
	float offsetXCamera, offsetYCamera;

};


#endif // _SCENE_INCLUDE

