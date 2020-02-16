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
	unsigned int getSpawnPosX();
	unsigned int getSpawnPosY();

	std::string getBackgroundPath();
	std::string getWalkAbleGridPath();
	std::string getForegroundPath();

	Chest* getChest(std::string theID);
	Monster* getMonster(std::string theID);
	PNJ* getPNJ(std::string theID);
	Props* getProps(std::string theID);
	Trigger* getTrigger(std::string theID);

	unsigned int getTpArrivalPosX(std::string theID);
	unsigned int getTpArrivalPosY(std::string theID);

	void initialize();
private:
	std::string ID;
	std::string Path;
	std::string Name;
	unsigned int spawnPosX;
	unsigned int spawnPosY;
	std::string BackgroundID;
	std::string WalkAbleGridID;
	std::string ForegroundID;

	std::map<std::string, Chest> chestMap;
	std::map<std::string, Monster> monsterMap;
	std::map<std::string, PNJ> PNJMap;
	std::map<std::string, Props> propsMap;
	std::map<std::string, Trigger> triggerMap;

	std::map<std::string, unsigned int> TPArrMap;
public:
	void setName(std::string newName);
	void setSpawnPoint(unsigned int newPosX, unsigned int newPosY);

	void setBackground(std::string newID);
	void setWalkAbleGrid(std::string newID);
	void setForeground(std::string newID);

	bool addPNJ(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addMonster(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addChest(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addProps(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addTrigger(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addTriggerShort(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight, std::string newSTPMap, std::string newSTPArrID);
	bool addTPArrival(std::string newID, unsigned int newPosX, unsigned int newPosY);
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