#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/Event.h>
#include <CEGUI/PropertySet.h>
#include <CEGUI/EventSet.h>
#include <CEGUI/InputEvent.h>
#include <glm/glm.hpp>
#include "mainPlayer.h"
using namespace CEGUI;

namespace Bengine {
    class GUI {
    public:
        void init(const std::string& resourceDirectory);
        void destroy();

        void draw();

        void setMouseCursor(const std::string& imageFile);
        void showMouseCursor();
        void hideMouseCursor();
		void mouseClick(int x, int y);
		void setShowMenu(bool show);

		void setLives(int numLives);
        void setFont(const std::string& fontFile);
		void loadScheme(const std::string& schemeFile);
        // Getters
		bool isMenuShowing();
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
        const CEGUI::GUIContext* getContext() { return m_context_inv; }
		CEGUI::Window* Bengine::GUI::getInventoryWindow();
		CEGUI::Window* Bengine::GUI::getLivesWindow();
		CEGUI::GUIContext* getMenuContext();

    private:
		int b1yt, b1yb, b2yt, b2yb, b3yt, b3yb, b4yt, b4yb, x0, x1;
		void Bengine::GUI::createInventory();
		void Bengine::GUI::createLives();
		void createMenu();
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context_inv = nullptr;
		CEGUI::GUIContext* m_context_lives = nullptr;
		CEGUI::GUIContext* m_context_menu = nullptr;
		CEGUI::Window* m_root_inv = nullptr;
        CEGUI::Window* m_root_lives = nullptr;
        unsigned int m_lastTime = 0;
		Window* inventoryWindow;
		Window* livesWindow;
		Window* windHeart1;
		Window* windHeart2;
		Window* windHeart3;
		vector<Window*> lives;
		bool showMenu;
		PushButton* pushButton;
		PushButton* pushButton2;
		PushButton* pushButton3;
		PushButton* pushButton4;

		void  onMenu1Click();
		void  onMenu2Click();
		void  onMenu3Click();
		void  onMenuCancelClick();
    };
}