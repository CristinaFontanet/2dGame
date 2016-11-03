#include "DialogGUI.h"
#include <string>
#include <iostream>
#include <vector>
#include "Constants.h"

CEGUI::OpenGL3Renderer* DialogGUI::m_renderer = nullptr;

void DialogGUI::init(const string& resourceDirectory, CEGUI::OpenGL3Renderer* rend) {
    // Check if the renderer and system were not already initialized
	m_renderer = rend;
    if (m_renderer == nullptr) {
        m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

        DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>(System::getSingleton().getResourceProvider());
        rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
        rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
        rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
        rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
        rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeel/");
        rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");

        ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::String im = rp->getDefaultResourceGroup();
		CEGUI::String im2 = CEGUI::ImageManager::getSingleton().getDefaultResourceGroup();
		int im3 = CEGUI::ImageManager::getSingleton().getImageCount();
		CEGUI::String im4 = CEGUI::ImageManager::getSingleton().getImagesetDefaultResourceGroup();
        Scheme::setDefaultResourceGroup("schemes");
        Font::setDefaultResourceGroup("fonts");
        WidgetLookManager::setDefaultResourceGroup("looknfeels");
        WindowManager::setDefaultResourceGroup("layouts");
        ScriptModule::setDefaultResourceGroup("lua_scripts");
    } 

	m_context = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	setFont("DejaVuSans-10");

	loadScheme("Generic.scheme");
	ImageManager::getSingleton().loadImageset("dialog.imageset", "imagesets");
	

	m_context = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	Window* menuWin = WindowManager::getSingleton().loadLayoutFromFile("dialog.layout");
	menuWin->setMousePassThroughEnabled(true); // this is important!
	m_context->setRootWindow(menuWin);
	txt = menuWin->getChild("Label");

}

void DialogGUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void DialogGUI::draw() {
	if (m_renderer != nullptr) {
		m_renderer->beginRendering();
		m_context->draw();
		m_renderer->endRendering();
		glDisable(GL_SCISSOR_TEST);
	}
}

void DialogGUI::loadScheme(const string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void DialogGUI::setFont(const string& fontFile) {
   // CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}

CEGUI::GUIContext*  DialogGUI::getContext() {
	return m_context;
}

void DialogGUI::setText(string text) {
	txt->setProperty("Text", text);
}
