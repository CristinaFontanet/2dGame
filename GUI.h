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
        const CEGUI::GUIContext* getContext() { return m_context; }
		CEGUI::Window* Bengine::GUI::getInventoryWindow();
    private:
		CEGUI::Window* Bengine::GUI::createInventory();
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context = nullptr;
        CEGUI::Window* m_root = nullptr;
        unsigned int m_lastTime = 0;
		Window* inventoryWindow;
    };
}