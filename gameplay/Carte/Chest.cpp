#include "Chest.h"

using namespace std;

Chest::Chest()
{
	ID = "";
	Path = "";
	textureID = "";
	width = 0;
	height = 0;
}

Chest::Chest(string newID, string newPath, float newPosX, float newPosY)
{
	ID = newID;
	Path = newPath;
	setPosition(newPosX, newPosY);
	textureID = "";
	width = 0;
	height = 0;
}


Chest::~Chest()
{
}


std::string Chest::getID()
{
	return ID;
}

void Chest::initialize()
{
	CTinyJS* theJSContext = nullptr;
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Chest.setTexture(newID)", &chest_js_setTexture, this);
		theJSContext->addNative("function Chest.setSize(newWidth, newHeight)", &chest_js_setSize, this);
		theJSContext->addNative("function Chest.addPosTexture(newID, newPosX, newPosY)", &chest_js_addPosTexture, this);
		theJSContext->addNative("function Chest.addTextureIntRect(newID, newPosX, newPosY, newWidth, newHeight)", &chest_js_addTextureIntRect, this);
		theJSContext->addNative("function Chest.addAnimation(newID, newNbImg, newDurationBImg)", &chest_js_addAnimation, this);

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

unsigned int Chest::getWidth()
{
	return width;
}

unsigned int Chest::getHeight()
{
	return height;
}

bool Chest::canInteract(sf::Vector2f playerPos)
{
	sf::FloatRect theRectToTest(getPosition().x - (((float)width / 2) + RAYON_TO_ACTIVATE), getPosition().y - ((float)height + RAYON_TO_ACTIVATE), (width + (2 * RAYON_TO_ACTIVATE)), (height + (2 * RAYON_TO_ACTIVATE)));
	return theRectToTest.contains(playerPos);
}

std::string Chest::getTexturePath()
{
	return (Path + ID + "/" + textureID);
}

sf::IntRect Chest::getTextureIntRect(std::string theIntRectID)
{
	if (mapTextureIntRect.count(theIntRectID) == 0) {
		theIntRectID = "default";
		if (mapTextureIntRect.count(theIntRectID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapTextureIntRect[theIntRectID];
}

sf::IntRect Chest::getDefaultTextureIntRect()
{
	string theNewID = "default";
	if (mapTextureIntRect.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapTextureIntRect[theNewID];
}

Animator * Chest::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

sf::IntRect Chest::getAnimationZeroIntRect(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return sf::IntRect(0, 0, width, height); }
	return getTextureIntRect(mapAnimator[theAnimationID].getZeroIntRectID());
}

void Chest::resetAnimation(std::string theAnimationID, sf::Time newElapsedTime)
{
	if (mapAnimator.count(theAnimationID) == 0) { return; }
	mapAnimator[theAnimationID].reset(newElapsedTime);
}

void Chest::setTextureID(std::string newID)
{
	textureID = newID;
}

void Chest::setSize(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
}

bool Chest::addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool Chest::addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, newWidth, newHeight);
	return true;
}

bool Chest::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
	return true;
}

void chest_js_setTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Chest*)userdata)->setTextureID(v->getParameter("newID")->getString());
}

void chest_js_setSize(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Chest*)userdata)->setSize(v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void chest_js_addPosTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Chest*)userdata)->addPosTexture(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt());
}

void chest_js_addTextureIntRect(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Chest*)userdata)->addTextureIntRect(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt(), v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void chest_js_addAnimation(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Chest*)userdata)->addAnimation(v->getParameter("newID")->getString(), v->getParameter("newNbImg")->getInt(), v->getParameter("newDurationBImg")->getDouble());
}
