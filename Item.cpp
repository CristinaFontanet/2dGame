#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Item.h"

using namespace std;

Item *Item::createItem(int type, int element)
{
	Item *item = new Item(type, element);
	return item;
}

Item::Item(int typeP, int elementP) {
	type = typeP;
	element = elementP;
}

Item::Item() {

 }