#pragma once

#include "Carte.h"
#include "Inventaire\Item.h"
#include "Player.h"

class gameStoryData
{
public:
	gameStoryData();
	gameStoryData(std::string newPath, std::string newID);
	~gameStoryData();

	std::string getID();
	std::string getName();
	std::string getVersion();

	Player* getPlayer();
	Item* getItem(std::string TheID);
	Carte* getCarte(std::string TheID);
	Carte* getStarter();
private:
	std::string ID;
	std::string Path;
	std::string Name;
	std::string Version;

	Player thePlayer;
	std::map<std::string, Item> itemMap;
	std::map<std::string, Carte> carteMap;
	std::string starterID;
public:
	bool addItem(std::string newID);
	bool addCarte(std::string newID);
	void setStartMap(std::string newID);
	void setVersion(std::string newVerison);
	void setName(std::string newName);
};

void GSD_js_addItem(CScriptVar *v, void *userdata);
void GSD_js_addMap(CScriptVar *v, void *userdata);
void GSD_js_setStartMap(CScriptVar *v, void *userdata);
void GSD_js_setVersion(CScriptVar *v, void *userdata);
void GSD_js_setName(CScriptVar *v, void *userdata);