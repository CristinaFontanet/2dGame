#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "SceneMain.h"
#include "SceneTutorial.h"
#include "SceneBoss.h"
#include "fmod.hpp"
#include "Constants.h"


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	void initBackground();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int x, int y);
	void mouseRelease(int x, int y);
	void alertYesClicked();
	void alertNoClicked();

	void playerOut(bool resetPlayer);

	void noHP();

	void gg();

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	std::pair<int, int> getMousePosition();

	std::pair<float, float> getOffsetCamera();

	int getPressedKey();

	void loopSound();

	void playBossLoop();
	
	void playMainLoop();

	bool dmgEnnemys(int dmg, glm::ivec2 dmgAt);

	FMOD::System* getSoundSystem();

	void killOgre(EnOgre * ogre);
	void proceedToBoss();
	void proceedToGame();
	bool isBossScene();
	bool isTutorialScene();
	void helpGetOut();
	void start();
private:
	bool loading;
	OwnTexture backgroundTexture;
	void  background();
	FMOD::System *system;
	FMOD::Sound     *mainLoop;
	FMOD::Sound     *bossLoop;
	FMOD::Channel   *channel1 = 0;
	FMOD::Channel   *channel2 = 0;
	int mouseX, mouseY;
	bool bPlay;                       // Continue to play game?
	SceneMain sceneMain;
	SceneTutorial sceneTutorial;
	SceneBoss sceneBoss;
	Scene* scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	int pressedKey;                                 // we can have access at any time

};


#endif // _GAME_INCLUDE

/*


glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
//glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f)
gluOrtho2D(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();
// Draw your quad here in screen coordinates

backgroundTexture.use();

glBegin(GL_QUADS);
glTexCoord2f(0 + 0.05, 1);
glVertex3f(0.0f, float(SCREEN_HEIGHT - 1), 0.f);

glTexCoord2f(1 - 0.05, 1);
glVertex3f(float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

glTexCoord2f(1 - 0.05, 0);
glVertex3f(float(SCREEN_WIDTH - 1), 0.f, 0.f);

glTexCoord2f(0 + 0.05, 0);
glVertex3f(0.0f, 0.f, 0.f);
glEnd();
//end draw background quad
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
*/
