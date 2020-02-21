#include "Carte.h"
#include "gameStoryData.h"

using namespace std;

Carte::Carte()
{
	ID = "";
	Path = "";
	Name = "";
	spawnPosX = 0;
	spawnPosY = 0;
	BackgroundID = "background.png";
	WalkAbleGridID = "walkablegrid.png";
	ForegroundID = "foreground.png";
}

Carte::Carte(string newPath, string newID)
{
	ID = newID;
	Path = newPath;
	Name = "";
	spawnPosX = 0;
	spawnPosY = 0;
	BackgroundID = "background.png";
	WalkAbleGridID = "walkablegrid.png";
	ForegroundID = "foreground.png";
}


Carte::~Carte()
{
}

string Carte::getID()
{
	return ID;
}

string Carte::getName()
{
	return Name;
}

float Carte::getSpawnPosX()
{
	return spawnPosX;
}

float Carte::getSpawnPosY()
{
	return spawnPosY;
}

std::string Carte::getBackgroundPath()
{
	return (Path + ID + "/" + BackgroundID);
}

std::string Carte::getWalkAbleGridPath()
{
	return (Path + ID + "/" + WalkAbleGridID);
}

std::string Carte::getForegroundPath()
{
	return (Path + ID + "/" + ForegroundID);
}

Chest* Carte::getChest(string theID)
{
	if (chestMap.count(theID) == 0) { return nullptr; }
	return &chestMap[theID];
}

vector<string> Carte::getChestIdList()
{
	vector<string> toRet(0);
	for (map<string, Chest>::iterator chestITE = chestMap.begin(); chestITE != chestMap.end(); chestITE++) { toRet.push_back(chestITE->first); }
	return toRet;
}

Monster* Carte::getMonster(string theID)
{
	if (monsterMap.count(theID) == 0) { return nullptr; }
	return &monsterMap[theID];
}

std::vector<std::string> Carte::getMonsterIdList()
{
	vector<string> toRet(0);
	for (map<string, Monster>::iterator monsterITE = monsterMap.begin(); monsterITE != monsterMap.end(); monsterITE++) { toRet.push_back(monsterITE->first); }
	return toRet;
}

PNJ* Carte::getPNJ(string theID)
{
	if (PNJMap.count(theID) == 0) { return nullptr; }
	return &PNJMap[theID];
}

std::vector<std::string> Carte::getPNJIdList()
{
	vector<string> toRet(0);
	for (map<string, PNJ>::iterator PNJITE = PNJMap.begin(); PNJITE != PNJMap.end(); PNJITE++) { toRet.push_back(PNJITE->first); }
	return toRet;
}

Props* Carte::getProps(string theID)
{
	if (propsMap.count(theID) == 0) { return nullptr; }
	return &propsMap[theID];
}

std::vector<std::string> Carte::getPropsIdList()
{
	vector<string> toRet(0);
	for (map<string, Props>::iterator propsITE = propsMap.begin(); propsITE != propsMap.end(); propsITE++) { toRet.push_back(propsITE->first); }
	return toRet;
}

Trigger* Carte::getTrigger(string theID)
{
	if (triggerMap.count(theID) == 0) { return nullptr; }
	return &triggerMap[theID];
}

std::vector<std::string> Carte::getTriggerIdList()
{
	vector<string> toRet(0);
	for (map<string, Trigger>::iterator triggerITE = triggerMap.begin(); triggerITE != triggerMap.end(); triggerITE++) { toRet.push_back(triggerITE->first); }
	return toRet;
}

float Carte::getTpArrivalPosX(string theID)
{
	string inMapID = (theID + "-PosX");
	if (triggerMap.count(theID) == 0) { return spawnPosX; }
	return TPArrMap[inMapID];
}

float Carte::getTpArrivalPosY(string theID)
{
	string inMapID = (theID + "-PosY");
	if (triggerMap.count(theID) == 0) { return spawnPosY; }
	return TPArrMap[inMapID];
}

