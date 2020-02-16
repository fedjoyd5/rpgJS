#include "Player.h"

using namespace std;

Player::Player()
{
	name = "";
	Path = "";
	textureID = "";
	width = 0;
	height = 0;
	speed = 1.00;
}

Player::Player(std::string newPath)
{
	name = "";
	Path = newPath;
	textureID = "";
	width = 0;
	height = 0;
	speed = 1.00;
}


Player::~Player()
{
}

std::string Player::getName()
{
	return name;
}

std::string Player::getTexturePath()
{
	return (Path + textureID);
}

void Player::registerPlayerInitiFunction(CTinyJS * TheJSC)
{
	if (TheJSC == nullptr) { return; }
	TheJSC->addNative("function Player.setName(newName)", &player_js_setName, this);
	TheJSC->addNative("function Player.setTexture(newID)", &player_js_setTexture, this);
	TheJSC->addNative("function Player.setSpeed(newSpeed)", &player_js_setSpeed, this);

	TheJSC->addNative("function Player.setSize(newWidth, newHeight)", &player_js_setSize, this);
	TheJSC->addNative("function Player.addPosTexture(newID, newPosX, newPosY)", &player_js_addPosTexture, this);
	TheJSC->addNative("function Player.addAnimation(newID, newNbImg, newDurationBImg)", &player_js_addAnimation, this);
}

unsigned int Player::getWidth()
{
	return width;
}

unsigned int Player::getHeight()
{
	return height;
}

sf::IntRect Player::getPosTexture(std::string theID)
{
	if (mapPosTexture.count(theID) == 0) {
		theID = "default";
		if (mapPosTexture.count(theID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapPosTexture[theID];
}

sf::IntRect Player::getDefaultTexture()
{
	string theNewID = "default";
	if (mapPosTexture.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapPosTexture[theNewID];
}

Animator * Player::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

float Player::getSpeed()
{
	return speed;
}

void Player::setName(std::string newName)
{
	name = newName;
}

void Player::setTexture(std::string newID)
{
	textureID = newID;
}

void Player::setSize(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
}

bool Player::addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY)
{
	if (mapPosTexture.count(newID) == 1) { return false; }
	mapPosTexture[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool Player::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
}

void Player::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

// ------------------------------------------------------------------

void player_js_setName(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->setName(v->getParameter("newName")->getString());
}

void player_js_setTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->setTexture(v->getParameter("newID")->getString());
}

void player_js_setSize(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->setSize(v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void player_js_addPosTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->addPosTexture(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt());
}

void player_js_addAnimation(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->addAnimation(v->getParameter("newID")->getString(), v->getParameter("newNbImg")->getInt(), v->getParameter("newDurationBImg")->getDouble());
}

void player_js_setSpeed(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->setSpeed(v->getParameter("newSpeed")->getDouble());
}
