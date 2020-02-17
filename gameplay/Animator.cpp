#include "Animator.h"

using namespace std;

Animator::Animator()
{
	AnimationId = "";
	NbImage = 0;
	DurationToNextImg = sf::seconds(0.00);

	curBaseTime = sf::seconds(0.00);
	timeMultip = 0.0;
	CurrentImg = 0;
}

Animator::Animator(std::string newAnimationID, unsigned int newNbImage, float newDurationToNextImg)
{
	AnimationId = newAnimationID;
	NbImage = newNbImage;
	DurationToNextImg = sf::seconds(newDurationToNextImg);

	curBaseTime = sf::seconds(0.00);
	timeMultip = 0.0;
	CurrentImg = 0;
}


Animator::~Animator()
{
}

std::string Animator::getCurID() {
	return (AnimationId + "-" + to_string(CurrentImg));
}

std::string Animator::getZeroID()
{
	return (AnimationId + "-0");
}

void Animator::nextImg()
{
	timeMultip = timeMultip + 1.0;
	CurrentImg++;
	if (CurrentImg >= NbImage) { CurrentImg = 0; return; }
}

void Animator::reset(sf::Time BaseTime)
{
	curBaseTime = BaseTime;
	timeMultip = 0.0;
	CurrentImg = 0;
}

sf::Time Animator::getDurationToNextImg()
{
	return (DurationToNextImg * timeMultip);
}

bool Animator::CheckTimeAndNext(sf::Time toCheck)
{
	sf::Time inTheIfCheck = (toCheck - curBaseTime);
	if (inTheIfCheck < getDurationToNextImg()) { return false; }
	nextImg();
	return true;
}
