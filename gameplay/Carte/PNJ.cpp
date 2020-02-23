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
