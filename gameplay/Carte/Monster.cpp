#include "Monster.h"

using namespace std;

Monster::Monster()
{
	ID = "";
	Path = "";
	textureID = "";
	width = 0;
	height = 0;
	speed = 0.00;
}

Monster::Monster(string newID, string newPath, float newPosX, float newPosY)
{
	ID = newID;
	Path = newPath;
	setPosition(newPosX, newPosY);
	textureID = "";
	width = 0;
	height = 0;
	speed = 0.00;
}


Monster::~Monster()
{
}

std::string Monster::getID()
{
	return ID;
}

void Monster::initialize()
{
	CTinyJS* theJSContext = nullptr;
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Monster.setSpeed(newSpeed)", &monster_js_setSpeed, this);
		theJSContext->addNative("function Monster.setTexture(newID)", &monster_js_setTexture, this);
		theJSContext->addNative("function Monster.setSize(newWidth, newHeight)", &monster_js_setSize, this);
		theJSContext->addNative("function Monster.addPosTexture(newID, newPosX, newPosY)", &monster_js_addPosTexture, this);
		theJSContext->addNative("function Monster.addTextureIntRect(newID, newPosX, newPosY, newWidth, newHeight)", &monster_js_addTextureIntRect, this);
		theJSContext->addNative("function Monster.addAnimation(newID, newNbImg, newDurationBImg)", &monster_js_addAnimation, this);

		try {
			theJSContext->execute(code);
		} catch (CScriptException *e) {
			printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
		}

		setTextureRect(getDefaultTextureIntRect());
		setOrigin(doAPourcent(50, width), height);
	}
	if (theJSContext != nullptr) { delete theJSContext; }
}

unsigned int Monster::getWidth()
{
	return width;
}

unsigned int Monster::getHeight()
{
	return height;
}

std::string Monster::getTexturePath()
{
	return (Path + ID + "/" + textureID);
}

sf::IntRect Monster::getTextureIntRect(std::string theIntRectID)
{
	if (mapTextureIntRect.count(theIntRectID) == 0) {
		theIntRectID = "default";
		if (mapTextureIntRect.count(theIntRectID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapTextureIntRect[theIntRectID];
}

sf::IntRect Monster::getDefaultTextureIntRect()
{
	string theNewID = "default";
	if (mapTextureIntRect.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapTextureIntRect[theNewID];
}

Animator * Monster::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

sf::IntRect Monster::getAnimationZeroIntRect(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return sf::IntRect(0, 0, width, height); }
	return getTextureIntRect(mapAnimator[theAnimationID].getZeroIntRectID());
}

void Monster::resetAnimation(std::string theAnimationID, sf::Time newElapsedTime)
{
	if (mapAnimator.count(theAnimationID) == 0) { return; }
	mapAnimator[theAnimationID].reset(newElapsedTime);
}

void Monster::moveRight(sf::Time newElapsedTime)
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

void Monster::moveLeft(sf::Time newElapsedTime)
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

void Monster::moveUp(sf::Time newElapsedTime)
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

void Monster::moveDown(sf::Time newElapsedTime)
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

void Monster::checkMove(sf::Image theWAG)
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

void Monster::setSpeed(float newSpeed)
{
	if (newSpeed < 0.01) { speed = 0.01; return; }
	if (newSpeed > 2.00) { speed = 1.00; return; }
	speed = newSpeed;
}

void Monster::setTextureID(std::string newID)
{
	textureID = newID;
}

void Monster::setSize(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
}

bool Monster::addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool Monster::addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, newWidth, newHeight);
	return true;
}

bool Monster::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
	return true;
}

void monster_js_setSpeed(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Monster*)userdata)->setSpeed(v->getParameter("newSpeed")->getDouble());
}

void monster_js_setTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Monster*)userdata)->setTextureID(v->getParameter("newID")->getString());
}

void monster_js_setSize(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Monster*)userdata)->setSize(v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void monster_js_addPosTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Monster*)userdata)->addPosTexture(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt());
}

void monster_js_addTextureIntRect(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Monster*)userdata)->addTextureIntRect(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt(), v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void monster_js_addAnimation(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Monster*)userdata)->addAnimation(v->getParameter("newID")->getString(), v->getParameter("newNbImg")->getInt(), v->getParameter("newDurationBImg")->getDouble());
}
