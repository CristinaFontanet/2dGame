#include "AlertGUI.h"
#include <string>
#include <iostream>
#include <vector>
#include "Constants.h"

CEGUI::OpenGL3Renderer* AlertGUI::m_renderer = nullptr;

void AlertGUI::init(const std::string& resourceDirectory, CEGUI::OpenGL3Renderer* rend, std::string text) {
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

	loadScheme("TaharezLook.scheme");
	loadScheme("WindowsLook.scheme");
	loadScheme("HUDDemo.scheme");
	loadScheme("GameMenu.scheme");
	loadScheme("Generic.scheme");
	loadScheme("OgreTray.scheme"); 
	loadScheme("AlfiskoSkin.scheme");
	loadScheme("SampleBrowser.scheme");
	loadScheme("VanillaSkin.scheme");
	loadScheme("VanillaCommonDialogs.scheme");
	ImageManager::getSingleton().loadImageset("TaharezLook.imageset", "imagesets");
	ImageManager::getSingleton().loadImageset("spritesheet_tiles.imageset", "imagesets");
	

	m_context = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	Window* menuWin = WindowManager::getSingleton().loadLayoutFromFile("AlertUI.layout");
	menuWin->setMousePassThroughEnabled(true); // this is important!
	m_context->setRootWindow(menuWin);
	Window* txt = menuWin->getChild("Label");
	txt->setProperty("Text", text);
}

void AlertGUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void AlertGUI::draw() {
	if (m_renderer != nullptr) {
		m_renderer->beginRendering();
		m_context->draw();
		m_renderer->endRendering();
		glDisable(GL_SCISSOR_TEST);
	}
}

void AlertGUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void AlertGUI::setFont(const std::string& fontFile) {
   // CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}

/** MOUSE **/
void AlertGUI::mouseClick(int x, int y) {
	//x: 313 y: 121
	
}

void  AlertGUI::onMenuNoClick() {
	//exit(0);
}

void  AlertGUI::onMenuYesClick() {
	//showMenu = false;
}

CEGUI::GUIContext*  AlertGUI::getContext() {
	return m_context;
}
