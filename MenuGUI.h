#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/Event.h>
#include <CEGUI/PropertySet.h>
#include <CEGUI/EventSet.h>
#include <CEGUI/InputEvent.h>
#include <glm/glm.hpp>
#include "mainPlayer.h"
#include "Anastasio.h"

using namespace CEGUI;

#define NUM_ROCKS_NEEDED_SWORD 2
#define NUM_GOLD_NEEDED_SWORD 2
#define NUM_DIAMOND_NEEDED_SWORD 2
#define NUM_ROCKS_NEEDED_PEAK 2
#define NUM_DIAMOND_NEEDED_PEAK 2
#define NUM_GOLD_NEEDED_BELL 2

class MenuGUI {
    public:

		static MenuGUI &instance() {
			static MenuGUI G;

			return G;
		}
        void init(const std::string& resourceDirectory, MainPlayer* mainPlayer, CEGUI::OpenGL3Renderer* rend, ShaderProgram &shaderProgram, TileMap * tileMap);
        void destroy();

        void draw();
		bool render();

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

		bool showAnastasio();
		void showHelp();

		void showCraftButton(bool b);

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
		void  onMenuInstructionsClick();
		void  onMenuCraftClick();
		void  onMenuExitClick();
		void  onMenuCancelClick();

		/** Crafting*/
		int c1x0, c1x1, c1y0, c1y1;
		int c2y0, c2y1;
		int c3y0, c3y1;
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
		Window* res2Img1;
		Window* res2ImgS1;
		Window* res2Num1;
		Window* res2Itm1Img;
		Window* res2Itm1SImg;
		Window* res2Itm1Num;
		Window* res2Itm2Img;
		Window* res2Itm2SImg;
		Window* res2Itm2Num;

		Window* res3Img1;
		Window* res3ImgS1;
		Window* res3Num1;
		Window* res3Itm1Img;
		Window* res3Itm1SImg;
		Window* res3Itm1Num;
		Window* res3Itm2Img;
		Window* res3Itm2SImg;
		Window* res3Itm2Num;
		bool craftSword();
		bool craftPeak();
		bool craftBell();

		void setCraftSword();
		void setCraftPeak();
		void setCraftBell();
		void updateItemsCrafting();
		void updateItemsSword();
		void updateItemsPeak();
		void updateItemsBell();
		bool enoughtRocksSword;
		bool enoughtRocksPeak;
		bool enoughtGoldBell;
		bool correctSword;

		Anastasio *anastasioInstr;
		bool showingAnastasio;
		bool showCraftBut;
	
};
