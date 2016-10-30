#include "MenuGUI.h"
#include <string>
#include <iostream>
#include <vector>
#include "Constants.h"

CEGUI::OpenGL3Renderer* MenuGUI::m_renderer = nullptr;

void MenuGUI::init(const std::string& resourceDirectory, MainPlayer* mPlayer, CEGUI::OpenGL3Renderer* rend) {
	showCrafting = false;
	showMenu = false;
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
		if (showCrafting) {
			cout << "x: " << x << ", y: " << y << endl;
			if (x > c1x0 && x < c1x1) {
				if (y > c1y0 && y < c1y1) craftSword();
				else if (y > c2y0 && y < c2y1)craftPeak();
				else if (y > c3y0 && y < c3y1) craftBell();
			}
		}
		else if (x > x0 && x < x1) {
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

void  MenuGUI::onMenuCraftClick() {
	showCrafting = true;
	updateItemsCrafting();
}

void MenuGUI::createCraftWindow() {
	m_context_craft = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	craftWindow = WindowManager::getSingleton().loadLayoutFromFile("crafting2.layout");
	craftWindow->setMousePassThroughEnabled(true); // this is important!
	m_context_craft->setRootWindow(craftWindow);

	Window* subWind = craftWindow->getChild("CraftingWind");
	Window* groupBox1 = subWind->getChild("StaticGroup");
	Window* res1 = groupBox1->getChild("Result1");
	res1Img1 = res1->getChild("Image");
	res1ImgS1 = res1->getChild("ImageS");
	res1Num1 = res1->getChild("Quant");
	Window* res1Itm1 = groupBox1->getChild("ItemNeeded1");
	res1Itm1Img = res1Itm1->getChild("Image");
	res1Itm1SImg = res1Itm1->getChild("ImageS");
	res1Itm1Num = res1Itm1->getChild("Quant");
	Window* itn2 = groupBox1->getChild("ItemNeeded2");
	res1Itm2Img = itn2->getChild("Image");
	res1Itm2SImg = itn2->getChild("ImageS");
	res1Itm2Num = itn2->getChild("Quant");

	setCraftSword();
	c1x0 = 516;
	c1x1 = 596;
	c1y0 = 147;
	c1y1 = 168;

	Window* groupBox2 = subWind->getChild("StaticGroup2");
	Window* res2 = groupBox2->getChild("Result1");
	res2Img1 = res2->getChild("Image");
	res2ImgS1 = res2->getChild("ImageS");
	res2Num1 = res2->getChild("Quant");
	Window* res2Itm1 = groupBox2->getChild("ItemNeeded1");
	res2Itm1Img = res2Itm1->getChild("Image");
	res2Itm1SImg = res2Itm1->getChild("ImageS");
	res2Itm1Num = res2Itm1->getChild("Quant");
	Window* itn3 = groupBox2->getChild("ItemNeeded2");
	res2Itm2Img = itn3->getChild("Image");
	res2Itm2SImg = itn3->getChild("ImageS");
	res2Itm2Num = itn3->getChild("Quant");
	setCraftPeak();
	c2y0 = 291;
	c2y1 = 313;

	Window* groupBox3 = subWind->getChild("StaticGroup3");
	Window* res3 = groupBox3->getChild("Result1");
	res3Img1 = res3->getChild("Image");
	res3ImgS1 = res3->getChild("ImageS");
	res3Num1 = res3->getChild("Quant");
	Window* res3Itm1 = groupBox3->getChild("ItemNeeded1");
	res3Itm1Img = res3Itm1->getChild("Image");
	res3Itm1SImg = res3Itm1->getChild("ImageS");
	res3Itm1Num = res3Itm1->getChild("Quant");
	Window* itn4 = groupBox3->getChild("ItemNeeded2");
	res3Itm2Img = itn4->getChild("Image");
	res3Itm2SImg = itn4->getChild("ImageS");
	res3Itm2Num = itn4->getChild("Quant");
	setCraftBell();
	c3y0 = 454;
	c3y1 = 474;
}

bool MenuGUI::craftSword() {
	if (enoughtRocksSword) {
		//TODO: So guai
		mainPlayer->getSword()->improveSword();
		mainPlayer->getRock()->reduceAmount(NUM_ROCKS_NEEDED_SWORD);
		setCraftSword();
		updateItemsCrafting();
		cout << "YESS" << endl;
	}
	else {
		//TODO: so error
		cout << "NOO" << endl;
	}
	return true;
}

bool MenuGUI::craftPeak() {
	if (enoughtRocksPeak) {
		//TODO: So guai
		mainPlayer->getPeak()->improvePeak();
		mainPlayer->getRock()->reduceAmount(NUM_ROCKS_NEEDED_PEAK);
		setCraftPeak();
		updateItemsCrafting();
		cout << "YESS" << endl;
	}
	else {
		//TODO: so error
		cout << "NOO" << endl;
	}
	return true;
}

bool MenuGUI::craftBell() {
	if (enoughtGoldBell) {
		//TODO: So guai
		mainPlayer->getBell()->addItem();
		mainPlayer->getGold()->reduceAmount(NUM_GOLD_NEEDED_BELL);
		setCraftBell();
		updateItemsCrafting();
		cout << "YESS" << endl;
	}
	else {
		//TODO: so error
		cout << "NOO" << endl;
	}
	return true;
}

void MenuGUI::setCraftSword() {
	Item *currentSword = mainPlayer->getSword();
	res1Num1->setProperty("Text", "1");
	switch (currentSword->element) {
	case TUSK:
		res1Img1->setProperty("Image", "spritesheet_tiles/RockSword");
		res1ImgS1->setProperty("Image", "spritesheet_tiles/RockSword");
		res1Itm1Img->setProperty("Image", "spritesheet_tiles/TuskSword");
		res1Itm1SImg->setProperty("Image", "spritesheet_tiles/TuskSword");
		res1Itm1Num->setProperty("Text", "1");
		res1Itm2Img->setProperty("Image", "spritesheet_tiles/Rock");
		res1Itm2SImg->setProperty("Image", "spritesheet_tiles/Rock");
		res1Itm2Num->setProperty("Text", to_string(NUM_ROCKS_NEEDED_SWORD));

		break;
	case ROCK:
		res1Img1->setProperty("Image", "spritesheet_tiles/GoldSword");
		res1ImgS1->setProperty("Image", "spritesheet_tiles/GoldSword");
		res1Itm1Img->setProperty("Image", "spritesheet_tiles/RockSword");
		res1Itm1SImg->setProperty("Image", "spritesheet_tiles/RockSword");
		res1Itm1Num->setProperty("Text", "1");
		res1Itm2Img->setProperty("Image", "spritesheet_tiles/Gold");
		res1Itm2SImg->setProperty("Image", "spritesheet_tiles/Gold");
		res1Itm2Num->setProperty("Text", to_string(NUM_GOLD_NEEDED_SWORD));
		break;
	case GOLD:
		res1Img1->setProperty("Image", "spritesheet_tiles/DiamondSword");
		res1ImgS1->setProperty("Image", "spritesheet_tiles/DiamondSword");
		res1Itm1Img->setProperty("Image", "spritesheet_tiles/GoldSword");
		res1Itm1SImg->setProperty("Image", "spritesheet_tiles/GoldSword");
		res1Itm1Num->setProperty("Text", "1");
		res1Itm2Img->setProperty("Image", "spritesheet_tiles/Diamond");
		res1Itm2SImg->setProperty("Image", "spritesheet_tiles/Diamond");
		res1Itm2Num->setProperty("Text", to_string(NUM_DIAMOND_NEEDED_SWORD));
		break;
	case DIAMOND:
		res1Img1->setProperty("Image", "spritesheet_tiles/OK");
		res1Itm1Img->setProperty("Image", "spritesheet_tiles/OK");
		res1Itm2Img->setProperty("Image", "spritesheet_tiles/OK");
		res1Num1->setProperty("Text", " "+ to_string(0));
		res1Itm1Num->setProperty("Text", " " + to_string(0));
		res1Itm2Num->setProperty("Text", " " + to_string(0));
		break;
	}
}

void MenuGUI::setCraftPeak() {
	Item *currentPeak = mainPlayer->getPeak();
	res2Num1->setProperty("Text", "1");
	switch (currentPeak->element) {
	case WOOD:
		res2Img1->setProperty("Image", "spritesheet_tiles/PickaxeRock");
		res2ImgS1->setProperty("Image", "spritesheet_tiles/PickaxeRock");
		res2Itm1Img->setProperty("Image", "spritesheet_tiles/PickaxeWood");
		res2Itm1SImg->setProperty("Image", "spritesheet_tiles/PickaxeWood");
		res2Itm1Num->setProperty("Text", "1");
		res2Itm2Img->setProperty("Image", "spritesheet_tiles/Rock");
		res2Itm2SImg->setProperty("Image", "spritesheet_tiles/Rock");
		res2Itm2Num->setProperty("Text", to_string(NUM_ROCKS_NEEDED_PEAK));

		break;
	case ROCK:
		res2Img1->setProperty("Image", "spritesheet_tiles/PickaxeDiamond");
		res2ImgS1->setProperty("Image", "spritesheet_tiles/PickaxeDiamond");
		res2Itm1Img->setProperty("Image", "spritesheet_tiles/PickaxeRock");
		res2Itm1SImg->setProperty("Image", "spritesheet_tiles/PickaxeRock");
		res2Itm1Num->setProperty("Text", "1");
		res2Itm2Img->setProperty("Image", "spritesheet_tiles/Diamond");
		res2Itm2SImg->setProperty("Image", "spritesheet_tiles/Diamond");
		res2Itm2Num->setProperty("Text", to_string(NUM_GOLD_NEEDED_PEAK));
		break;
	case DIAMOND:
		res2Img1->setProperty("Image", "spritesheet_tiles/OK");
		res2Itm1Img->setProperty("Image", "spritesheet_tiles/OK");
		res2Itm2Img->setProperty("Image", "spritesheet_tiles/OK");
		res2Num1->setProperty("Text", " " + to_string(0));
		res2Itm1Num->setProperty("Text", " " + to_string(0));
		res2Itm2Num->setProperty("Text", " " + to_string(0));
		break;
	}

}

void MenuGUI::setCraftBell() {
	Item *currentBell = mainPlayer->getBell();
	res3Num1->setProperty("Text", "1");
	if (currentBell->getAmount() == 0) {
		res3Img1->setProperty("Image", "spritesheet_tiles/Bell");
		res3ImgS1->setProperty("Image", "spritesheet_tiles/Bell");
		res3Itm1Img->setProperty("Image", "spritesheet_tiles/DiamondSword");
		res3Itm1SImg->setProperty("Image", "spritesheet_tiles/DiamondSword");
		res3Itm1Num->setProperty("Text", "1");
		res3Itm2Img->setProperty("Image", "spritesheet_tiles/Gold");
		res3Itm2SImg->setProperty("Image", "spritesheet_tiles/Gold");
		res3Itm2Num->setProperty("Text", to_string(NUM_GOLD_NEEDED_BELL));
	}
	else {
		res3Img1->setProperty("Image", "spritesheet_tiles/OK");
		res3Itm1Img->setProperty("Image", "spritesheet_tiles/OK");
		res3Itm2Img->setProperty("Image", "spritesheet_tiles/OK");
		res3Num1->setProperty("Text", " " + to_string(0));
		res3Itm1Num->setProperty("Text", " " + to_string(0));
		res3Itm2Num->setProperty("Text", " " + to_string(0));
	}
}

void MenuGUI::updateItemsCrafting() {
	updateItemsSword();
	updateItemsPeak();
	updateItemsBell();
}

void MenuGUI::updateItemsSword() {
	Item *currentSword = mainPlayer->getSword();
	res1Itm1SImg->setVisible(true);
	switch (currentSword->element) {
	case TUSK:
		if (mainPlayer->getRock()->getAmount() >= NUM_ROCKS_NEEDED_SWORD) {
			res1Itm2SImg->setVisible(true);
			enoughtRocksSword = true;
			res1ImgS1->setVisible(true);
		}
		else {
			res1Itm2SImg->setVisible(false);
			res1ImgS1->setVisible(false);
			enoughtRocksSword = false;
		}
		break;
	case ROCK:
		if (mainPlayer->getGold()->getAmount() >= NUM_GOLD_NEEDED_SWORD) {
			res1Itm2SImg->setVisible(true);
			enoughtRocksSword = true;
			res1ImgS1->setVisible(true);
		}
		else {
			res1Itm2SImg->setVisible(false);
			res1ImgS1->setVisible(false);
			enoughtRocksSword = false;
		}
		break;
	case GOLD:
		if (mainPlayer->getDiamond()->getAmount() >= NUM_DIAMOND_NEEDED_SWORD) {
			res1Itm2SImg->setVisible(true);
			enoughtRocksSword = true;
			res1ImgS1->setVisible(true);
		}
		else {
			res1Itm2SImg->setVisible(false);
			res1ImgS1->setVisible(false);
			enoughtRocksSword = false;
		}
		break;
	case DIAMOND:
		res1Itm2SImg->setVisible(false);
		res1Itm1SImg->setVisible(false);
		res1ImgS1->setVisible(false);
		enoughtRocksSword = false;
		break;
	}
}

void MenuGUI::updateItemsPeak() {
	Item *currentPeak = mainPlayer->getPeak();
	res2Itm1SImg->setVisible(true);
	switch (currentPeak->element) {
	case WOOD:
		if (mainPlayer->getRock()->getAmount() >= NUM_ROCKS_NEEDED_PEAK) {
			res2Itm2SImg->setVisible(true);
			enoughtRocksPeak = true;
			res2ImgS1->setVisible(true);
		}
		else {
			res2Itm2SImg->setVisible(false);
			res2ImgS1->setVisible(false);
			enoughtRocksPeak = false;
		}
		break;
	case ROCK:
		if (mainPlayer->getGold()->getAmount() >= NUM_GOLD_NEEDED_SWORD) {
			res2Itm2SImg->setVisible(true);
			enoughtRocksPeak = true;
			res2ImgS1->setVisible(true);
		}
		else {
			res2Itm2SImg->setVisible(false);
			res2ImgS1->setVisible(false);
			enoughtRocksPeak = false;
		}
		break;
	case DIAMOND:
		res2Itm2SImg->setVisible(false);
		res2Itm1SImg->setVisible(false);
		res2ImgS1->setVisible(false);
		enoughtRocksPeak = false;
		break;
	}
}

void MenuGUI::updateItemsBell() {
	Item *currentBell = mainPlayer->getBell();
	res3Itm1SImg->setVisible(true);
	if (currentBell->getAmount() == 0) {
		if (mainPlayer->getGold()->getAmount() >= NUM_GOLD_NEEDED_BELL) {
			res3Itm2SImg->setVisible(true);
			enoughtGoldBell = true;
			res3ImgS1->setVisible(true);
		}
		else {
			res3Itm2SImg->setVisible(false);
			res3ImgS1->setVisible(false);
			enoughtGoldBell = false;
		}
	}
	else {
		res3Itm2SImg->setVisible(false);
		res3Itm1SImg->setVisible(false);
		res3ImgS1->setVisible(false);
		enoughtGoldBell = false;
	}
}