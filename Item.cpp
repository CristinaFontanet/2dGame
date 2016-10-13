#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Item.h"


Item *Item::createItem(int type, int element, int dmg, CEGUI::Window* inventoryWindow) {
	Item *item = new Item(type, element, dmg);
	if (inventoryWindow == nullptr) {

	}
	return item;
}

Item::Item(int typeP, int elementP, int dmgP) {
	type = typeP;
	element = elementP;
	dmg = dmgP;
}

Item::Item() {

 }