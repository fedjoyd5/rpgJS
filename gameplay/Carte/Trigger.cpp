#include "Trigger.h"

using namespace std;

Trigger::Trigger()
{
	ID = "";
	Path = "";

	Activateur = sf::FloatRect(0, 0, 0, 0);
	textureID = "";
	width = 0;
	height = 0;

	simpleTp = false;
	simpleTpMap = "";
	simpleTpArrID = "";
}

Trigger::Trigger(string newID, string newPath, float newPosX, float newPosY)
{
	ID = newID;
	Path = newPath;
	setPosition(newPosX, newPosY);

	Activateur = sf::FloatRect(newPosX, newPosY, 0, 0);
	textureID = "";
	width = 0;
	height = 0;

	simpleTp = false;
	simpleTpMap = "";
	simpleTpArrID = "";
}

Trigger::Trigger(string newID, float newPosX, float newPosY, unsigned int newWidth, unsigned int newHeight, string newSimpleTpMap, string newSimpleTpArrID)
{
	ID = newID;
	Path = "";
	setPosition(newPosX, newPosY);
	width = newWidth;
	height = newHeight;

	Activateur = sf::FloatRect(newPosX, newPosY, newWidth, newHeight);
	textureID = "";

	simpleTp = true;
	simpleTpMap = newSimpleTpMap;
	simpleTpArrID = newSimpleTpArrID;
}


Trigger::~Trigger()
{
}

std::string Trigger::getID()
{
	return ID;
}

void Trigger::initialize()
{
	CTinyJS* theJSContext = nullptr;
	if (simpleTp) { return; }
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Trigger.setTexture(newID)", &trigger_js_setTexture, this);
		theJSContext->addNative("function Trigger.setSize(newWidth, newHeight)", &trigger_js_setSize, this);
		theJSContext->addNative("function Trigger.addPosTexture(newID, newPosX, newPosY)", &trigger_js_addPosTexture, this);
		theJSContext->addNative("function Trigger.addTextureIntRect(newID, newPosX, newPosY, newWidth, newHeight)", &trigger_js_addTextureIntRect, this);
		theJSContext->addNative("function Trigger.addAnimation(newID, newNbImg, newDurationBImg)", &trigger_js_addAnimation, this);

		try {
			theJSContext->execute(code);
		} catch (CScriptException *e) {
			printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
		}

		setTextureRect(getDefaultTextureIntRect());
		setOrigin(0, 0);
	}
	if (theJSContext != nullptr) { delete theJSContext; }
}

bool Trigger::CheckIsIn(sf::Vector2f posToCheck)
{
	return Activateur.contains(posToCheck);
}

bool Trigger::isSimpleTP()
{
	return simpleTp;
}

string Trigger::getSimpleTPMap()
{
	return simpleTpMap;
}

string Trigger::getSimpleTPArrID()
{
	return simpleTpArrID;
}

unsigned int Trigger::getWidth()
{
	return Activateur.width;
}

unsigned int Trigger::getHeight()
{
	return Activateur.height;
}

std::string Trigger::getTexturePath()
{
	return (Path + ID + "/" + textureID);
}

sf::IntRect Trigger::getTextureIntRect(std::string theIntRectID)
{
	if (mapTextureIntRect.count(theIntRectID) == 0) {
		theIntRectID = "default";
		if (mapTextureIntRect.count(theIntRectID) == 0) { return sf::IntRect(0, 0, width, height); }
	}
	return mapTextureIntRect[theIntRectID];
}

sf::IntRect Trigger::getDefaultTextureIntRect()
{
	string theNewID = "default";
	if (mapTextureIntRect.count(theNewID) == 0) { return sf::IntRect(0, 0, width, height); }
	return mapTextureIntRect[theNewID];
}

Animator * Trigger::getAnimation(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return nullptr; }
	return &(mapAnimator[theAnimationID]);
}

sf::IntRect Trigger::getAnimationZeroIntRect(std::string theAnimationID)
{
	if (mapAnimator.count(theAnimationID) == 0) { return sf::IntRect(0, 0, width, height); }
	return getTextureIntRect(mapAnimator[theAnimationID].getZeroIntRectID());
}

void Trigger::resetAnimation(std::string theAnimationID, sf::Time newElapsedTime)
{
	if (mapAnimator.count(theAnimationID) == 0) { return; }
	mapAnimator[theAnimationID].reset(newElapsedTime);
}

void Trigger::setTextureID(std::string newID)
{
	textureID = newID;
}

void Trigger::setSize(unsigned int newWidth, unsigned int newHeight)
{
	width = newWidth;
	height = newHeight;
	Activateur = sf::FloatRect(getPosition().x, getPosition().y, newWidth, newHeight);
}

bool Trigger::addPosTexture(std::string newID, unsigned int newPosX, unsigned int newPosY)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, width, height);
	return true;
}

bool Trigger::addTextureIntRect(std::string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight)
{
	if (mapTextureIntRect.count(newID) == 1) { return false; }
	mapTextureIntRect[newID] = sf::IntRect(newPosX, newPosY, newWidth, newHeight);
	return true;
}

bool Trigger::addAnimation(std::string newAnimationID, unsigned int newNbImage, float newDurationBImg)
{
	if (mapAnimator.count(newAnimationID) == 1) { return false; }
	mapAnimator[newAnimationID] = Animator(newAnimationID, newNbImage, newDurationBImg);
	return true;
}

// ----------------------------------------

void trigger_js_setTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->setTextureID(v->getParameter("newID")->getString());
}

void trigger_js_setSize(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->setSize(v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void trigger_js_addPosTexture(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->addPosTexture(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt());
}

void trigger_js_addTextureIntRect(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->addTextureIntRect(v->getParameter("newID")->getString(), v->getParameter("newPosX")->getInt(), v->getParameter("newPosY")->getInt(), v->getParameter("newWidth")->getInt(), v->getParameter("newHeight")->getInt());
}

void trigger_js_addAnimation(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->addAnimation(v->getParameter("newID")->getString(), v->getParameter("newNbImg")->getInt(), v->getParameter("newDurationBImg")->getDouble());
}
