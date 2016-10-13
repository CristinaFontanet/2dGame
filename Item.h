#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <iostream>


using namespace std;


class Item
{
public:

	Item(int type, int element);

private:

	Item * createItem(int type, int element);


};

#endif 