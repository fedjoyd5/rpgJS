// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <SFML\Graphics.hpp>

#include "Gameplay.h"
#include "TIJS.h"


// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

sf::IntRect getTextureIntRect(Player* ThePl, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Trigger* TheTrigger, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Props* TheProps, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(PNJ* ThePNJ, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Monster* TheMonster, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Chest* TheChest, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));

#define INVISIBLE_INTRECT sf::IntRect(0, 0, 20, 20)
#define AFFICHE_INTRECT sf::IntRect(20, 0, 20, 20)
#define NBPX_ADD 10.0

#define BTNE_O_WIDTH 10
#define BTNE_O_HEIGHT 20

void setPositionAuDessus(sf::Sprite* InfoBtn, sf::Sprite* theObj, float height);