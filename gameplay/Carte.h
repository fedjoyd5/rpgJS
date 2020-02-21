#pragma once

#include <string>
#include <vector>
#include <map>

#include "../TIJS.h"
#include "Carte\Chest.h"
#include "Carte\Monster.h"
#include "Carte\PNJ.h"
#include "Carte\Props.h"
#include "Carte\Trigger.h"
#include "Player.h"

class Carte
{
public:
	Carte();
	Carte(std::string newPath, std::string newID);
	~Carte();

	std::string getID();
	std::string getName();
	float getSpawnPosX();
	float getSpawnPosY();

	std::string getBackgroundPath();
	std::string getWalkAbleGridPath();
	std::string getForegroundPath();

	Chest* getChest(std::string theID);
	std::vector<std::string> getChestIdList();
	Monster* getMonster(std::string theID);
	std::vector<std::string> getMonsterIdList();
	PNJ* getPNJ(std::string theID);
	std::vector<std::string> getPNJIdList();
	Props* getProps(std::string theID);
	std::vector<std::string> getPropsIdList();
	Trigger* getTrigger(std::string theID);
	std::vector<std::string> getTriggerIdList();

	float getTpArrivalPosX(std::string theID);
	float getTpArrivalPosY(std::string theID);

	void initialize();
private:
	std::string ID;
	std::string Path;
	std::string Name;
	float spawnPosX;
	float spawnPosY;
	std::string BackgroundID;
	std::string WalkAbleGridID;
	std::string ForegroundID;

	std::map<std::string, Chest> chestMap;
	std::map<std::string, Monster> monsterMap;
	std::map<std::string, PNJ> PNJMap;
	std::map<std::string, Props> propsMap;
	std::map<std::string, Trigger> triggerMap;

	std::map<std::string, float> TPArrMap;
public:
	void setName(std::string newName);
	void setSpawnPoint(float newPosX, float newPosY);

	void setBackground(std::string newID);
	void setWalkAbleGrid(std::string newID);
	void setForeground(std::string newID);

	bool addPNJ(std::string newID, float newPosX, float newPosY);
	bool addMonster(std::string newID, float newPosX, float newPosY);
	bool addChest(std::string newID, float newPosX, float newPosY);
	bool addProps(std::string newID, float newPosX, float newPosY);
	bool addTrigger(std::string newID, float newPosX, float newPosY);
	bool addTriggerShort(std::string newID, float newPosX, float newPosY, unsigned int newWidth, unsigned int newHeight, std::string newSTPMap, std::string newSTPArrID);
	bool addTPArrival(std::string newID, float newPosX, float newPosY);
};

void carte_js_setName(CScriptVar *v, void *userdata);
void carte_js_setSpawnPoint(CScriptVar *v, void *userdata);
void carte_js_setBrackground(CScriptVar *v, void *userdata);
void carte_js_setWalkAbleGrid(CScriptVar *v, void *userdata);
void carte_js_setForeground(CScriptVar *v, void *userdata);

void carte_js_addPNJ(CScriptVar *v, void *userdata);
void carte_js_addMonster(CScriptVar *v, void *userdata);
void carte_js_addChest(CScriptVar *v, void *userdata);
void carte_js_addProps(CScriptVar *v, void *userdata);
void carte_js_addTrigger(CScriptVar *v, void *userdata);
void carte_js_addTriggerShort(CScriptVar *v, void *userdata);

void carte_js_addTPArrival(CScriptVar *v, void *userdata);