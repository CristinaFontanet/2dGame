#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <iostream>


using namespace std;


class Item
{
public:
	#define PICKAXE 1
	#define MATERIAL 2


	Item(int typeP, int elementP);
	Item();

	int type;
	int element;

private:

	Item * createItem(int type, int element);
};

#endif 