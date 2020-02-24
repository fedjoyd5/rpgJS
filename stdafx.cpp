// stdafx.cpp : fichier source incluant simplement les fichiers Include standard
// rpgJS.pch représente l'en-tête précompilé
// stdafx.obj contient les informations de type précompilées

#include "stdafx.h"

// TODO: faites référence aux en-têtes supplémentaires nécessaires dans STDAFX.H
// absents de ce fichier

using namespace std;

sf::IntRect getTextureIntRect(Player* ThePl, std::string AnimationID, sf::Time CurTime)
{
	if (ThePl == nullptr) { return sf::IntRect(0, 0, 0, 0); }
	Animator* TheAnim = ThePl->getAnimation(AnimationID);
	if (TheAnim == nullptr) { return ThePl->getDefaultTextureIntRect(); }
	TheAnim->CheckTimeAndNext(CurTime);
	return ThePl->getTextureIntRect(TheAnim->getCurIntRectID());
}

sf::IntRect getTextureIntRect(Trigger* TheTrigger, std::string AnimationID, sf::Time CurTime)
{
	if (TheTrigger == nullptr) { return sf::IntRect(0, 0, 0, 0); }
	if (TheTrigger->isSimpleTP()) { return sf::IntRect(0, 0, 0, 0); }
	Animator* TheAnim = TheTrigger->getAnimation(AnimationID);
	if (TheAnim == nullptr) { return TheTrigger->getDefaultTextureIntRect(); }
	TheAnim->CheckTimeAndNext(CurTime);
	return TheTrigger->getTextureIntRect(TheAnim->getCurIntRectID());
}

sf::IntRect getTextureIntRect(Props* TheProps, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(PNJ* ThePNJ, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(Monster* TheMonster, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

sf::IntRect getTextureIntRect(Chest* TheChest, std::string AnimationID, sf::Time CurTime)
{
	return sf::IntRect();
}

void setPositionAuDessus(sf::Sprite * InfoBtn, sf::Sprite * theObj, float height)
{
	InfoBtn->setPosition(theObj->getPosition().x, (theObj->getPosition().y - (height + NBPX_ADD)));
}
