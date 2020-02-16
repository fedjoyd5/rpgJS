#include "Item.h"

using namespace std;

Item::Item()
{
	ID = "";
	Path = "";
	Name = "";
	Weight = 0.0;
}

Item::Item(std::string newPath, std::string newID)
{
	ID = newID;
	Path = newPath;
	Name = "";
	Weight = 0.0;
}

Item::Item(string newID, string newName, double newWeight)
{
	ID = newID;
	Path = "";
	Name = newName;
	Weight = newWeight;
}


Item::~Item()
{
}

string Item::getID()
{
	return ID;
}

string Item::getName()
{
	return Name;
}

double Item::getWeight()
{
	return Weight;
}

void Item::initialize()
{
	CTinyJS* theJSContext = nullptr;
	string code = getCodeFromFiles(Path + ID + "/index.js");
	if (!code.empty()) {
		theJSContext = getNewJSContext();
		theJSContext->addNative("function Item.setName(newName)", &item_js_setName, this);
		theJSContext->addNative("function Item.setWeight(newWeight)", &item_js_setWeight, this);

		try {
			theJSContext->execute(code);
		} catch (CScriptException *e) {
			printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
		}
	}
	if (theJSContext != nullptr) { delete theJSContext; }
}

bool Item::setName(std::string newName)
{
	Name = newName;
	//printf("item new name \"%s\"", Name.c_str());
	return true;
}

bool Item::setWeight(double newWeight)
{
	Weight = newWeight;
	//printf("item new weight \"%0.2f\"", Weight);
	return true;
}

// ---------------------------------------

void item_js_setName(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Item*)userdata)->setName(v->getParameter("newName")->getString());
}

void item_js_setWeight(CScriptVar * v, void * userdata)
{
	if (userdata == nullptr) { return; }
	((Item*)userdata)->setWeight(v->getParameter("newWeight")->getDouble());
}
