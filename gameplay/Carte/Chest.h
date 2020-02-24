#pragma once

#include <string>
#include <map>
#include <SFML\Graphics.hpp>

#include "../Inventory.h"
#include "../../TIJS.h"
#include "../Animator.h"

class Chest : public sf::Sprite
{
public:
	Chest();
	Chest(std::string newID, std::string newPath, float newPosX, float newPosY);
	~Chest();

	std::string getID();
	void initialize();
	unsigned int getWidth();
	unsigned int getHeight();

	bool canInteract(sf::Vector2f playerPos);

	std::string getTexturePath();
	sf::IntRect getTextureIntRect(std::string theIntRectID);
	sf::IntRect getDefaultTextureIntRect();
	Animator* getAnimation(std::string theAnimationID);
	sf::IntRect getAnimationZeroIntRect(std::string theAnimationID);
	void resetAnimation(std::string theAnimationID, sf::Time newElapsedTime);
private:
	std::string ID;
	std::string Path;

	std::string textureID;
	unsigned int width;
	unsigned int height;
	std::map<std::string, sf::IntRect> mapTextureIntRect;
	std::map<std::string, Animator> mapAnimator;
public:
	void setTextureID(std::string newID);
	void setSize(unsigned int newWidth, unsigned int newHeight);
	bool addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight);
	bool addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg);
};

void chest_js_setTexture(CScriptVar *v, void *userdata);
void chest_js_setSize(CScriptVar *v, void *userdata);
void chest_js_addPosTexture(CScriptVar *v, void *userdata);
void chest_js_addTextureIntRect(CScriptVar *v, void *userdata);
void chest_js_addAnimation(CScriptVar *v, void *userdata);

