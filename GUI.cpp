#include "GUI.h"
#include <string>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
//#include <SDL/SDL_timer.h>

CEGUI::OpenGL3Renderer* Bengine::GUI::m_renderer = nullptr;

void Bengine::GUI::init(const std::string& resourceDirectory) {
	showMenu = false;
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
	m_context_menu = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	Window* menuWin = WindowManager::getSingleton().loadLayoutFromFile("menu.layout");
	menuWin->setMousePassThroughEnabled(true); // this is important!
	m_context_menu->setRootWindow(menuWin);
	pushButton = (PushButton*)menuWin->getChild("Button1");
	pushButton2 = (PushButton*)menuWin->getChild("Button2");
	pushButton3 = (PushButton*)menuWin->getChild("Button3");
	pushButton4 = (PushButton*)menuWin->getChild("Button4");
}

CEGUI::GUIContext*  Bengine::GUI::getMenuContext() {
	return m_context_menu;
}

void  Bengine::GUI::onMenu2Click() {
	pushButton2->setText("Button 2 clicked");
}

void  Bengine::GUI::onMenu3Click() {
	pushButton3->setText("Button 3 clicked");
}

void  Bengine::GUI::onMenu4Click() {
	pushButton4->setText("Button 4 clicked");
}


void  Bengine::GUI::onMenu1Click() {
	pushButton->setText("Button 1 clicked");
}

void Bengine::GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context_inv);
	CEGUI::System::getSingleton().destroyGUIContext(*m_context_lives);
}

void Bengine::GUI::draw() {
    m_renderer->beginRendering();
    m_context_inv->draw();
	m_context_lives->draw();
	if(showMenu)m_context_menu->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void Bengine::GUI::setShowMenu(bool show) {
	showMenu = show;
}

void Bengine::GUI::mouseClick( int x, int y) {
	//x: 313 y: 121
	int x0 = 0.35*SCREEN_WIDTH;
	int x1 = 0.65*SCREEN_WIDTH;
	if (x > x0 && x < x1) {
		int b1yt = 0.2*SCREEN_HEIGHT;
		int b1yb = 0.3*SCREEN_HEIGHT;

		int b2yt = 0.35*SCREEN_HEIGHT;
		int b2yb = 0.45*SCREEN_HEIGHT;

		int b3yt = 0.5*SCREEN_HEIGHT;
		int b3yb = 0.6*SCREEN_HEIGHT;

		int b4yt = 0.65*SCREEN_HEIGHT;
		int b4yb = 0.75*SCREEN_HEIGHT;
		if (y > b1yt && y < b1yb) {
			onMenu1Click();
		}
		else if(y > b2yt && y < b2yb) {
			onMenu2Click();
		}
		else if(y > b3yt && y < b3yb) {
			onMenu3Click();
		}
		else if(y > b4yt && y < b4yb) {
			onMenu4Click();
		}

	}
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
