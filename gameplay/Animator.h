#pragma once

#include <string>
#include <map>
#include <SFML\System\Clock.hpp>

class Animator
{
public:
	Animator();
	Animator(std::string newAnimationID, unsigned int newNbImage, float newDurationToNextImg);
	~Animator();

	std::string getCurID();
	std::string getZeroID();

	void nextImg();
	void reset(sf::Time BaseTime);

	sf::Time getDurationToNextImg();
	bool CheckTimeAndNext(sf::Time toCheck);
private:
	std::string AnimationId;
	unsigned int NbImage;
	sf::Time DurationToNextImg;

	sf::Time curBaseTime;
	unsigned int CurrentImg;
	float timeMultip;
};

