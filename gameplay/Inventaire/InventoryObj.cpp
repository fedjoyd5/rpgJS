#include "InventoryObj.h"

using namespace std;

InventoryObj::InventoryObj()
{
	ID = "";
	RefObj = nullptr;
}


InventoryObj::~InventoryObj()
{
}


string InventoryObj::getID()
{
	return ID;
}

Item* InventoryObj::getRef()
{
	return RefObj;
}


InventoryObj::InventoryObj(Item* newRefObj)
{
	ID = newRefObj->getID();
	RefObj = newRefObj;
}

InventoryObj::InventoryObj(InventoryObj* newRefObj)
{
	ID = newRefObj->getID();
	RefObj = newRefObj->getRef();
}
