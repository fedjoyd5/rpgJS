#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "Inventaire\InventoryObj.h"
#include "Inventaire\InventoryViewObj.h"

class Inventory
{
public:
	std::vector<InventoryObj> Content;

	Inventory();
	Inventory(double newMaxWeight);
	~Inventory();
  
	std::vector<InventoryViewObj> getContentView();
	double getActualWeight();
	double getMaxWeight();
	void setMaxWeight(double newMaxWeight);
private:
	double maxWeight;
};

