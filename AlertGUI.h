#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/Event.h>
#include <CEGUI/PropertySet.h>
#include <CEGUI/EventSet.h>
#include <CEGUI/InputEvent.h>
#include <glm/glm.hpp>


using namespace CEGUI;

class AlertGUI {
    public:
        void init(const std::string& resourceDirectory, CEGUI::OpenGL3Renderer* rend, std::string text);
        void destroy();

        void draw();
		void mouseClick(int x, int y);
		void showMenuClicked();

        void setFont(const std::string& fontFile);
		void loadScheme(const std::string& schemeFile);
        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		CEGUI::GUIContext* getContext();

    private:
        static CEGUI::OpenGL3Renderer* m_renderer;
		CEGUI::GUIContext* m_context = nullptr;
		CEGUI::Window* m_root_menu = nullptr;
		PushButton* pushButtonYes;
		PushButton* pushButtonNo;

		void  onMenuYesClick();
		void  onMenuNoClick();
};