void Carte::initialize()
{
	CTinyJS* theJSContext = getNewJSContext();
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Map.setName(newName)", &carte_js_setName, this);
		theJSContext->addNative("function Map.setSpawnPoint(newPosX, newPosY)", &carte_js_setSpawnPoint, this);
		theJSContext->addNative("function Map.addPNJ(newPosX, newPosY, newID)", &carte_js_addPNJ, this);
		theJSContext->addNative("function Map.addMonster(newPosX, newPosY, newID)", &carte_js_addMonster, this);
		theJSContext->addNative("function Map.addChest(newPosX, newPosY, newID)", &carte_js_addChest, this);
		theJSContext->addNative("function Map.addProps(newPosX, newPosY, newID)", &carte_js_addProps, this);
		theJSContext->addNative("function Map.addTrigger(newPosX, newPosY, newID)", &carte_js_addTrigger, this);
		theJSContext->addNative("function Map.addTriggerShort(newPosX, newPosY, newWidth, newHeight, newID, newSTPMap, newSTPArrID)", &carte_js_addTriggerShort, this);
		theJSContext->addNative("function Map.addTPArrival(newPosX, newPosY, newID)", &carte_js_addTPArrival, this);

		theJSContext->addNative("function Map.setBackground(newID)", &carte_js_setBrackground, this);
		theJSContext->addNative("function Map.setWalkAbleGrid(newID)", &carte_js_setWalkAbleGrid, this);
		theJSContext->addNative("function Map.setForeground(newID)", &carte_js_setForeground, this);
		
		try {
			theJSContext->execute(code);
		} catch (CScriptException *e) {
			printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
		}

		for (map<string, Chest>::iterator chestITE = chestMap.begin(); chestITE != chestMap.end(); chestITE++) {
			chestITE->second.initialize();
		}
		for (map<string, Monster>::iterator monsterITE = monsterMap.begin(); monsterITE != monsterMap.end(); monsterITE++) {
			monsterITE->second.initialize();
		}
		for (map<string, PNJ>::iterator PNJITE = PNJMap.begin(); PNJITE != PNJMap.end(); PNJITE++) {
			PNJITE->second.initialize();
		}
		for (map<string, Props>::iterator propsITE = propsMap.begin(); propsITE != propsMap.end(); propsITE++) {
			propsITE->second.initialize();
		}
		for (map<string, Trigger>::iterator triggerITE = triggerMap.begin(); triggerITE != triggerMap.end(); triggerITE++) {
			triggerITE->second.initialize();
		}
	}
	if (theJSContext != nullptr) { delete theJSContext; }
}

// ---------- les setter ----------

void Carte::setName(string newName)
{
	Name = newName;
	//printf("new name : %s\n", Name.c_str());
}

void Carte::setSpawnPoint(float newPosX, float newPosY)
{
	spawnPosX = newPosX;
	spawnPosY = newPosY;
	//printf("new spawnpoint : %i, %i\n", spawnPosX, spawnPosY);
}

void Carte::setBackground(std::string newID)
{
	BackgroundID = newID;
}

void Carte::setWalkAbleGrid(std::string newID)
{
	WalkAbleGridID = newID;
}

void Carte::setForeground(std::string newID)
{
	ForegroundID = newID;
}

bool Carte::addPNJ(string newID, float newPosX, float newPosY)
{
	//printf("new PNJ : %s, %i, %i\n", newID.c_str(), newPosX, newPosY);
	//return false;
	if (PNJMap.count(newID) == 1) { return false; }
	PNJMap[newID] = PNJ(newID, (Path + ID + "/PNJ/"), newPosX, newPosY);
	return true;
}

bool Carte::addMonster(string newID, float newPosX, float newPosY)
{
	//printf("new Monster : %s, %i, %i\n", newID.c_str(), newPosX, newPosY);
	//return false;
	if (monsterMap.count(newID) == 1) { return false; }
	monsterMap[newID] = Monster(newID, (Path + ID + "/Monster/"), newPosX, newPosY);
	return true;
}

bool Carte::addChest(string newID, float newPosX, float newPosY)
{
	//printf("new Chest : %s, %i, %i\n", newID.c_str(), newPosX, newPosY);
	//return false;
	if (chestMap.count(newID) == 1) { return false; }
	chestMap[newID] = Chest(newID, (Path + ID + "/Chest/"), newPosX, newPosY);
	return true;
}

bool Carte::addProps(string newID, float newPosX, float newPosY)
{
	//printf("new Props : %s, %i, %i\n", newID.c_str(), newPosX, newPosY);
	//return false;
	if (propsMap.count(newID) == 1) { return false; }
	propsMap[newID] = Props(newID, (Path + ID + "/Props/"), newPosX, newPosY);
	return true;
}

