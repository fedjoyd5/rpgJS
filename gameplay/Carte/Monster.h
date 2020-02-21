#pragma once

#include <string>
#include <map>
#include <SFML\Graphics.hpp>

#include "../../TIJS.h"
#include "../Animator.h"

class Monster : public sf::Sprite
{
public:
	Monster();
	Monster(std::string newID, std::string newPath, float newPosX, float newPosY);
	~Monster();

	void initialize();
	float getSpeed();
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
	float speed;

	std::string textureID;
	unsigned int width;
	unsigned int height;
	std::map<std::string, sf::IntRect> mapTextureIntRect;
	std::map<std::string, Animator> mapAnimator;
public:
	void setSpeed(float newSpeed);

	void setTextureID(std::string newID);
	void setSize(unsigned int newWidth, unsigned int newHeight);
	bool addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight);
	bool addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg);
};

void monster_js_setSpeed(CScriptVar *v, void *userdata);
void monster_js_setTexture(CScriptVar *v, void *userdata);
void monster_js_setSize(CScriptVar *v, void *userdata);
void monster_js_addPosTexture(CScriptVar *v, void *userdata);
void monster_js_addTextureIntRect(CScriptVar *v, void *userdata);
void monster_js_addAnimation(CScriptVar *v, void *userdata);

