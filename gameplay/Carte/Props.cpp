#include "Props.h"

using namespace std;

Props::Props()
{
	ID = "";
	Path = "";
	textureID = "";
	width = 0;
	height = 0;
}

Props::Props(string newID, string newPath, float newPosX, float newPosY)
{
	ID = newID;
	Path = newPath;
	setPosition(newPosX, newPosY);
	textureID = "";
	width = 0;
	height = 0;
}


Props::~Props()
{
}

std::string Props::getID()
{
	return ID;
}

void Props::initialize()
{
	CTinyJS* theJSContext = nullptr;
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Props.setTexture(newID)", &props_js_setTexture, this);
		theJSContext->addNative("function Props.setSize(newWidth, newHeight)", &props_js_setSize, this);
		theJSContext->addNative("function Props.addPosTexture(newID, newPosX, newPosY)", &props_js_addPosTexture, this);
		theJSContext->addNative("function Props.addTextureIntRect(newID, newPosX, newPosY, newWidth, newHeight)", &props_js_addTextureIntRect, this);
		theJSContext->addNative("function Props.addAnimation(newID, newNbImg, newDurationBImg)", &props_js_addAnimation, this);

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

unsigned int Props::getWidth()
{
	return width;
}

unsigned int Props::getHeight()
{
	return height;
}

bool Props::canInteract(sf::Vector2f playerPos)
{
	sf::FloatRect theRectToTest(getPosition().x - (((float)width / 2) + RAYON_TO_ACTIVATE), getPosition().y - ((float)height + RAYON_TO_ACTIVATE), (width + (2 * RAYON_TO_ACTIVATE)), (height + (2 * RAYON_TO_ACTIVATE)));
	return theRectToTest.contains(playerPos);
}

std::string Props::getTexturePath()
{
	return (Path + ID + "/" + textureID);
}

sf::IntRect Props::getTextureIntRect(std::string theIntRectID)
{
	if (mapTextureIntRect.count(theIntRectID) == 0) {
		theIntRectID = "default";
		if (mapTextureIntRect.count(theIntRectID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapTextureIntRect[theIntRectID];
}

sf::IntRect Props::getDefaultTextureIntRect()
{
	string theNewID = "default";
	if (mapTextureIntRect.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapTextureIntRect[theNewID];
}

Animator * Props::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

sf::IntRect Props::getAnimationZeroIntRect(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return sf::IntRect(0, 0, width, height); }
	return getTextureIntRect(mapAnimator[theAnimationID].getZeroIntRectID());
}

void Props::resetAnimation(std::string theAnimationID, sf::Time newElapsedTime)
{
	if (mapAnimator.count(theAnimationID) == 0) { return; }
	mapAnimator[theAnimationID].reset(newElapsedTime);
}

void Props::setTextureID(std::string newID)
{
	textureID = newID;
}

void Props::setSize(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
}

bool Props::addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool Props::addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, newWidth, newHeight);
	return true;
}

bool Props::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
	return true;
}

void props_js_setTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Props*)userdata)->setTextureID(v->getParameter("newID")->getString());
}

void props_js_setSize(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Props*)userdata)->setSize(v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void props_js_addPosTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Props*)userdata)->addPosTexture(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt());
}

void props_js_addTextureIntRect(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Props*)userdata)->addTextureIntRect(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt(), v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void props_js_addAnimation(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Props*)userdata)->addAnimation(v->getParameter("newID")->getString(), v->getParameter("newNbImg")->getInt(), v->getParameter("newDurationBImg")->getDouble());
}
