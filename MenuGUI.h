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

#define NUM_ROCKS_NEEDED 2
#define NUM_GOLD_NEEDED_SWORD 2
#define NUM_DIAMOND_NEEDED_SWORD 2

class MenuGUI {
    public:
        void init(const std::string& resourceDirectory, MainPlayer* mainPlayer, CEGUI::OpenGL3Renderer* rend);
        void destroy();

        void draw();

        void setMouseCursor(const std::string& imageFile);
        void showMouseCursor();
        void hideMouseCursor();
		void mouseClick(int x, int y);
		void showMenuClicked();

        void setFont(const std::string& fontFile);
		void loadScheme(const std::string& schemeFile);
        // Getters
		bool isMenuShowing();
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		CEGUI::GUIContext* getMenuContext();


		void MenuGUI::setCraftSword();

    private:
		void createCraftWindow();
		void createMenu();
        static CEGUI::OpenGL3Renderer* m_renderer;
		CEGUI::GUIContext* m_context_menu = nullptr;
		CEGUI::Window* m_root_menu = nullptr;
		MainPlayer* mainPlayer;
		/** Menu*/
		int b1yt, b1yb, b2yt, b2yb, b3yt, b3yb, b4yt, b4yb, x0, x1;
		bool showMenu;
		PushButton* pushButton;
		PushButton* pushButton2;
		PushButton* pushButton3;
		PushButton* pushButton4;
		void  onMenu1Click();
		void  onMenuCraftClick();
		void  onMenuExitClick();
		void  onMenuCancelClick();

		/** Crafting*/
		int c1x0, c1x1, c1y0, c1y1;
		bool showCrafting;
		CEGUI::GUIContext* m_context_craft = nullptr;
		Window* craftWindow;
		Window* res1Img1;
		Window* res1ImgS1;
		Window* res1Num1;
		Window* res1Itm1Img;
		Window* res1Itm1SImg;
		Window* res1Itm1Num;
		Window* res1Itm2Img;
		Window* res1Itm2SImg;
		Window* res1Itm2Num;
		bool craftSword();
		void updateItemsCrafting();
		bool enoughtRocks;
	
};
