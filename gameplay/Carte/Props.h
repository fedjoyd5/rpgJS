#pragma once

#include <string>
#include <map>
#include <SFML\Graphics.hpp>

#include "../../TIJS.h"
#include "../Animator.h"

class Props : public sf::Sprite
{
public:
	Props();
	Props(std::string newID, std::string newPath, float newPosX, float newPosY);
	~Props();

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

void props_js_setTexture(CScriptVar *v, void *userdata);
void props_js_setSize(CScriptVar *v, void *userdata);
void props_js_addPosTexture(CScriptVar *v, void *userdata);
void props_js_addTextureIntRect(CScriptVar *v, void *userdata);
void props_js_addAnimation(CScriptVar *v, void *userdata);

