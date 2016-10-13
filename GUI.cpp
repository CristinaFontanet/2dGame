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

	setMouseCursor("TaharezLook/MouseArrow");

	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(Key::Scan::ArrowDown); // Tells CEGUI Key has been Pressed
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(Key::Scan::ArrowUp); // Tells CEGUI Key has been Released

	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar('c');

	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
	//CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(float delta_x, float delta_y);
	//CEGUI::System::getSingleton().injectTimePulse(float timeElapsed);
	createInventory();
}

void Bengine::GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void Bengine::GUI::draw() {
    m_renderer->beginRendering();
    m_context->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void Bengine::GUI::setMouseCursor(const std::string& imageFile) {
    m_context->getMouseCursor().setDefaultImage(imageFile);
}

void Bengine::GUI::showMouseCursor() {
    m_context->getMouseCursor().show();
}

void Bengine::GUI::hideMouseCursor() {
    m_context->getMouseCursor().hide();
}


void Bengine::GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

CEGUI::Window* Bengine::GUI::createInventory() {
	if (inventoryWindow == nullptr) {
		inventoryWindow = WindowManager::getSingleton().loadLayoutFromFile("inventory2.layout");
		m_context->setRootWindow(inventoryWindow);
		
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
	return inventoryWindow;
}

CEGUI::Window* Bengine::GUI::getInventoryWindow() {
	return inventoryWindow;
}

void Bengine::GUI::setFont(const std::string& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}
