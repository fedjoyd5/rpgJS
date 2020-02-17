// rpgJS.cpp : définit le point d'entrée pour l'application console.
//
//  CTinyJS* TheJSContext = getNewJSContext();
//	delete TheJSContext;
//

#include "stdafx.h"

using namespace std;

unsigned int width = 1500;
unsigned int height = 800;
bool fullscreen = false;
string DirPath("");

enum Phase {
	MainMenue,
	InGame,
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
	sf::View TheView(sf::FloatRect(0,0,width,height));

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

	// ------------------ sprite loading --------------------------------

	sf::Texture playerTexture;
	playerTexture.loadFromFile(TheStoryData.getPlayer()->getTexturePath());
	sf::Sprite* spritePlayer = new sf::Sprite(playerTexture, TheStoryData.getPlayer()->getDefaultTexture());
	spritePlayer->setOrigin(doAPourcent(50, TheStoryData.getPlayer()->getWidth()), TheStoryData.getPlayer()->getHeight());

	// ------------------ meta loading --------------------------------

	sf::Image WAG;

	// ------------------ creation des bouton du menu --------------------------------
	
	sf::IntRect PlayButton(doAMap(PosXbtnPlay, bgTexture.getSize().x, width), doAMap(PosYbtnPlay, bgTexture.getSize().y, height), doAMap(btnPlay.getSize().x, bgTexture.getSize().x, width), doAMap(btnPlay.getSize().y, bgTexture.getSize().y, height));

	// ------------------ debut du programme en interaction avec le joueur --------------------------------

	bool notRightBefore = true, notLeftBefore = true, notUpBefore = true, notDownBefore = true;
	sf::Clock AnimationClock = sf::Clock();

