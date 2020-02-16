#include "Trigger.h"

using namespace std;

Trigger::Trigger()
{
	ID = "";
	Path = "";
	PosX = 0;
	PosY = 0;
	simpleTp = false;
	simpleTpMap = "";
	simpleTpArrID = "";
}

Trigger::Trigger(string newID, string newPath, unsigned int newPosX, unsigned int newPosY)
{
	ID = newID;
	Path = newPath;
	PosX = newPosX;
	PosY = newPosY;
	Width = 0;
	Height = 0;
	simpleTp = false;
	simpleTpMap = "";
	simpleTpArrID = "";
}

Trigger::Trigger(string newID, unsigned int newPosX, unsigned int newPosY, unsigned int newWidth, unsigned int newHeight, string newSimpleTpMap, string newSimpleTpArrID)
{
	ID = newID;
	Path = "";
	PosX = newPosX;
	PosY = newPosY;
	Width = newWidth;
	Height = newHeight;
	simpleTp = true;
	simpleTpMap = newSimpleTpMap;
	simpleTpArrID = newSimpleTpArrID;
}


Trigger::~Trigger()
{
}

void Trigger::initialize()
{
	CTinyJS* theJSContext = nullptr;
	if (simpleTp) { return; }
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Trigger.setWidth(newWidth)", &trigger_js_setWidth, this);
		theJSContext->addNative("function Trigger.setHeight(newHeight)", &trigger_js_setHeight, this);

		try {
			theJSContext->execute(code);
		} catch (CScriptException *e) {
			printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
		}
	}
	if (theJSContext != nullptr) { delete theJSContext; }
}

bool Trigger::CheckIsIn(unsigned int testPosX, unsigned int testPosY)
{
	if (testPosX < PosX || testPosX > (PosX + Width)) { return false; }
	if (testPosY < PosY || testPosY > (PosY + Height)) { return false; }
	return true;
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

void Trigger::setWidth(unsigned int newWidth)
{
	Width = newWidth;
}

void Trigger::setHeight(unsigned int newHeight)
{
	Height = newHeight;
}

// ----------------------------------------

void trigger_js_setWidth(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->setWidth(v->getParameter("newWidth")->getInt());
}

void trigger_js_setHeight(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Trigger*)userdata)->setHeight(v->getParameter("newHeight")->getInt());
}
