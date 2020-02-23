#include "TIJS.h"

using namespace std;

bool checkColor(sf::Color ToTest1, sf::Color ToTest2)
{
	if (ToTest1.r != ToTest2.r) { return false; }
	if (ToTest1.g != ToTest2.g) { return false; }
	if (ToTest1.b != ToTest2.b) { return false; }
	if (ToTest1.a != ToTest2.a) { return false; }
	return true;
}

int doAPourcent(double Pourcent, int Maximum) {
	return (int)((double)Maximum * (Pourcent / 100));
}

int doAPourcentWithCenter(double Pourcent, int Maximum, int objTaille) {
	return (doAPourcent(Pourcent, Maximum) - (int)((double)objTaille / 2));
}


int doAMap(int Cur, int MaxDep, int MaxArr) {
	return doAMap(Cur, 0, MaxDep, 0, MaxArr);
}
int doAMap(int Cur, int MinDep, int MaxDep, int MinArr, int MaxArr) {
	double Pourcent = ((double)(Cur - MinDep) / (double)(MaxDep - MinDep));
	return (int)((Pourcent * (MaxArr - MinArr)) + MinArr);
}

CTinyJS* getNewJSContext() {
	CTinyJS *js = new CTinyJS();
	/* add the functions from TinyJS_Functions.cpp */
	registerFunctions(js);
	registerMathFunctions(js);
	/* Add a native function */
	js->addNative("function print(text)", &js_print, nullptr);

	js->addNative("function Global.setBoolVar(newID, newBool)", &js_setBoolVar, nullptr);
	js->addNative("function Global.getBoolVar(theID)", &js_getBoolVar, nullptr);
	js->addNative("function Global.remBoolVar(theID)", &js_remBoolVar, nullptr);

	js->addNative("function Global.setIntVar(newID, newInt)", &js_setIntVar, nullptr);
	js->addNative("function Global.getIntVar(theID)", &js_getIntVar, nullptr);
	js->addNative("function Global.remIntVar(theID)", &js_remIntVar, nullptr);

	js->addNative("function Global.setDoubleVar(newID, newDouble)", &js_setDoubleVar, nullptr);
	js->addNative("function Global.getDoubleVar(theID)", &js_getDoubleVar, nullptr);
	js->addNative("function Global.remDoubleVar(theID)", &js_remDoubleVar, nullptr);

	js->addNative("function Global.setStringVar(newID, newString)", &js_setStringVar, nullptr);
	js->addNative("function Global.getStringVar(theID)", &js_getStringVar, nullptr);
	js->addNative("function Global.remStringVar(theID)", &js_remStringVar, nullptr);

	return js;
}


void js_print(CScriptVar *v, void *userdata) {
	printf("> %s\n", v->getParameter("text")->getString().c_str());
}

string getCodeFromFiles(string Path) {
	ifstream TheFileToRead(Path.c_str());
	string toRet = "";
	if (TheFileToRead) {
		string CurLigne = "";
		bool isFirst = true;
		while (getline(TheFileToRead, CurLigne)) { toRet = ((isFirst ? "" : toRet + "\n") + CurLigne); if (isFirst) { isFirst = false; } }
	}
	else { printf("ERROR : impossible d'ouvrire \"%s\"\n", Path.c_str()); }
	return toRet;
}

vector<string> getListExtension(string Path) {
	ifstream ExtListFile(Path.c_str());
	vector<string> toRet(0);
	if (ExtListFile) {
		string CurLigne = "";
		while (getline(ExtListFile, CurLigne)) { toRet.push_back(CurLigne); }
	}
	else { printf("ERROR : impossible d'ouvrire \"%s\"\n", Path.c_str()); }
	return toRet;
}


// ---------- global bool var ----------

// function Global.setBoolVar(newID, newBool)
void js_setBoolVar(CScriptVar * v, void * userdata)
{
	globalBoolVar[v->getParameter("newID")->getString()] = v->getParameter("newBool")->getBool();
}

// function Global.getBoolVar(theID)
void js_getBoolVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalBoolVar.count(theID) == 0) { return; }
	v->getReturnVar()->setInt(globalBoolVar[theID]);
}

// function Global.remBoolVar(theID)
void js_remBoolVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalBoolVar.count(theID) == 0) { return; }
	globalBoolVar.erase(theID);
}

// ---------- global int var ----------

// function Global.setIntVar(newID, newInt)
void js_setIntVar(CScriptVar * v, void * userdata)
{
	globalIntVar[v->getParameter("newID")->getString()] = v->getParameter("newInt")->getInt();
}

// function Global.getIntVar(theID)
void js_getIntVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalIntVar.count(theID) == 0) { return; }
	v->getReturnVar()->setInt(globalIntVar[theID]);
}

// function Global.remIntVar(theID)
void js_remIntVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalIntVar.count(theID) == 0) { return; }
	globalIntVar.erase(theID);
}

// ---------- global double var ----------

// function Global.setDoubleVar(newID, newDouble)
void js_setDoubleVar(CScriptVar * v, void * userdata)
{
	globalDoubleVar[v->getParameter("newID")->getString()] = v->getParameter("newDouble")->getDouble();
}

// function Global.getDoubleVar(theID)
void js_getDoubleVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalDoubleVar.count(theID) == 0) { return; }
	v->getReturnVar()->setDouble(globalDoubleVar[theID]);
}

// function Global.remDoubleVar(theID)
void js_remDoubleVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalDoubleVar.count(theID) == 0) { return; }
	globalDoubleVar.erase(theID);
}

// ---------- global string var ----------

// function Global.setStringVar(newID, newString)
void js_setStringVar(CScriptVar * v, void * userdata)
{
	globalStringVar[v->getParameter("newID")->getString()] = v->getParameter("newString")->getString();
}

// function Global.getStringVar(theID)
void js_getStringVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalStringVar.count(theID) == 0) { return; }
	v->getReturnVar()->setString(globalStringVar[theID]);
}

// function Global.remStringVar(theID)
void js_remStringVar(CScriptVar * v, void * userdata)
{
	string theID = v->getParameter("theID")->getString();
	if (globalStringVar.count(theID) == 0) { return; }
	globalStringVar.erase(theID);
}
