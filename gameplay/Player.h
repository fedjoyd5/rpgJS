#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <SFML\Graphics\Rect.hpp>

#include "Inventory.h"
#include "../TIJS.h"
#include "Animator.h"

class Player
{
public:
	Player();
	Player(std::string newPath);
	~Player();

	void registerPlayerInitiFunction(CTinyJS* TheJSC);
	std::string getName();
	float getSpeed();

	std::string getTexturePath();
	unsigned int getWidth();
	unsigned int getHeight();
	sf::IntRect getPosTexture(std::string theID);
	sf::IntRect getDefaultTexture();
	Animator* getAnimation(std::string theAnimationID);
private:
	std::string name;
	std::string Path;
	float speed;

	std::string textureID;
	unsigned int width;
	unsigned int height;
	std::map<std::string, sf::IntRect> mapPosTexture;
	std::map<std::string, Animator> mapAnimator;
public:
	void setName(std::string newName);
	void setTexture(std::string newID);
	void setSpeed(float newSpeed);

	void setSize(unsigned int newWidth, unsigned int newHeight);
	bool addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg);
};

void player_js_setName(CScriptVar *v, void *userdata);
void player_js_setTexture(CScriptVar *v, void *userdata);
void player_js_setSpeed(CScriptVar *v, void *userdata);
//void player_js_(CScriptVar *v, void *userdata);
//void player_js_(CScriptVar *v, void *userdata);

void player_js_setSize(CScriptVar *v, void *userdata);
void player_js_addPosTexture(CScriptVar *v, void *userdata);
void player_js_addAnimation(CScriptVar *v, void *userdata);