#include "Player.h"

using namespace std;

Player::Player() : Sprite()
{
	name = "";
	Path = "";
	textureID = "";
	width = 0;
	height = 0;
	speed = 1.00;

	notRightBefore = true, notLeftBefore = true, notUpBefore = true, notDownBefore = true;
	notRightActivate = true, notLeftActivate = true, notUpActivate = true, notDownActivate = true;
	RightLeftDepl = 0.0, UpDownDepl = 0.0;
}

Player::Player(std::string newPath) : Sprite()
{
	name = "";
	Path = newPath;
	textureID = "";
	width = 0;
	height = 0;
	speed = 1.00;

	notRightBefore = true, notLeftBefore = true, notUpBefore = true, notDownBefore = true;
	notRightActivate = true, notLeftActivate = true, notUpActivate = true, notDownActivate = true;
	RightLeftDepl = 0, UpDownDepl = 0;
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
	TheJSC->addNative("function Player.setSpeed(newSpeed)", &player_js_setSpeed, this);

	TheJSC->addNative("function Player.setTexture(newID)", &player_js_setTexture, this);
	TheJSC->addNative("function Player.setSize(newWidth, newHeight)", &player_js_setSize, this);
	TheJSC->addNative("function Player.addPosTexture(newID, newPosX, newPosY)", &player_js_addPosTexture, this);
	TheJSC->addNative("function Player.addTextureIntRect(newID, newPosX, newPosY, newWidth, newHeight)", &player_js_addTextureIntRect, this);
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

sf::IntRect Player::getTextureIntRect(std::string theIntRectID)
{
	if (mapTextureIntRect.count(theIntRectID) == 0) {
		theIntRectID = "default";
		if (mapTextureIntRect.count(theIntRectID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapTextureIntRect[theIntRectID];
}

sf::IntRect Player::getDefaultTextureIntRect()
{
	string theNewID = "default";
	if (mapTextureIntRect.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapTextureIntRect[theNewID];
}

Animator * Player::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

sf::IntRect Player::getAnimationZeroIntRect(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return sf::IntRect(0, 0, width, height); }
	return getTextureIntRect(mapAnimator[theAnimationID].getZeroIntRectID());
}

void Player::resetAnimation(std::string theAnimationID, sf::Time newElapsedTime)
{
	if (mapAnimator.count(theAnimationID) == 0) { return; }
	mapAnimator[theAnimationID].reset(newElapsedTime);
}

void Player::initialize()
{
	setTextureRect(getDefaultTextureIntRect());
	setOrigin(doAPourcent(50, width), height);
}

void Player::moveRight(sf::Time newElapsedTime)
{
	RightLeftDepl = 1;
	if (notRightBefore) {
		resetAnimation(WALKRIGHT_AN, newElapsedTime);
		notRightBefore = false;
	}
	notRightActivate = false;

	Animator* theAnim = getAnimation(WALKRIGHT_AN);
	if (theAnim != nullptr) {
		theAnim->CheckTimeAndNext(newElapsedTime);
		setTextureRect(getTextureIntRect(theAnim->getCurIntRectID()));
	} else { setTextureRect(getDefaultTextureIntRect()); }
}

void Player::moveLeft(sf::Time newElapsedTime)
{
	RightLeftDepl = -1;
	if (notLeftBefore) {
		resetAnimation(WALKLEFT_AN, newElapsedTime);
		notLeftBefore = false;
	}
	notLeftActivate = false;

	Animator* theAnim = getAnimation(WALKLEFT_AN);
	if (theAnim != nullptr) {
		theAnim->CheckTimeAndNext(newElapsedTime);
		setTextureRect(getTextureIntRect(theAnim->getCurIntRectID()));
	} else { setTextureRect(getDefaultTextureIntRect()); }
}

void Player::moveUp(sf::Time newElapsedTime)
{
	UpDownDepl = -1;
	if (notUpBefore) {
		resetAnimation(WALKUP_AN, newElapsedTime);
		notUpBefore = false;
	}
	notUpActivate = false;

	Animator* theAnim = getAnimation(WALKUP_AN);
	if (theAnim != nullptr) {
		theAnim->CheckTimeAndNext(newElapsedTime);
		setTextureRect(getTextureIntRect(theAnim->getCurIntRectID()));
	} else { setTextureRect(getDefaultTextureIntRect()); }
}

void Player::moveDown(sf::Time newElapsedTime)
{
	UpDownDepl = 1;
	if (notDownBefore) {
		resetAnimation(WALKDOWN_AN, newElapsedTime);
		notDownBefore = false;
	}
	notDownActivate = false;

	Animator* theAnim = getAnimation(WALKDOWN_AN);
	if (theAnim != nullptr) {
		theAnim->CheckTimeAndNext(newElapsedTime);
		setTextureRect(getTextureIntRect(theAnim->getCurIntRectID()));
	} else { setTextureRect(getDefaultTextureIntRect()); }
}

void Player::checkMove(sf::Image theWAG)
{
	if (notRightActivate && !notRightBefore) { notRightBefore = true; setTextureRect(getAnimationZeroIntRect(WALKRIGHT_AN)); }
	if (notLeftActivate && !notLeftBefore) { notLeftBefore = true; setTextureRect(getAnimationZeroIntRect(WALKLEFT_AN)); }
	if (notUpActivate && !notUpBefore) { notUpBefore = true; setTextureRect(getAnimationZeroIntRect(WALKUP_AN)); }
	if (notDownActivate && !notDownBefore) { notDownBefore = true; setTextureRect(getAnimationZeroIntRect(WALKDOWN_AN)); }

	float PosXAct = getPosition().x;
	float PosYAct = getPosition().y;

	if (sf::FloatRect(0, 0, theWAG.getSize().x, theWAG.getSize().y).contains((PosXAct + RightLeftDepl), (PosYAct + UpDownDepl))) {
		bool depPasFait = true;
		if (!checkColor(theWAG.getPixel((PosXAct + RightLeftDepl), (PosYAct + UpDownDepl)), NO_WALK_COLOR)) {
			move(RightLeftDepl*speed, UpDownDepl*speed);
			depPasFait = false;
		}
		if (!checkColor(theWAG.getPixel(PosXAct, (PosYAct + UpDownDepl)), NO_WALK_COLOR) && depPasFait) {
			move(0, UpDownDepl*speed);
			depPasFait = false;
		}
		if (!checkColor(theWAG.getPixel((PosXAct + RightLeftDepl), PosYAct), NO_WALK_COLOR) && depPasFait) {
			move(RightLeftDepl*speed, 0);
			depPasFait = false;
		}
	}

	notRightActivate = true, notLeftActivate = true, notUpActivate = true, notDownActivate = true;
	RightLeftDepl = 0, UpDownDepl = 0;
}

void Player::setName(std::string newName)
{
	name = newName;
}

void Player::setTextureID(std::string newID)
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
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool Player::addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, newWidth, newHeight);
	return true;
}

bool Player::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
	return true;
}

void Player::setSpeed(float newSpeed)
{
	if (newSpeed < 0.01) { speed = 0.01; return; }
	if (newSpeed > 2.00) { speed = 1.00; return; }
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
	((Player*)userdata)->setTextureID(v->getParameter("newID")->getString());
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

void player_js_addTextureIntRect(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Player*)userdata)->addTextureIntRect(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt(), v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
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
