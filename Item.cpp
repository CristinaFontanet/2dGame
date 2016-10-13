#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Item.h"


Item *Item::createItem(int type, int element, CEGUI::Window* inventoryWindow) {
	Item *item = new Item(type, element);
	if (inventoryWindow == nullptr) {

	}

	return item;
}

Item::Item(int typeP, int elementP) {
	type = typeP;
	element = elementP;
}

Item::Item() {

 }