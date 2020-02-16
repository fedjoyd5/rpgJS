#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "Item.h"

class InventoryObj
{
public:
	InventoryObj();
	~InventoryObj();
	InventoryObj(Item* newRefObj);
	InventoryObj(InventoryObj* newRefObj);

	std::string getID();
	Item* getRef();
private:
	std::string ID;
	Item* RefObj;
};

