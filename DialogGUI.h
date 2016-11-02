#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/Event.h>
#include <CEGUI/PropertySet.h>
#include <CEGUI/EventSet.h>
#include <CEGUI/InputEvent.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <string.h>

using namespace CEGUI;
using namespace std;

class DialogGUI {
    public:
        void init(const string& resourceDirectory, CEGUI::OpenGL3Renderer* rend);
        void destroy();

        void draw();

        void setFont(const string& fontFile);
		void loadScheme(const string& schemeFile);
        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		CEGUI::GUIContext* getContext();

		void setText(string txt);

    private:
        static CEGUI::OpenGL3Renderer* m_renderer;
		CEGUI::GUIContext* m_context = nullptr;
		Window* txt;

};
