#pragma once

#include <string>
#include "../../TIJS.h"
#include "../Animator.h"

class Props
{
public:
	Props();
	Props(std::string newID, std::string newPath, unsigned int newPosX, unsigned int newPosY);
	~Props();

	void initialize();
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

	std::string textureID;
	unsigned int width;
	unsigned int height;
	std::map<std::string, unsigned int> posTexture;
};

