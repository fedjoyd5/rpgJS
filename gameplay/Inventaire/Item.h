#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include "../../TIJS.h"

class Item
{
public:
	Item();
	Item(std::string newPath, std::string newID);
	Item(std::string newID, std::string newName, double newWeight);
	~Item();
	std::string getID();
	std::string getName();
	double getWeight();

	void initialize();

private:
	std::string ID;
	std::string Path;
	std::string Name;
	double Weight;

public:
	bool setName(std::string newName);
	bool setWeight(double newWeight);
};

void item_js_setName(CScriptVar *v, void *userdata);
void item_js_setWeight(CScriptVar *v, void *userdata);

