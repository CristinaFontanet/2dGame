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

//Pre: te els materials i es resten
bool Item::improveSword() {
	if (type == SWORD) {
		switch (element) {
		case TUSK:										//TODO: canviar dmg
			element = ROCK;
			dmg = 4;
			setWindowProperties();
			return true;
			break;
		case ROCK:
			element = GOLD;
			dmg = 5;
			setWindowProperties();
			return true;
			break;
		case GOLD:
			element = DIAMOND;
			dmg = 6;
			setWindowProperties();
			return true;
			break;
		}
	}
	return false;
}

bool Item::improvePeak() {
	if (type == PICKAXE) {
		switch (element) {	//WOOD: 1, ROCK = 2; DIAMOND = 5
		case WOOD:										//TODO: canviar dmg
			element = ROCK;
			dmg = 2;
			setWindowProperties();
			return true;
			break;
		case ROCK:
			element = DIAMOND;
			dmg = 5;
			setWindowProperties();
			return true;
			break;
		}
	}
	return false;
}

Item::Item(int typeP, int elementP, int dmgP, int initialAmount, CEGUI::Window* inventoryWindow) {
	type = typeP;
	element = elementP;
	dmg = dmgP;
	windInventory = inventoryWindow;
	amount = initialAmount;
	setWindowProperties();
}

string Item::getMaterialString() {
	string material;
	switch (type) {
	case PICKAXE:
		slot = "Slot1";
		switch (element) {
		case WOOD:
			material = "PickaxeWood";
			break;
		case ROCK:
			material = "PickaxeRock";
			break;
		case DIAMOND:
			material = "PickaxeDiamond";
			break;
		default:
			material = "";
			break;
		}
		break;
	case SWORD:
		slot = "Slot2";
		switch (element) {
		case TUSK:
			material = "TuskSword";
			break;
		case ROCK:
			material = "RockSword";
			break;
		case GOLD:
			material = "GoldSword";
			break;
		case DIAMOND:
			material = "DiamondSword";
			break;
		}
		break;
	case MATERIAL:
		switch (element) {
		case TUSK:
			slot = "Slot3";
			material = "Tusk";
			break;
		case WOOD:
			slot = "Slot3";
			material = "Wood";
			break;
		case ROCK:
			slot = "Slot4";
			material = "Rock";
			break;
		case COAL:
			slot = "Slot5";
			material = "Coal";
			break;
		case GOLD:
			slot = "Slot6";
			material = "Gold";
			break;
		case DIAMOND:
			slot = "Slot7";
			material = "Diamond";
			break;
		default:
			material = "";
			break;
		}
		break;
	case BELLITEM:
		slot = "Slot8";
		material = "Bell";
		break;
	default:
		slot = "";
		break;
	}
	return material;
}

void Item::setWindowProperties() {
	if (windInventory != nullptr) {
		string material = getMaterialString();
		if (slot.size() > 0 && material.size() > 0) {
			CEGUI::Window* sl1 = windInventory->getChild(slot);
			if (sl1 != nullptr) {
				windImage = sl1->getChild("Image");
				windImageSelected = sl1->getChild("ImageS");
				windImageSelected->setVisible(false);
				windImage->setVisible(true);
				windAmount = sl1->getChild("Quant");
				windAmount->setProperty("Text", to_string(amount));
				//windAmount->setProperty("HorzFormatting", "HorzCentred");
				if (type == BELLITEM && amount == 0) {
					windImage->setProperty("Image", "spritesheet_tiles/QuestionMark");
					windImageSelected->setProperty("Image", "spritesheet_tiles/QuestionMark");
				}
				else {
					windImage->setProperty("Image", "spritesheet_tiles/" + material);
					windImageSelected->setProperty("Image", "spritesheet_tiles/" + material);
				}
			}
		}
		
	}
}

Item::Item() {

 }

int Item::getAmount() {
	return amount;
}

int Item::getElement() {
	return element;
}

void Item::reduceAmount(int num) {
	amount -= num;
	if (windAmount != nullptr)
		windAmount->setProperty("Text", to_string(amount));
}

void Item::addItem() {
	amount += 1;
	if (windAmount != nullptr) {
		windAmount->setProperty("Text", to_string(amount));
		if (type == BELLITEM && amount != 0) {
			windImage->setProperty("Image", "spritesheet_tiles/Bell");
			windImageSelected->setProperty("Image", "spritesheet_tiles/Bell");
		}
	}
}

void Item::setAmount(int newAmount) {
	amount = newAmount;
	if (windAmount != nullptr) {
		windAmount->setProperty("Text", to_string(amount));
		if (type == BELLITEM && amount != 0) {
			windImage->setProperty("Image", "spritesheet_tiles/Bell");
			windImageSelected->setProperty("Image", "spritesheet_tiles/Bell");
		}
	}
		
	
}

void Item::setElement(int elem) {
	element = elem;
	setWindowProperties();
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