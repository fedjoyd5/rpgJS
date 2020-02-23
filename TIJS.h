#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <SFML/Graphics/Color.hpp>

#include "TJS\TinyJS.h"
#include "TJS\TinyJS_Functions.h"
#include "TJS\TinyJS_MathFunctions.h"

#define WALKUP_AN "WalkUp"
#define WALKDOWN_AN "WalkDown"
#define WALKRIGHT_AN "WalkRight"
#define WALKLEFT_AN "WalkLeft"
#define NO_WALK_COLOR sf::Color(0, 0, 0, 255)

bool checkColor(sf::Color ToTest1, sf::Color ToTest2);

int doAPourcent(double Pourcent, int Maximum);
int doAPourcentWithCenter(double Pourcent, int Maximum, int objTaille);
int doAMap(int Cur, int MaxDep, int MaxArr);
int doAMap(int Cur, int MinDep, int MaxDep, int MinArr, int MaxArr);

CTinyJS* getNewJSContext();

void js_print(CScriptVar *v, void *userdata);

std::string getCodeFromFiles(std::string Path);
std::vector<std::string> getListExtension(std::string Path);

static std::map<std::string, bool> globalBoolVar;
void js_setBoolVar(CScriptVar *v, void *userdata);
void js_getBoolVar(CScriptVar *v, void *userdata);
void js_remBoolVar(CScriptVar *v, void *userdata);

static std::map<std::string, int> globalIntVar;
void js_setIntVar(CScriptVar *v, void *userdata);
void js_getIntVar(CScriptVar *v, void *userdata);
void js_remIntVar(CScriptVar *v, void *userdata);

static std::map<std::string, double> globalDoubleVar;
void js_setDoubleVar(CScriptVar *v, void *userdata);
void js_getDoubleVar(CScriptVar *v, void *userdata);
void js_remDoubleVar(CScriptVar *v, void *userdata);

static std::map<std::string, std::string> globalStringVar;
void js_setStringVar(CScriptVar *v, void *userdata);
void js_getStringVar(CScriptVar *v, void *userdata);
void js_remStringVar(CScriptVar *v, void *userdata);