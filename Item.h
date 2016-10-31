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
	string getMaterialString();
	void addItem();
	void setSelected(bool select);
	void setWindowProperties();
	void setElement(int element);
	bool improveSword();
	bool improvePeak();
	vector<pair<Item*, int>>* getEvolveItemsNeeded();
	void setEvolveItemsNeeded(vector<pair<Item*, int>>*);
	int getAmount();
	int getElement();
	int type;
	int element;
	int dmg;
	int amount;

private:
	vector<pair<Item*,int>> *evolveItems;
	CEGUI::Window* windImage = nullptr;
	CEGUI::Window* windImageSelected = nullptr;
	CEGUI::Window* windAmount = nullptr;
	CEGUI::Window* windInventory = nullptr;
	string slot;

	struct evolveItem {
		int type;
	};
};

#endif 