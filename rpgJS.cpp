// rpgJS.cpp : définit le point d'entrée pour l'application console.
//
//  CTinyJS* TheJSContext = getNewJSContext();
//	delete TheJSContext;
//

#include "stdafx.h"

#define BORDER_ADD 50.0

#define BTN_DOWN sf::Keyboard::S
#define BTN_RIGHT sf::Keyboard::D
#define BTN_UP_AZERTY sf::Keyboard::Z
#define BTN_LEFT_AZERTY sf::Keyboard::Q
#define BTN_UP_QWERTY sf::Keyboard::W
#define BTN_LEFT_QWERTY sf::Keyboard::A

using namespace std;

unsigned int width = 1500;
unsigned int height = 800;
bool fullscreen = false;
bool azertyuiop = true;
string DirPath("");

enum Phase {
	MainMenue,
	InGame,
	InCinematique,
	InInventory,
	InPause,
};
Phase ActualPhase = MainMenue;

string StoryID = "rpgJS";
gameStoryData TheStoryData;

int main(int argc, char *argv[])
{
	for (int indeArg = 1; indeArg < argc; indeArg++) {
		string curArg(argv[indeArg]);
		if (curArg == "-w" && argc > (indeArg + 1)) {
			indeArg++;
			width = atoi(argv[indeArg]);
		}
		if (curArg == "-h" && argc > (indeArg + 1)) {
			indeArg++;
			height = atoi(argv[indeArg]);
		}
		if (curArg == "-DP" && argc > (indeArg + 1)) {
			indeArg++;
			DirPath = string(argv[indeArg]);
		}
		if (curArg == "-s" && argc > (indeArg + 1)) {
			indeArg++;
			StoryID = string(argv[indeArg]);
		}
		if (curArg == "-fullscreen") { fullscreen = true; }
		if (curArg == "-zqsd") { azertyuiop = true; }
		if (curArg == "-wasd") { azertyuiop = false; }
	}

	// ------------------ chargement de l'histoire --------------------------------

	printf("start loading story ...\n\n");
	TheStoryData = gameStoryData((DirPath + "story/"), StoryID);
	printf("\nstory \"%s\" loaded !!\n", TheStoryData.getID().c_str());
	printf("Name : %s\n", TheStoryData.getName().c_str());
	printf("Version : %s\n\n", TheStoryData.getVersion().c_str());

	//Item* theIte = TheStoryData.getItem("hache");
	//if (theIte != nullptr) { printf("item \"hache\" : %s(%0.3f)\n", theIte->getName().c_str(), theIte->getWeight()); }

	//Carte* theIte = TheStoryData.getCarte("starter");
	//if (theIte != nullptr) { printf("map \"starter\" : %s(%i, %i)\n", theIte->getName().c_str(), theIte->getSpawnPosX(), theIte->getSpawnPosY()); }

	// ------------------ creation fenetre (et vue) --------------------------------

	sf::RenderWindow window(sf::VideoMode(width, height), StoryID, (fullscreen ? sf::Style::Fullscreen : sf::Style::Default));
	width = window.getSize().x;
	height = window.getSize().y;
	sf::View TheView(sf::FloatRect(0, 0, width, height));

	// ------------------ creation du BG et du FG (et chargment du menu) --------------------------------

	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile(DirPath + "base/backgroundMM.png")) { printf("il y a eu une erreur lors du chargement du background"); }

	sf::Image btnPlay;
	btnPlay.loadFromFile(DirPath + "base/btnPlay.png");
	unsigned int PosXbtnPlay = doAPourcentWithCenter(50, bgTexture.getSize().x, btnPlay.getSize().x);
	unsigned int PosYbtnPlay = doAPourcentWithCenter(75, bgTexture.getSize().y, btnPlay.getSize().y);
	bgTexture.update(btnPlay, PosXbtnPlay, PosYbtnPlay);

	//if (!bgTexture.loadFromFile(TheStoryData.getStarter()->getBackgroundPath())) { printf("il y a eu une erreur lors du chargement du background"); }
	sf::RectangleShape* BackgroundShape = new sf::RectangleShape(sf::Vector2f(width, height));
	BackgroundShape->setTexture(&bgTexture);
	//BackgroundShape->setFillColor(sf::Color::Blue);
	//BackgroundShape->setOutlineThickness(10);
	//BackgroundShape->setOutlineColor(sf::Color::Cyan);

	sf::Texture fgTexture;
	if (!fgTexture.loadFromFile(DirPath + "base/backgroundMM.png")) { printf("il y a eu une erreur lors du chargement du foreground"); }
	//if (!fgTexture.loadFromFile(TheStoryData.getStarter()->getForegroundPath())) { printf("il y a eu une erreur lors du chargement du foreground"); }
	sf::RectangleShape* ForegroundShape = new sf::RectangleShape(sf::Vector2f(fgTexture.getSize()));
	ForegroundShape->setTexture(&fgTexture);

	// ----------------------------------------------------------------

	vector<sf::Texture*> staticTextureList;
	staticTextureList.push_back(new sf::Texture());
	staticTextureList[0]->loadFromFile(TheStoryData.getPlayer()->getTexturePath());
	TheStoryData.getPlayer()->setTexture(*staticTextureList[0]);

	vector<sf::Texture*> DynamicTextureList;

	// ------------------ meta loading --------------------------------

	sf::Image WAG;

	// ------------------ creation des bouton du menu --------------------------------
	
	sf::IntRect PlayButton(doAMap(PosXbtnPlay, bgTexture.getSize().x, width), doAMap(PosYbtnPlay, bgTexture.getSize().y, height), doAMap(btnPlay.getSize().x, bgTexture.getSize().x, width), doAMap(btnPlay.getSize().y, bgTexture.getSize().y, height));

	// ------------------ debut du programme en interaction avec le joueur --------------------------------

	sf::Clock Timer = sf::Clock();
	vector<string> theChestLST, theMonsterLST, thePNJLST, thePropsLST, theTriggerLST;
	Carte* TheSTMap = nullptr;

	/*sf::Clock Fpscounter = sf::Clock();
	int theCounter = 0;*/

	while (window.isOpen())
	{
		/*theCounter = theCounter + 1;
		if (Fpscounter.getElapsedTime() >= sf::seconds(1.0)) {
			printf("- %i image/s\n", theCounter);
			Fpscounter.restart();
			theCounter = 0;
		}*/

		// ------------------ check des evenements --------------------------------

		sf::Event TheEvent;
		while (window.pollEvent(TheEvent)) {
			switch (TheEvent.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
				case sf::Event::KeyPressed:
					if((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && ActualPhase == Phase::MainMenue) || (TheEvent.mouseButton.button == sf::Mouse::Left && ActualPhase == Phase::MainMenue && PlayButton.contains(TheEvent.mouseButton.x, TheEvent.mouseButton.y))){
						TheSTMap = TheStoryData.getStarter();
						if (TheSTMap != nullptr) {
							//printf("loading \"%s\"\n", TheSTMap->getBackgroundPath().c_str());
							//printf("loading \"%s\"\n", TheSTMap->getForegroundPath().c_str());

							bgTexture.loadFromFile(TheSTMap->getBackgroundPath());
							delete BackgroundShape;
							BackgroundShape = new sf::RectangleShape(sf::Vector2f(bgTexture.getSize()));
							BackgroundShape->setTexture(&bgTexture);
							//BackgroundShape->setFillColor(sf::Color::Blue);
							//BackgroundShape->setOutlineThickness(10);
							//BackgroundShape->setOutlineColor(sf::Color::Cyan);

							fgTexture.loadFromFile(TheSTMap->getForegroundPath());
							delete ForegroundShape;
							ForegroundShape = new sf::RectangleShape(sf::Vector2f(fgTexture.getSize()));
							ForegroundShape->setTexture(&fgTexture);

							//printf("BackgroundShape size X: %0.2f, Y: %0.2f\n", BackgroundShape.getSize().x, BackgroundShape.getSize().y);
							//printf("ForegroundShape size X: %0.2f, Y: %0.2f\n", ForegroundShape.getSize().x, ForegroundShape.getSize().y);

							WAG.loadFromFile(TheSTMap->getWalkAbleGridPath());
							TheStoryData.getPlayer()->setPosition(TheSTMap->getSpawnPosX(), TheSTMap->getSpawnPosY());
							//TheView.setCenter(TheSTMap->getSpawnPosX(), TheSTMap->getSpawnPosY());

							for (unsigned int dTextureIndex = 0; dTextureIndex < DynamicTextureList.size(); dTextureIndex++) { delete DynamicTextureList[dTextureIndex]; }
							DynamicTextureList.clear();

							theChestLST = TheSTMap->getChestIdList();
							for (unsigned int theIndex = 0; theIndex < theChestLST.size(); theIndex++) {
								Chest* curChest = TheSTMap->getChest(theChestLST[theIndex]);
								unsigned int tempChestInd = DynamicTextureList.size();
								DynamicTextureList.push_back(new sf::Texture());
								DynamicTextureList[tempChestInd]->loadFromFile(curChest->getTexturePath());
								curChest->setTexture(*DynamicTextureList[tempChestInd]);
							}

							theMonsterLST = TheSTMap->getMonsterIdList();
							for (unsigned int theIndex = 0; theIndex < theMonsterLST.size(); theIndex++) {
								Monster* curMonster = TheSTMap->getMonster(theMonsterLST[theIndex]);
								unsigned int tempMonsterInd = DynamicTextureList.size();
								DynamicTextureList.push_back(new sf::Texture());
								DynamicTextureList[tempMonsterInd]->loadFromFile(curMonster->getTexturePath());
								curMonster->setTexture(*DynamicTextureList[tempMonsterInd]);
							}

							thePNJLST = TheSTMap->getPNJIdList();
							for (unsigned int theIndex = 0; theIndex < thePNJLST.size(); theIndex++) {
								PNJ* curPNJ = TheSTMap->getPNJ(thePNJLST[theIndex]);
								unsigned int tempPNJInd = DynamicTextureList.size();
								DynamicTextureList.push_back(new sf::Texture());
								DynamicTextureList[tempPNJInd]->loadFromFile(curPNJ->getTexturePath());
								curPNJ->setTexture(*DynamicTextureList[tempPNJInd]);
							}

							thePropsLST = TheSTMap->getPropsIdList();
							for (unsigned int theIndex = 0; theIndex < thePropsLST.size(); theIndex++) {
								Props* curProps = TheSTMap->getProps(thePropsLST[theIndex]);
								unsigned int tempPropsInd = DynamicTextureList.size();
								DynamicTextureList.push_back(new sf::Texture());
								DynamicTextureList[tempPropsInd]->loadFromFile(curProps->getTexturePath());
								curProps->setTexture(*DynamicTextureList[tempPropsInd]);
							}

							theTriggerLST = TheSTMap->getTriggerIdList();
							for (unsigned int theIndex = 0; theIndex < theTriggerLST.size(); theIndex++) {
								Trigger* curTrigger = TheSTMap->getTrigger(theTriggerLST[theIndex]);
								if (!curTrigger->isSimpleTP()) {
									unsigned int tempTriggerInd = DynamicTextureList.size();
									DynamicTextureList.push_back(new sf::Texture());
									DynamicTextureList[tempTriggerInd]->loadFromFile(curTrigger->getTexturePath());
									curTrigger->setTexture(*DynamicTextureList[tempTriggerInd]);
								}
							}

							ActualPhase = Phase::InGame;
							Timer.restart();
						}
					}
					break;
				default:
					break;
			}
		}

		// ------------------ player move (phase -> InGame) --------------------------------

		if (ActualPhase == Phase::InGame && TheStoryData.getPlayer() != nullptr) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(BTN_RIGHT)) { TheStoryData.getPlayer()->moveRight(Timer.getElapsedTime()); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(azertyuiop ? BTN_LEFT_AZERTY : BTN_LEFT_QWERTY)) { TheStoryData.getPlayer()->moveLeft(Timer.getElapsedTime()); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(azertyuiop ? BTN_UP_AZERTY : BTN_UP_QWERTY)) { TheStoryData.getPlayer()->moveUp(Timer.getElapsedTime()); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(BTN_DOWN)) { TheStoryData.getPlayer()->moveDown(Timer.getElapsedTime()); }

			TheStoryData.getPlayer()->checkMove(WAG);
			TheView.setCenter(TheStoryData.getPlayer()->getPosition());
		}

		// ------------------ TheView move (phase -> InCinematique) --------------------------------

		if (ActualPhase == Phase::InCinematique) {}

		// ------------------ traitement des info --------------------------------------------------

		// ------------------ dessin du rendu sur la fenetre ---------------------------------------

		sf::FloatRect floatRectVeiw(TheView.getCenter().x - (((double)width / 2) + BORDER_ADD), TheView.getCenter().y - (((double)height / 2) + BORDER_ADD), width + (BORDER_ADD*2), height + (BORDER_ADD*2));

		window.clear();
		switch (ActualPhase) {
		case Phase::MainMenue:
			window.draw(*BackgroundShape);
			break;
		case Phase::InCinematique:
		case Phase::InGame:
			window.setView(TheView);

			window.draw(*BackgroundShape);
			for (unsigned int it = 0; it < theChestLST.size(); it++) {
				Chest* theChest = TheSTMap->getChest(theChestLST[it]);
				if (floatRectVeiw.contains(theChest->getPosition())) { window.draw(*theChest); }
			}
			for (unsigned int it = 0; it < theMonsterLST.size(); it++) {
				Monster* theMonster = TheSTMap->getMonster(theMonsterLST[it]);
				if (floatRectVeiw.contains(theMonster->getPosition())) { window.draw(*theMonster); }
			}
			for (unsigned int it = 0; it < thePNJLST.size(); it++) {
				PNJ* thePNJ = TheSTMap->getPNJ(thePNJLST[it]);
				if (floatRectVeiw.contains(thePNJ->getPosition())) { window.draw(*thePNJ); }
			}
			for (unsigned int it = 0; it < thePropsLST.size(); it++) {
				Props* theProps = TheSTMap->getProps(thePropsLST[it]);
				if (floatRectVeiw.contains(theProps->getPosition())) { window.draw(*theProps); }
			}
			for (unsigned int it = 0; it < theTriggerLST.size(); it++) {
				Trigger* theTrigger = TheSTMap->getTrigger(theTriggerLST[it]);
				if (floatRectVeiw.contains(theTrigger->getPosition())) { window.draw(*theTrigger); }
			}
			window.draw(*TheStoryData.getPlayer());
			//window.draw(*ForegroundShape);
			break;
		default:
			break;
		}
		window.display();
	}

	delete BackgroundShape;
	delete ForegroundShape;
	for (unsigned int sTextureIndex = 0; sTextureIndex < staticTextureList.size(); sTextureIndex++) { delete staticTextureList[sTextureIndex]; }
	staticTextureList.clear();
	for (unsigned int dTextureIndex = 0; dTextureIndex < DynamicTextureList.size(); dTextureIndex++) { delete DynamicTextureList[dTextureIndex]; }
	DynamicTextureList.clear();
	
    return EXIT_SUCCESS;
}