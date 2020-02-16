#include "PNJ.h"

using namespace std;

PNJ::PNJ()
{
	ID = "";
	Path = "";
	PosX = 0;
	PosY = 0;
}

PNJ::PNJ(string newID, string newPath, unsigned int newPosX, unsigned int newPosY)
{
	ID = newID;
	Path = newPath;
	PosX = newPosX;
	PosY = newPosY;
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

		try {
			theJSContext->execute(code);
		} catch (CScriptException *e) {
			printf("(ERROR) in %s(%s) : %s\n", ID.c_str(), (Path + ID + "/index.js").c_str(), e->text.c_str());
		}
	}
	if (theJSContext != nullptr) { delete theJSContext; }
}
