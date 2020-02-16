#pragma once

#include <string>
#include "../../TIJS.h"
#include "../Animator.h"

class Trigger
{
public:
	Trigger();
	Trigger(std::string newID, std::string newPath, unsigned int newPosX, unsigned int newPosY);
	Trigger(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight, std::string newSimpleTpMap, std::string newSimpleTpArrID);
	~Trigger();

	void initialize();
	bool CheckIsIn(unsigned int testPosX, unsigned int testPosY);
	
	bool isSimpleTP();
	std::string getSimpleTPMap();
	std::string getSimpleTPArrID();
	std::string getTexturePath();

	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getPosXTexture(std::string theID);
	unsigned int getPosYTexture(std::string theID);
	unsigned int getDefaultXTexture();
	unsigned int getDefaultYTexture();
private:
	std::string ID;
	std::string Path;
	unsigned int PosX;
	unsigned int PosY;
	unsigned int Width;
	unsigned int Height;

	std::string textureID;
	unsigned int width;
	unsigned int height;
	std::map<std::string, unsigned int> posTexture;

	bool simpleTp;
	std::string simpleTpMap;
	std::string simpleTpArrID;

public:
	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);
};

void trigger_js_setWidth(CScriptVar * v, void * userdata);
void trigger_js_setHeight(CScriptVar * v, void * userdata);