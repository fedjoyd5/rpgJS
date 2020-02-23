#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <SFML\Graphics.hpp>

#include "Inventory.h"
#include "../TIJS.h"
#include "Animator.h"

class Player : public sf::Sprite
{
public:
	Player();
	Player(std::string newPath);
	~Player();

	void registerPlayerInitiFunction(CTinyJS* TheJSC);
	std::string getName();
	unsigned int getWidth();
	unsigned int getHeight();

	std::string getTexturePath();
	sf::IntRect getTextureIntRect(std::string theIntRectID);
	sf::IntRect getDefaultTextureIntRect();
	Animator* getAnimation(std::string theAnimationID);
	sf::IntRect getAnimationZeroIntRect(std::string theAnimationID);
	void resetAnimation(std::string theAnimationID, sf::Time newElapsedTime);

	void initialize();

	void moveRight(sf::Time newElapsedTime);
	void moveLeft(sf::Time newElapsedTime);
	void moveUp(sf::Time newElapsedTime);
	void moveDown(sf::Time newElapsedTime);
	void checkMove(sf::Image theWAG);
private:
	std::string name;
	std::string Path;
	float speed;

	std::string textureID;
	unsigned int width, height;
	std::map<std::string, sf::IntRect> mapTextureIntRect;
	std::map<std::string, Animator> mapAnimator;

	bool notRightBefore, notLeftBefore, notUpBefore, notDownBefore;
	bool notRightActivate, notLeftActivate, notUpActivate, notDownActivate;
	float RightLeftDepl, UpDownDepl;
public:
	void setName(std::string newName);
	void setSpeed(float newSpeed);

	void setTextureID(std::string newID);
	void setSize(unsigned int newWidth, unsigned int newHeight);
	bool addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY);
	bool addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight);
	bool addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg);
};

void player_js_setName(CScriptVar *v, void *userdata);
void player_js_setSpeed(CScriptVar *v, void *userdata);
//void player_js_(CScriptVar *v, void *userdata);
//void player_js_(CScriptVar *v, void *userdata);

void player_js_setTexture(CScriptVar *v, void *userdata);
void player_js_setSize(CScriptVar *v, void *userdata);
void player_js_addPosTexture(CScriptVar *v, void *userdata);
void player_js_addTextureIntRect(CScriptVar *v, void *userdata);
void player_js_addAnimation(CScriptVar *v, void *userdata);