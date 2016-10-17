#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
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

        void setFont(const std::string& fontFile);
		void loadScheme(const std::string& schemeFile);
        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
        const CEGUI::GUIContext* getContext() { return m_context_inv; }
		CEGUI::Window* Bengine::GUI::getInventoryWindow();
		CEGUI::Window* Bengine::GUI::getLivesWindow();

		void setLives(int numLives);
    private:
		void Bengine::GUI::createInventory();
		void Bengine::GUI::createLives();
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context_inv = nullptr;
		CEGUI::GUIContext* m_context_lives = nullptr;
		CEGUI::Window* m_root_inv = nullptr;
        CEGUI::Window* m_root_lives = nullptr;
        unsigned int m_lastTime = 0;
		Window* inventoryWindow;
		Window* livesWindow;
		Window* windHeart1;
		Window* windHeart2;
		Window* windHeart3;
		vector<Window*> lives;
    };
}