#include "gameStoryData.h"

using namespace std;

gameStoryData::gameStoryData()
{
	ID = "";
	Path = "";
	Name = "";
	Version = "";
	starterID = "";
	thePlayer = Player();
}

gameStoryData::gameStoryData(string newPath, string newID)
{
	ID = newID;
	Path = newPath;
	thePlayer = Player(Path + ID + "/");
	Name = "";
	Version = "";
	starterID = "";

	CTinyJS* theJSContext = getNewJSContext();

	theJSContext->addNative("function Story.setName(newName)", &GSD_js_setName, this);
	theJSContext->addNative("function Story.setVersion(newVersion)", &GSD_js_setVersion, this);
	theJSContext->addNative("function Story.addItem(newID)", &GSD_js_addItem, this);
	theJSContext->addNative("function Story.addMap(newID)", &GSD_js_addMap, this);
	theJSContext->addNative("function Story.setStartMap(newID)", &GSD_js_setStartMap, this);
	thePlayer.registerPlayerInitiFunction(theJSContext);

	try {
		theJSContext->execute(getCodeFromFiles(Path + ID + "/index.js"));
	} catch (CScriptException *e) {
		printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
	}

	for (map<string, Item>::iterator iteraItem = itemMap.begin(); iteraItem != itemMap.end(); iteraItem++) {
		iteraItem->second.initialize();
	}
	for (map<string, Carte>::iterator iteraMap = carteMap.begin(); iteraMap != carteMap.end(); iteraMap++) {
		iteraMap->second.initialize();
	}

	delete theJSContext;
}


gameStoryData::~gameStoryData()
{
}

string gameStoryData::getID()
{
	return ID;
}

string gameStoryData::getName()
{
	return Name;
}

string gameStoryData::getVersion()
{
	return Version;
}

Player * gameStoryData::getPlayer()
{
	return &thePlayer;
}

Item * gameStoryData::getItem(string TheID)
{
	if (itemMap.count(TheID) == 0) { return nullptr; }
	return &(itemMap[TheID]);
}

Carte * gameStoryData::getCarte(string TheID)
{
	if (carteMap.count(TheID) == 0) { return nullptr; }
	return &(carteMap[TheID]);
}

Carte * gameStoryData::getStarter()
{
	if (carteMap.count(starterID) == 0) { return nullptr; }
	return &(carteMap[starterID]);
}

// -----------------------

bool gameStoryData::addItem(string newID)
{
	//printf("the new Item ID : %s(%s)\n", newID.c_str(), (Path + ID + "/item/").c_str());
	//return false;
	if (itemMap.count(newID) == 1) { return false; }
	itemMap[newID] = Item(Path + ID + "/item/", newID);
	return true;
}

bool gameStoryData::addCarte(string newID)
{
	//printf("the new Carte ID : %s(%s)\n", newID.c_str(), (Path + ID + "/map/").c_str());
	//return false;
	if (carteMap.count(newID) == 1) { return false; }
	carteMap[newID] = Carte(Path + ID + "/map/", newID);
	return true;
}

void gameStoryData::setStartMap(string newID)
{
	starterID = newID;
	//printf("the new Starter : %s\n", ID.c_str());
}

void gameStoryData::setVersion(string newVersion)
{
	Version = newVersion;
	//printf("the new Version : %s\n", Version.c_str());
}

void gameStoryData::setName(string newName)
{
	Name = newName;
	//printf("the new Name : %s\n", Name.c_str());
}

// ------------------------

void GSD_js_addItem(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((gameStoryData*)userdata)->addItem(v->getParameter("newID")->getString());
}

void GSD_js_addMap(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((gameStoryData*)userdata)->addCarte(v->getParameter("newID")->getString());
}

void GSD_js_setStartMap(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((gameStoryData*)userdata)->setStartMap(v->getParameter("newID")->getString());
}

void GSD_js_setVersion(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((gameStoryData*)userdata)->setVersion(v->getParameter("newVersion")->getString());
}

void GSD_js_setName(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((gameStoryData*)userdata)->setName(v->getParameter("newName")->getString());
}