#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include <CEGUI/CEGUI.h>
#include <vector>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

using namespace std;


class Item {
public:
	#define PICKAXE 1
	#define MATERIAL 2
	#define SWORD 3
	#define BELL 4

	Item * createItem(int type, int element, int dmg, int amount, CEGUI::Window* inventoryWindow);
	Item(int typeP, int elementP, int dmgP, int amount, CEGUI::Window* inventoryWindow);
	Item();

	void setAmount(int newAmount);
	void reduceAmount(int num);
	int getAmount();
	string getMaterialString();
	void addItem();
	void setSelected(bool select);
	void setWindowProperties();
	bool improveSword();
	bool improvePeak();
	vector<pair<Item*, int>>* getEvolveItemsNeeded();
	void setEvolveItemsNeeded(vector<pair<Item*, int>>*);
	int type;
	int element;
	int dmg;
	int amount;

private:
	vector<pair<Item*,int>> *evolveItems;
	CEGUI::Window* windImage;
	CEGUI::Window* windImageSelected;
	CEGUI::Window* windAmount;
	CEGUI::Window* windInventory;
	string slot;

	struct evolveItem {
		int type;
	};
};

#endif 