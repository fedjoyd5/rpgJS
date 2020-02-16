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

	void nextImg();
	void reset();

	sf::Time getDurationToNextImg();
	bool CheckTime(sf::Time toCheck);
	bool CheckTimeAndNext(sf::Time toCheck);
private:
	std::string AnimationId;
	unsigned int NbImage;
	sf::Time DurationToNextImg;

	unsigned int CurrentImg;
	float timeMultip;
};

