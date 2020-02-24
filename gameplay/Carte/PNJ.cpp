#include "PNJ.h"

using namespace std;

PNJ::PNJ()
{
	ID = "";
	Path = "";
	textureID = "";
	width = 0;
	height = 0;
	speed = 0.00;
}

PNJ::PNJ(string newID, string newPath, float newPosX, float newPosY)
{
	ID = newID;
	Path = newPath;
	setPosition(newPosX, newPosY);
	textureID = "";
	width = 0;
	height = 0;
	speed = 0.00;
}


PNJ::~PNJ()
{
}

std::string PNJ::getID()
{
	return ID;
}

void PNJ::initialize()
{
	CTinyJS* theJSContext = nullptr;
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function PNJ.setSpeed(newSpeed)", &PNJ_js_setSpeed, this);
		theJSContext->addNative("function PNJ.setTexture(newID)", &PNJ_js_setTexture, this);
		theJSContext->addNative("function PNJ.setSize(newWidth, newHeight)", &PNJ_js_setSize, this);
		theJSContext->addNative("function PNJ.addPosTexture(newID, newPosX, newPosY)", &PNJ_js_addPosTexture, this);
		theJSContext->addNative("function PNJ.addTextureIntRect(newID, newPosX, newPosY, newWidth, newHeight)", &PNJ_js_addTextureIntRect, this);
		theJSContext->addNative("function PNJ.addAnimation(newID, newNbImg, newDurationBImg)", &PNJ_js_addAnimation, this);

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

unsigned int PNJ::getWidth()
{
	return width;
}

unsigned int PNJ::getHeight()
{
	return height;
}

bool PNJ::canInteract(sf::Vector2f playerPos)
{
	sf::FloatRect theRectToTest(getPosition().x - (((float)width / 2) + RAYON_TO_ACTIVATE), getPosition().y - ((float)height + RAYON_TO_ACTIVATE), (width + (2 * RAYON_TO_ACTIVATE)), (height + (2 * RAYON_TO_ACTIVATE)));
	return theRectToTest.contains(playerPos);
}

std::string PNJ::getTexturePath()
{
	return (Path + ID + "/" + textureID);
}

sf::IntRect PNJ::getTextureIntRect(std::string theIntRectID)
{
	if (mapTextureIntRect.count(theIntRectID) == 0) {
		theIntRectID = "default";
		if (mapTextureIntRect.count(theIntRectID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapTextureIntRect[theIntRectID];
}

sf::IntRect PNJ::getDefaultTextureIntRect()
{
	string theNewID = "default";
	if (mapTextureIntRect.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapTextureIntRect[theNewID];
}

Animator * PNJ::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

sf::IntRect PNJ::getAnimationZeroIntRect(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return sf::IntRect(0, 0, width, height); }
	return getTextureIntRect(mapAnimator[theAnimationID].getZeroIntRectID());
}

void PNJ::resetAnimation(std::string theAnimationID, sf::Time newElapsedTime)
{
	if (mapAnimator.count(theAnimationID) == 0) { return; }
	mapAnimator[theAnimationID].reset(newElapsedTime);
}

void PNJ::moveRight(sf::Time newElapsedTime)
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

void PNJ::moveLeft(sf::Time newElapsedTime)
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

void PNJ::moveUp(sf::Time newElapsedTime)
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

void PNJ::moveDown(sf::Time newElapsedTime)
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

void PNJ::checkMove(sf::Image theWAG)
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

void PNJ::setSpeed(float newSpeed)
{
	if (newSpeed < 0.01) { speed = 0.01; return; }
	if (newSpeed > 2.00) { speed = 1.00; return; }
	speed = newSpeed;
}

void PNJ::setTextureID(std::string newID)
{
	textureID = newID;
}

void PNJ::setSize(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
}

bool PNJ::addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool PNJ::addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, newWidth, newHeight);
	return true;
}

bool PNJ::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
	return true;
}

void PNJ_js_setSpeed(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((PNJ*)userdata)->setSpeed(v->getParameter("newSpeed")->getDouble());
}

void PNJ_js_setTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((PNJ*)userdata)->setTextureID(v->getParameter("newID")->getString());
}

void PNJ_js_setSize(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((PNJ*)userdata)->setSize(v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void PNJ_js_addPosTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((PNJ*)userdata)->addPosTexture(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt());
}

void PNJ_js_addTextureIntRect(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((PNJ*)userdata)->addTextureIntRect(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt(), v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void PNJ_js_addAnimation(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((PNJ*)userdata)->addAnimation(v->getParameter("newID")->getString(), v->getParameter("newNbImg")->getInt(), v->getParameter("newDurationBImg")->getDouble());
}
