#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Item.h"

using namespace std;

Item *Item::createItem(int type, int element, int dmg)
{
	Item *item = new Item(type, element,dmg);
	return item;
}

Item::Item(int typeP, int elementP, int dmgP) {
	type = typeP;
	element = elementP;
	dmg = dmgP;
}

Item::Item() {

 }