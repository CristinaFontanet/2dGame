#include "GUI.h"
#include <string>
#include <iostream>
#include <vector>

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
	men_context_lives = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	Window* menuWin = WindowManager::getSingleton().loadLayoutFromFile("menu.layout");
	men_context_lives->setRootWindow(menuWin);
	//menuWin->setMousePassThroughEnabled(true); // this is important!
	//menuWin->subscribeEvent(Window::EventMouseClick, Event::Subscriber(&FirstWindowSample::evClicked, this));
	pushButton = (PushButton*)menuWin->getChild("Button1");
	pushButton->setText("Hey! Come here!");
	pushButton2 = (PushButton*)menuWin->getChild("Button2");
	pushButton2->setText("Hey! Come here!");
	pushButton2->subscribeEvent(PushButton::EventMouseButtonDown, Event::Subscriber(&Bengine::GUI::onPushButtonClicked, this));
	pushButton->subscribeEvent(PushButton::EventMouseButtonDown, Event::Subscriber(&Bengine::GUI::onPushButtonClicked, this));
//	pushButton->subscribeEvent(PushButton::EventMouseEnters, Event::Subscriber(&Bengine::GUI::onMouseEnters, this));
	//pushButton->subscribeEvent(PushButton::EventMouseLeaves, Event::Subscriber(&Bengine::GUI::onMouseLeaves, this));
}

bool  Bengine::GUI::onPushButtonClicked(const CEGUI::EventArgs &e)
{
	// Our button has been clicked!
	//CEGUI::PushButton * pushButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow("Button1"));
//	pushButton->setText("We got clicked!");
/*	const CEGUI::WindowEventArgs& wea =
        static_cast<const CEGUI::WindowEventArgs&>(e);

    wea.window->setText( "Why you click me?" ); */

	const CEGUI::MouseEventArgs& we =
		static_cast<const CEGUI::MouseEventArgs&>(e);

	CEGUI::String senderID = we.window->getName();
	string aux = senderID.c_str();
	if (senderID == "Button1")
	{
		pushButton->setText("We got clicked!");
		// code for dealing with a "TheButton"
	}
	else if (senderID == "Button2")
	{
		pushButton2->setText("We got clicked!");
		// code for dealing with a "TheButton"
	}

	return true;
}

bool  Bengine::GUI::onMouseEnters(const CEGUI::EventArgs &e)
{
	// Mouse has entered the button. (Hover)
	//CEGUI::PushButton * pushButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow("Button1"));
	pushButton->setText("Now click!");
	return true;
}

bool  Bengine::GUI::onMouseLeaves(const CEGUI::EventArgs &e)
{
	// Mouse has left the button.
	//CEGUI::PushButton * pushButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow("Button1"));
	// Back to its original state!
	pushButton->setText("Hey! Come here!");
	return true;
}

void Bengine::GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context_inv);
	CEGUI::System::getSingleton().destroyGUIContext(*m_context_lives);
}

void Bengine::GUI::draw() {
    m_renderer->beginRendering();
    m_context_inv->draw();
	m_context_lives->draw();
	if(showMenu)men_context_lives->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void Bengine::GUI::setShowMenu(bool show) {
	showMenu = show;
}

void Bengine::GUI::mouseClick( int x, int y) {
	//CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
	men_context_lives->injectMouseButtonDown(CEGUI::LeftButton);
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
