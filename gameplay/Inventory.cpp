#include "Inventory.h"

using namespace std;

Inventory::Inventory()
{
	Content = vector<InventoryObj>(0);
	maxWeight = 0;
}
Inventory::Inventory(double newMaxWeight)
{
	Content = vector<InventoryObj>();
	maxWeight = newMaxWeight;
}


Inventory::~Inventory()
{
}

double Inventory::getActualWeight()
{
	double toRet = 0;
	for (unsigned int i = 0; i < Content.size(); i++) { toRet = toRet + Content[i].getRef()->getWeight(); }
	return toRet;
}

double Inventory::getMaxWeight()
{
	return maxWeight;
}

void Inventory::setMaxWeight(double newMaxWeight)
{ 
	maxWeight = newMaxWeight;
}

vector<InventoryViewObj> Inventory::getContentView()
{
	vector<InventoryViewObj> toRet(0);
  for(unsigned int Cuur = 0; Cuur < Content.size(); Cuur++){
    int thInd = InventoryViewObj::getItemListIndex(toRet, Content[Cuur].getID());
    if(thInd != -1){
      toRet[thInd].addUn();
    }else{
      thInd = toRet.size();
      toRet.push_back(InventoryViewObj(&Content[Cuur]));
      toRet[thInd].setNbItem(1);
    }
  }
	return toRet;
}
