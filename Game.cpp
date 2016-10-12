#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

#include "include\SDL.h"

#include "CEGUI\CEGUI.h"

#include <include\SDL_timer.h>
#include <include\SDL_events.h>
#include <include\SDL_keycode.h>
#include <include\SDL_scancode.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

using namespace std;

using namespace CEGUI;

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	if (key == 'i' || key == 'I') scene.openInventory();
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Game::mousePress(int button, int x, int y)
{
	mouseX = x;
	mouseY = y;
	scene.mouseClicked(x, y);
}

void Game::mouseRelease(int button, int x, int y)
{
	mouseX = x;
	mouseY = y;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

std::pair<int,int> Game::getMousePosition() {
	pair <int, int> position;
	position.first = mouseX;
	position.second = mouseY;
	return position;
}

std::pair<float, float> Game::getOffsetCamera() {
	return scene.getOffsetCamera();
}






void inject_input(bool & must_quit)
{

	SDL_Event e;

	// Go through all available events:
	while (SDL_PollEvent(&e))
	{

		// Route according to the event type:
		switch (e.type)
		{

			// Mouse section:

		case SDL_MOUSEMOTION:
			// We inject the mouse position directly here:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(
				static_cast<float>(e.motion.x), static_cast<float>(e.motion.y));
			break;

		case SDL_MOUSEBUTTONDOWN:
		//	handle_mouse_down(e.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			//handle_mouse_up(e.button.button);
			break;

			// Keyboard section:
			
		case SDL_KEYDOWN:

		/*	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(e.key.keysym.scancode);

			/*
			* Managing the character is more difficult, we have to use a translated
			* unicode value:
			*
			*

			if ((e.key.keysym.unicode & 0xFF80) == 0)
			{
				CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(
					e.key.keysym.unicode & 0x7F);
			}
			break; */

		case SDL_KEYUP:
		/*	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(e.key.keysym.scancode);
			break;
			*/
			// A WM quit event occured:
		case SDL_QUIT:
			must_quit = true;
			break;

	/*	case SDL_VIDEORESIZE:
			CEGUI::System::getSingleton().notifyDisplaySizeChanged(
				CEGUI::Size(e.resize.w, e.resize.h));
			break; */

		}

	}

}

void Game::handle_mouse_down(Uint8 button)
{

	switch (button)
	{

	case SDL_BUTTON_LEFT:
		System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
		break;

	case SDL_BUTTON_MIDDLE:
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
		break;

	case SDL_BUTTON_RIGHT:
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
		break;

/*	case SDL_BUTTON_WHEELDOWN:
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(-1);
		break;

	case SDL_BUTTON_WHEELUP:
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(+1);
		break;
		*/
	default:
		cout << "handle_mouse_down ignored '" << static_cast<int>(button)
			<< "'" << endl;
		break;

	}

}