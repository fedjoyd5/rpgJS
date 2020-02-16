// stdafx.cpp : fichier source incluant simplement les fichiers Include standard
// rpgJS.pch représente l'en-tête précompilé
// stdafx.obj contient les informations de type précompilées

#include "stdafx.h"

// TODO: faites référence aux en-têtes supplémentaires nécessaires dans STDAFX.H
// absents de ce fichier

using namespace std;

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

bool checkColor(sf::Color ToTest1, sf::Color ToTest2)
{
	if (ToTest1.r != ToTest2.r) { return false; }
	if (ToTest1.g != ToTest2.g) { return false; }
	if (ToTest1.b != ToTest2.b) { return false; }
	if (ToTest1.a != ToTest2.a) { return false; }
	return true;
}

sf::IntRect getTextureIntRect(Player * ThePl, std::string AnimationID, sf::Time CurTime)
{
	if (ThePl == nullptr) { return sf::IntRect(0, 0, 0, 0); }
	Animator* TheAnim = ThePl->getAnimation(AnimationID);
	if (TheAnim == nullptr) { return ThePl->getDefaultTexture(); }
	TheAnim->CheckTimeAndNext(CurTime);
	return ThePl->getPosTexture(TheAnim->getCurID());
}

sf::IntRect getTextureIntRect(Trigger * TheTrigger, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(Props * TheProps, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(PNJ * ThePNJ, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(Monster * TheMonster, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(Chest * TheChest, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}
