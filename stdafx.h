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

int doAPourcent(double Pourcent, int Maximum);
int doAPourcentWithCenter(double Pourcent, int Maximum, int objTaille);
int doAMap(int Cur, int MaxDep, int MaxArr);
int doAMap(int Cur, int MinDep, int MaxDep, int MinArr, int MaxArr);

bool checkColor(sf::Color ToTest1, sf::Color ToTest2);

sf::IntRect getTextureIntRect(Player* ThePl, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Trigger* TheTrigger, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Props* TheProps, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(PNJ* ThePNJ, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Monster* TheMonster, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));
sf::IntRect getTextureIntRect(Chest* TheChest, std::string AnimationID, sf::Time CurTime = sf::seconds(0.0));