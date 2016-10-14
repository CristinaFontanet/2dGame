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

	Item * createItem(int type, int element, int dmg, int amount, CEGUI::Window* inventoryWindow);
	Item(int typeP, int elementP, int dmgP, int amount, CEGUI::Window* inventoryWindow);
	Item();

	void setAmount(int newAmount);
	void addItem();
	void setSelected(bool select);

	int type;
	int element;
	int dmg;
	int amount;

private:

	CEGUI::Window* windImage;
	CEGUI::Window* windImageSelected;
	CEGUI::Window* windAmount;
	CEGUI::Window* windInventory;
};

#endif 