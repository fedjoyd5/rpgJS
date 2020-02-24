#pragma once

#include <string>
#include <map>
#include <SFML\Graphics.hpp>

#include "../../TIJS.h"
#include "../Animator.h"

class Trigger : public sf::Sprite
{
public:
	Trigger();
	Trigger(std::string newID, std::string newPath, float newPosX, float newPosY);
	Trigger(std::string newID, float newPosX, float newPosY, unsigned int newWidth, unsigned int newHeight, std::string newSimpleTpMap, std::string newSimpleTpArrID);
	~Trigger();

	std::string getID();
	void initialize();
	bool CheckIsIn(sf::Vector2f posToCheck);
	
	bool isSimpleTP();
	std::string getSimpleTPMap();
	std::string getSimpleTPArrID();
	unsigned int getWidth();
	unsigned int getHeight();

	std::string getTexturePath();
	sf::IntRect getTextureIntRect(std::string theIntRectID);
	sf::IntRect getDefaultTextureIntRect();
	Animator* getAnimation(std::string theAnimationID);
	sf::IntRect getAnimationZeroIntRect(std::string theAnimationID);
	void resetAnimation(std::string theAnimationID, sf::Time newElapsedTime);
private:
	std::string ID;
	std::string Path;
	sf::FloatRect Activateur;

	std::string textureID;
	unsigned int width;
	unsigned int height;
	std::map<std::string, sf::IntRect> mapTextureIntRect;
	std::map<std::string, Animator> mapAnimator;

	bool simpleTp;
	std::string simpleTpMap;
	std::string simpleTpArrID;

public:
	void setTextureID(std::string newID);
	void setSize(unsigned int newWidth, unsigned int newHeight);
	bool addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight);
	bool addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg);
};

void trigger_js_setTexture(CScriptVar *v, void *userdata);
void trigger_js_setSize(CScriptVar *v, void *userdata);
void trigger_js_addPosTexture(CScriptVar *v, void *userdata);
void trigger_js_addTextureIntRect(CScriptVar *v, void *userdata);
void trigger_js_addAnimation(CScriptVar *v, void *userdata);