#include "MenuGUI.h"
#include <string>
#include <iostream>
#include <vector>
#include "Constants.h"

CEGUI::OpenGL3Renderer* MenuGUI::m_renderer = nullptr;

void MenuGUI::init(const std::string& resourceDirectory, MainPlayer* mPlayer, CEGUI::OpenGL3Renderer* rend) {
	showCrafting = false;
	mainPlayer = mPlayer;
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

	m_context_menu = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	m_context_craft = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
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

	createMenu();
	createCraftWindow();
}

void MenuGUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context_menu);
}

void MenuGUI::draw() {
    m_renderer->beginRendering();
	if(showMenu) m_context_menu->draw();
	if (showCrafting) m_context_craft->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void MenuGUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void MenuGUI::setFont(const std::string& fontFile) {
   // CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context_menu->setDefaultFont(fontFile);
}

/** MOUSE **/
void MenuGUI::mouseClick(int x, int y) {
	//x: 313 y: 121
	if (showMenu) {
		if (x > x0 && x < x1) {
			if (y > b1yt && y < b1yb) onMenu1Click();
			else if (y > b2yt && y < b2yb) onMenuCraftClick();
			else if (y > b3yt && y < b3yb) onMenuExitClick();
			else if (y > b4yt && y < b4yb) onMenuCancelClick();
		}
	}
}

void MenuGUI::setMouseCursor(const std::string& imageFile) {
	m_context_menu->getMouseCursor().setDefaultImage(imageFile);
}

void MenuGUI::showMouseCursor() {
	m_context_menu->getMouseCursor().show();
}

void MenuGUI::hideMouseCursor() {
	m_context_menu->getMouseCursor().hide();
}

/** MENU **/
void MenuGUI::showMenuClicked() {
	if (showMenu) {
		if (showCrafting) showCrafting = false;
		else showMenu = false;
	}
	else showMenu = true;
}

void  MenuGUI::onMenu1Click() {
	pushButton->setText("Button 1 clicked");
}

void  MenuGUI::onMenuCraftClick() {
	showCrafting = true;
}

void  MenuGUI::onMenuExitClick() {
	exit(0);
}

void  MenuGUI::onMenuCancelClick() {
	showMenu = false;
}

bool MenuGUI::isMenuShowing() {
	return showMenu;
}

CEGUI::GUIContext*  MenuGUI::getMenuContext() {
	return m_context_menu;
}

void MenuGUI::createMenu() {
	m_context_menu = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	Window* menuWin = WindowManager::getSingleton().loadLayoutFromFile("menu.layout");
	menuWin->setMousePassThroughEnabled(true); // this is important!
	m_context_menu->setRootWindow(menuWin);
	pushButton = (PushButton*)menuWin->getChild("Button1");
	pushButton2 = (PushButton*)menuWin->getChild("Button2");
	pushButton3 = (PushButton*)menuWin->getChild("Button3");
	pushButton4 = (PushButton*)menuWin->getChild("Button4");

	x0 = 0.35*SCREEN_WIDTH;
	x1 = 0.65*SCREEN_WIDTH;

	b1yt = 0.2*SCREEN_HEIGHT;
	b1yb = 0.3*SCREEN_HEIGHT;

	b2yt = 0.35*SCREEN_HEIGHT;
	b2yb = 0.45*SCREEN_HEIGHT;

	b3yt = 0.5*SCREEN_HEIGHT;
	b3yb = 0.6*SCREEN_HEIGHT;

	b4yt = 0.65*SCREEN_HEIGHT;
	b4yb = 0.75*SCREEN_HEIGHT;
}

/** Crafting **/

void MenuGUI::createCraftWindow() {
	m_context_craft = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	craftWindow = WindowManager::getSingleton().loadLayoutFromFile("crafting2.layout");
	craftWindow->setMousePassThroughEnabled(true); // this is important!
	m_context_craft->setRootWindow(craftWindow);

	Window* subWind = craftWindow->getChild("CraftingWind");
	Window* groupBox1 = subWind->getChild("StaticGroup");
	Window* res1 = groupBox1->getChild("Result1");
	res1Img1 = res1->getChild("Image");
	res1Num1 = res1->getChild("Quant");
	Window* res1Itm1 = groupBox1->getChild("ItemNeeded1");
	res1Itm1Img = res1Itm1->getChild("Image");
	res1Itm1Num = res1Itm1->getChild("Quant");
	Window* itn2 = groupBox1->getChild("ItemNeeded2");
	res1Itm2Img = itn2->getChild("Image");
	res1Itm2Num = itn2->getChild("Quant");

	setCraftSword();
}

void MenuGUI::setCraftSword() {
	Item *currentSword = mainPlayer->getSword();
	res1Num1->setProperty("Text", "1");
	switch (currentSword->element) {
	case TUSK:
		res1Img1->setProperty("Image", "spritesheet_tiles/RockSword");
		res1Itm1Img->setProperty("Image", "spritesheet_tiles/TuskSword");
		res1Itm1Num->setProperty("Text", "1");
		res1Itm2Img->setProperty("Image", "spritesheet_tiles/Rock");
		res1Itm2Num->setProperty("Text", "20");
		break;
	case ROCK:
		res1Img1->setProperty("Image", "spritesheet_tiles/GoldSword");
		res1Itm1Img->setProperty("Image", "spritesheet_tiles/RockSword");
		res1Itm1Num->setProperty("Text", "1");
		res1Itm2Img->setProperty("Image", "spritesheet_tiles/Gold");
		res1Itm2Num->setProperty("Text", "30");
		break;
	case GOLD:
		break;
	}

}