	while (window.isOpen())
	{
		// ------------------ check des evenements --------------------------------

		sf::Event TheEvent;
		while (window.pollEvent(TheEvent)) {
			switch (TheEvent.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && ActualPhase == Phase::MainMenue){
						Carte* TheSTMap = TheStoryData.getStarter();
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
							TheView.setCenter(TheSTMap->getSpawnPosX(), TheSTMap->getSpawnPosY());

							ActualPhase = Phase::InGame;
							AnimationClock.restart();
						}
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (TheEvent.mouseButton.button == sf::Mouse::Left && ActualPhase == Phase::MainMenue && PlayButton.contains(TheEvent.mouseButton.x, TheEvent.mouseButton.y)) {
						Carte* TheSTMap = TheStoryData.getStarter();
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
							TheView.setCenter(TheSTMap->getSpawnPosX(), TheSTMap->getSpawnPosY());

							ActualPhase = Phase::InGame;
							AnimationClock.restart();
						}
					}
					break;
				default:
					break;
			}
		}

		// ------------------ check entré clavier pour les deplacement --------------------------------

		int RightLeftDepl = 0;
		int UpDownDepl = 0;
		int PosXAct = TheView.getCenter().x;
		int PosYAct = TheView.getCenter().y;
		bool notRightActivate = true, notLeftActivate = true, notUpActivate = true, notDownActivate = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ActualPhase == Phase::InGame) {
			RightLeftDepl = 1;
			if (notRightBefore) {
				Animator* TheAnim = TheStoryData.getPlayer()->getAnimation("WalkRight");
				if (TheAnim != nullptr) { TheAnim->reset(AnimationClock.getElapsedTime()); }
				notRightBefore = false;
			}
			notRightActivate = false;
			spritePlayer->setTextureRect(getTextureIntRect(TheStoryData.getPlayer(), "WalkRight", AnimationClock.getElapsedTime()));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ActualPhase == Phase::InGame) {
			RightLeftDepl = -1;
			if (notLeftBefore) {
				Animator* TheAnim = TheStoryData.getPlayer()->getAnimation("WalkLeft");
				if (TheAnim != nullptr) { TheAnim->reset(AnimationClock.getElapsedTime()); }
				notLeftBefore = false;
			}
			notLeftActivate = false;
			spritePlayer->setTextureRect(getTextureIntRect(TheStoryData.getPlayer(), "WalkLeft", AnimationClock.getElapsedTime()));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ActualPhase == Phase::InGame) {
			UpDownDepl = -1;
			if (notUpBefore) {
				Animator* TheAnim = TheStoryData.getPlayer()->getAnimation("WalkUp");
				if (TheAnim != nullptr) { TheAnim->reset(AnimationClock.getElapsedTime()); }
				notUpBefore = false;
			}
			notUpActivate = false;
			spritePlayer->setTextureRect(getTextureIntRect(TheStoryData.getPlayer(), "WalkUp", AnimationClock.getElapsedTime()));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ActualPhase == Phase::InGame) {
			UpDownDepl = 1;
			if (notDownBefore) {
				Animator* TheAnim = TheStoryData.getPlayer()->getAnimation("WalkDown");
				if (TheAnim != nullptr) { TheAnim->reset(AnimationClock.getElapsedTime()); }
				notDownBefore = false;
			}
			notDownActivate = false;
			spritePlayer->setTextureRect(getTextureIntRect(TheStoryData.getPlayer(), "WalkDown", AnimationClock.getElapsedTime()));
		}

		if (notRightActivate && !notRightBefore) { notRightBefore = true; spritePlayer->setTextureRect(TheStoryData.getPlayer()->getPosTexture("WalkRight-0")); }
		if (notLeftActivate && !notLeftBefore) { notLeftBefore = true; spritePlayer->setTextureRect(TheStoryData.getPlayer()->getPosTexture("WalkLeft-0")); }
		if (notUpActivate && !notUpBefore) { notUpBefore = true; spritePlayer->setTextureRect(TheStoryData.getPlayer()->getPosTexture("WalkUp-0")); }
		if (notDownActivate && !notDownBefore) { notDownBefore = true; spritePlayer->setTextureRect(TheStoryData.getPlayer()->getPosTexture("WalkDown-0")); }

		if (sf::FloatRect(0, 0, WAG.getSize().x, WAG.getSize().y).contains((PosXAct + RightLeftDepl), (PosYAct + UpDownDepl))) {
			bool depPasFait = true;
			if (!checkColor(WAG.getPixel((PosXAct + RightLeftDepl), (PosYAct + UpDownDepl)), sf::Color(0, 0, 0, 255))) {
				TheView.move(((float)RightLeftDepl)*TheStoryData.getPlayer()->getSpeed(), ((float)UpDownDepl)*TheStoryData.getPlayer()->getSpeed());
				depPasFait = false;
			}
			if (!checkColor(WAG.getPixel(PosXAct, (PosYAct + UpDownDepl)), sf::Color(0, 0, 0, 255)) && depPasFait) {
				TheView.move(0, ((float)UpDownDepl)*TheStoryData.getPlayer()->getSpeed());
				depPasFait = false;
			}
			if (!checkColor(WAG.getPixel((PosXAct + RightLeftDepl), PosYAct), sf::Color(0, 0, 0, 255)) && depPasFait) {
				TheView.move(((float)RightLeftDepl)*TheStoryData.getPlayer()->getSpeed(), 0);
				depPasFait = false;
			}
		}
		spritePlayer->setPosition(TheView.getCenter());

		// ------------------ traitement des info --------------------------------

		// ------------------ dessin du rendu sur la fenetre --------------------------------

		window.clear();
		switch (ActualPhase) {
		case Phase::MainMenue:
			window.draw(*BackgroundShape);
			break;
		case Phase::InGame:
			window.setView(TheView);

			window.draw(*BackgroundShape);
			window.draw(*spritePlayer);
			window.draw(*ForegroundShape);
			break;
		default:
			break;
		}
		window.display();
	}

	delete BackgroundShape;
	delete ForegroundShape;
	delete spritePlayer;

    return EXIT_SUCCESS;
}