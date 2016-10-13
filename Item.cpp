#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Item.h"
#include "TileMap.h"


Item *Item::createItem(int type, int element, int dmg, int amount, CEGUI::Window* inventoryWindow) {
	Item *item = new Item(type, element, dmg, amount, inventoryWindow);
	return item;
}

Item::Item(int typeP, int elementP, int dmgP, int initialAmount, CEGUI::Window* inventoryWindow) {
	type = typeP;
	element = elementP;
	dmg = dmgP;
	windInventory = inventoryWindow;
	amount = initialAmount;
	if (windInventory != nullptr) {
		string slot, material;

		switch (typeP) {
		case PICKAXE:
			slot = "Slot1";
			switch (elementP) {
			case WOOD:
				material = "PickaxeWood";
				break;
			case ROCK:
				material = "PickaxeRock";
				break;
			default:
				material = "";
				break;
			}
			break;
		case MATERIAL:
			slot = "Slot2"; 
			switch (elementP) {
			case WOOD:
				material = "Wood";
				break;
			case ROCK:
				material = "Rock";
				break;
			case TUSK:
				material = "Tusk";
				break;
			default:
				material = "";
				break;
			}
			break;
		default:
			slot = "";
			break;
		}
		CEGUI::Window* sl1 = windInventory->getChild(slot);
		if (sl1 != nullptr && slot.size() >0 && material.size()>0) {
			windImage = sl1->getChild("Image");
			windImageSelected = sl1->getChild("ImageS");
			windImage->setProperty("Image", "spritesheet_tiles/"+material);
			windImageSelected->setProperty("Image", "spritesheet_tiles/" + material);
			windImageSelected->setVisible(false);
			windImage->setVisible(true);
			windAmount = sl1->getChild("Quant");
			windAmount->setProperty("Text", to_string(amount));
		}
	}
}

Item::Item() {

 }

void Item::setAmount(int newAmount) {
	amount = newAmount;
	if (windAmount != nullptr)
		windAmount->setProperty("Text", to_string(amount));
	
}

void Item::setSelected(bool select) {
	if (select) {
		if (!windImageSelected->isVisible()) windImageSelected->setVisible(true);
		if(windImage->isVisible())windImage->setVisible(false);
	}
	else {
		if (windImageSelected->isVisible())windImageSelected->setVisible(false);
		if (!windImage->isVisible())windImage->setVisible(true);
	}
}