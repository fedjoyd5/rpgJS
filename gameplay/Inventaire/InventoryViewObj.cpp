#include "InventoryViewObj.h"

using namespace std;

InventoryViewObj::InventoryViewObj() : InventoryObj(){
  int nbInvItem = 0;
}

InventoryViewObj::~InventoryViewObj(){
}

InventoryViewObj::InventoryViewObj(InventoryObj* newRefObj, int newNBItem) : InventoryObj(newRefObj){
  int nbInvItem = newNBItem;
}

int InventoryViewObj::getNbItem(){
  return nbInvItem;
}

double InventoryViewObj::getWeight() {
	return ((double)getNbItem() * getRef()->getWeight());
}

void InventoryViewObj::setNbItem(int newNbItem){
  nbInvItem = newNbItem;
}

void InventoryViewObj::addUn(){
  nbInvItem++;
}

int InventoryViewObj::getItemListIndex(vector<InventoryViewObj> TheList, string TheID){
  int toRetu = -1;
  for(unsigned int curInd = 0;curInd < TheList.size(); curInd++){
    if(TheList[curInd].getID() == TheID){ toRetu = curInd; }
  }
  return toRetu;
}