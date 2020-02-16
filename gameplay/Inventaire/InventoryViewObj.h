#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "InventoryObj.h"

class InventoryViewObj : public InventoryObj
{
public:
	InventoryViewObj();
	~InventoryViewObj();
	InventoryViewObj(InventoryObj* newRefObj, int newNBItem = 1);

  int getNbItem();
  double getWeight();

  void setNbItem(int newNbItem);
  void addUn();

  static int getItemListIndex(std::vector<InventoryViewObj> TheList, std::string TheID);
private:
  int nbInvItem;
};