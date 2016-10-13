#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

using namespace std;


class Item {
public:
	#define PICKAXE 1
	#define MATERIAL 2

	Item * createItem(int type, int element, int dmg, CEGUI::Window* inventoryWindow);
	Item(int typeP, int elementP, int dmgP);
	Item();

	int type;
	int element;
	int dmg;

private:

	CEGUI::Window* windImage;
	CEGUI::Window* windImageSelected;
	CEGUI::Window* windAmount;
	CEGUI::Window* windInventory;
};

#endif 