bool Carte::addTrigger(string newID, float newPosX, float newPosY)
{
	//printf("new Trigger : %s, %i, %i\n", newID.c_str(), newPosX, newPosY);
	//return false;
	if (triggerMap.count(newID) == 1) { return false; }
	triggerMap[newID] = Trigger(newID, (Path + ID + "/Trigger/"), newPosX, newPosX);
	return true;
}

bool Carte::addTriggerShort(string newID, float newPosX, float newPosY, unsigned int newWidth, unsigned int newHeight, string newSTPMap, string newSTPArrID)
{
	//printf("new Trigger short : %s, %i, %i, %i, %i to %s(%s)\n", newID.c_str(), newPosX, newPosY, newWidth, newHeight, newSTPMap.c_str(), newSTPArrID.c_str());
	//return false;
	if (triggerMap.count(newID) == 1) { return false; }
	triggerMap[newID] = Trigger(newID, newPosX, newPosY, newWidth, newHeight, newSTPMap, newSTPArrID);
	return true;
}

bool Carte::addTPArrival(string newID, float newPosX, float newPosY)
{
	//printf("new TPArrival : %s, %i, %i\n", newID.c_str(), newPosX, newPosY);
	//return false;
	if (TPArrMap.count(newID + "-PosX") == 1 || TPArrMap.count(newID + "-PosY") == 1) { return false; }
	TPArrMap[newID + "-PosX"] = newPosX;
	TPArrMap[newID + "-PosY"] = newPosY;
	return true;
}

// ----------------- js function ---------------

void carte_js_setName(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	((Carte*)userdata)->setName(v->getParameter("newName")->getString());
}

void carte_js_setSpawnPoint(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	((Carte*)userdata)->setSpawnPoint((float)v->getParameter("newPosX")->getDouble(), (float)v->getParameter("newPosY")->getDouble());
}

void carte_js_setBrackground(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Carte*)userdata)->setBackground(v->getParameter("newID")->getString());
}

void carte_js_setWalkAbleGrid(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Carte*)userdata)->setWalkAbleGrid(v->getParameter("newID")->getString());
}

void carte_js_setForeground(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Carte*)userdata)->setForeground(v->getParameter("newID")->getString());
}

void carte_js_addPNJ(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	string curPNJID = v->getParameter("newID")->getString();
	((Carte*)userdata)->addPNJ(curPNJID, curPosX, curPosY);
}

void carte_js_addMonster(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	string curMonsterID = v->getParameter("newID")->getString();
	((Carte*)userdata)->addMonster(curMonsterID, curPosX, curPosY);
}

void carte_js_addChest(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	string curChestID = v->getParameter("newID")->getString();
	((Carte*)userdata)->addChest(curChestID, curPosX, curPosY);
}

void carte_js_addProps(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	string curPropsID = v->getParameter("newID")->getString();
	((Carte*)userdata)->addProps(curPropsID, curPosX, curPosY);
}

void carte_js_addTrigger(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	string curTriggerID = v->getParameter("newID")->getString();
	((Carte*)userdata)->addTrigger(curTriggerID, curPosX, curPosY);
}

void carte_js_addTriggerShort(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	int curTriggerWidth = v->getParameter("newWidth")->getInt();
	int curTriggerHeight = v->getParameter("newHeight")->getInt();
	string curTriggerID = v->getParameter("newID")->getString();
	string newSTPMap = v->getParameter("newSTPMap")->getString();
	string newSTPArrID = v->getParameter("newSTPArrID")->getString();
	((Carte*)userdata)->addTriggerShort(curTriggerID, curPosX, curPosY, curTriggerWidth, curTriggerHeight, newSTPMap, newSTPArrID);
}

void carte_js_addTPArrival(CScriptVar * v, void * userdata) {
	if (userdata == nullptr) { return; }
	float curPosX = (float)v->getParameter("newPosX")->getDouble();
	float curPosY = (float)v->getParameter("newPosY")->getDouble();
	string curTPAID = v->getParameter("newID")->getString();
	((Carte*)userdata)->addTPArrival(curTPAID, curPosX, curPosY);
}