#include "Animator.h"

using namespace std;

Animator::Animator()
{
	AnimationId = "";
	NbImage = 0;
	DurationToNextImg = sf::seconds(0.00);

	timeMultip = 0.0;
	CurrentImg = 0;
}

Animator::Animator(std::string newAnimationID, unsigned int newNbImage, float newDurationToNextImg)
{
	AnimationId = newAnimationID;
	NbImage = newNbImage;
	DurationToNextImg = sf::seconds(newDurationToNextImg);

	timeMultip = 0.0;
	CurrentImg = 0;
}


Animator::~Animator()
{
}

std::string Animator::getCurID() {
	return (AnimationId + "-" + to_string(CurrentImg));
}

void Animator::nextImg()
{
	timeMultip = timeMultip + 1.0;
	CurrentImg++;
	if (CurrentImg >= NbImage) { CurrentImg = 0; return; }
}

void Animator::reset()
{
	timeMultip = 0.0;
	CurrentImg = 0;
}

sf::Time Animator::getDurationToNextImg()
{
	return (DurationToNextImg * timeMultip);
}

bool Animator::CheckTime(sf::Time toCheck)
{
	return (toCheck >= DurationToNextImg);
}

bool Animator::CheckTimeAndNext(sf::Time toCheck)
{
	if (toCheck < getDurationToNextImg()) { return false; }
	nextImg();
	return true;
}
