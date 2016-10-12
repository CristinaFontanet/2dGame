#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include "mainPlayer.h"
#include <include\SDL_timer.h>
#include <include\SDL_events.h>
using namespace CEGUI;
//#include <SDL/SDL_events.h>

namespace Bengine {
    class GUI {
    public:
        void init(const std::string& resourceDirectory);
        void destroy();

        void draw();
        void update();

        void setMouseCursor(const std::string& imageFile);
        void showMouseCursor();
        void hideMouseCursor();
		bool closeWindowButton(const CEGUI::EventArgs& e);

        void onSDLEvent(SDL_Event& evnt);

        void loadScheme(const std::string& schemeFile);
        void setFont(const std::string& fontFile);
        CEGUI::Window* createWidget(const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
        static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);
		CEGUI::Window* Bengine::GUI::createInventory(const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
        const CEGUI::GUIContext* getContext() { return m_context; }
    private:
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context = nullptr;
        CEGUI::Window* m_root = nullptr;
        unsigned int m_lastTime = 0;
		DefaultWindow* d_root;
		FrameWindow* inventoryWindow;
    };
}