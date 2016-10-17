#include "GUI.h"
#include <string>
#include <vector>

//#include <SDL/SDL_timer.h>

CEGUI::OpenGL3Renderer* Bengine::GUI::m_renderer = nullptr;

void Bengine::GUI::init(const std::string& resourceDirectory) {
    // Check if the renderer and system were not already initialized
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

    m_context_inv = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	m_context_lives = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
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

	setMouseCursor("TaharezLook/MouseArrow");

	createInventory();
	createLives();
}

void Bengine::GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context_inv);
	CEGUI::System::getSingleton().destroyGUIContext(*m_context_lives);
}

void Bengine::GUI::draw() {
    m_renderer->beginRendering();
    m_context_inv->draw();
	m_context_lives->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void Bengine::GUI::setMouseCursor(const std::string& imageFile) {
    m_context_inv->getMouseCursor().setDefaultImage(imageFile);
	m_context_lives->getMouseCursor().setDefaultImage(imageFile);
}

void Bengine::GUI::showMouseCursor() {
    m_context_inv->getMouseCursor().show();
	m_context_lives->getMouseCursor().show();
}

void Bengine::GUI::hideMouseCursor() {
    m_context_inv->getMouseCursor().hide();
	m_context_lives->getMouseCursor().hide();
}

void Bengine::GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void Bengine::GUI::createInventory() {
	if (inventoryWindow == nullptr) {
		inventoryWindow = WindowManager::getSingleton().loadLayoutFromFile("inventory2.layout");
		m_context_inv->setRootWindow(inventoryWindow);
		
		Window* sl1 = inventoryWindow->getChild("Slot1");
		if (sl1 != nullptr) {
			Window* img = sl1->getChild("Image");
			img->setProperty("Image", "spritesheet_tiles/Fusta");
			Window* img2 = sl1->getChild("ImageS");
			img2->setVisible(true);
			img->setVisible(false);
			Window* quant = sl1->getChild("Quant");
			quant->setProperty("Text", "99");
		}
	}
}

void Bengine::GUI::createLives() {
	livesWindow = WindowManager::getSingleton().loadLayoutFromFile("lives.layout");
	m_context_lives->setRootWindow(livesWindow);
}

CEGUI::Window* Bengine::GUI::getInventoryWindow() {
	return inventoryWindow;
}

CEGUI::Window* Bengine::GUI::getLivesWindow() {
	return livesWindow;
}


void Bengine::GUI::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context_inv->setDefaultFont(fontFile);
	m_context_lives->setDefaultFont(fontFile);
}
