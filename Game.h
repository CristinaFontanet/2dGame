#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


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
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button, int x, int y);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	std::pair<int, int> getMousePosition();

	std::pair<float, float> getOffsetCamera();

	int getPressedKey();

	void loopSound();

private:
	int mouseX, mouseY;
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	int pressedKey;                                 // we can have access at any time
};


#endif // _GAME_INCLUDE


