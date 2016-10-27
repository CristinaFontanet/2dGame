#include "MenuGUI.h"
#include <string>
#include <iostream>
#include <vector>
#include "Constants.h"

CEGUI::OpenGL3Renderer* MenuGUI::m_renderer = nullptr;

void MenuGUI::init(const std::string& resourceDirectory, MainPlayer* mainPlayer, CEGUI::OpenGL3Renderer* rend) {
	showCrafting = false;
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
	pushButton2->setText("Button 2 clicked");
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
}

void MenuGUI::setCraftElements(vector<pair<Item*, vector<pair<Item*, int>>*>>* itemsToImprove) {
	int siz = itemsToImprove->size();
	Item* result1 = itemsToImprove->at(0).first;
	vector<pair<Item*, int>>* elementsNeeded = itemsToImprove->at(0).second;

	Window* subWind = craftWindow->getChild("CraftingWind");
	Window* groupBox1 = subWind->getChild("StaticGroup");
	Window* res1 = groupBox1->getChild("Result1");
		Window* img1 = res1->getChild("Image");
		img1->setProperty("Image", "spritesheet_tiles/"+result1->getMaterialString());
		Window* num1 = res1->getChild("Quant");
		num1->setProperty("Text", "1");
		//Correcte fins aqui
	pair<Item*, int> it1= elementsNeeded->at(0);
	Window* itn1 = groupBox1->getChild("ItemNeeded1");
		Window* img2 = itn1->getChild("Image");
		img2->setProperty("Image", "spritesheet_tiles/" + it1.first->getMaterialString());
		Window* num2 = itn1->getChild("Quant");
		num2->setProperty("Text", to_string(it1.second));

	pair<Item*, int> it2 = elementsNeeded->at(1);
	Window* itn2 = groupBox1->getChild("ItemNeeded2");

		Window* img3 = itn2->getChild("Image");
		img3->setProperty("Image", "spritesheet_tiles/" + it2.first->getMaterialString());
		Window* num3 = itn2->getChild("Quant");
		num3->setProperty("Text", to_string(it2.second));
}

