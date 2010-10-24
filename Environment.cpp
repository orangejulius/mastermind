#include "Environment.h"

#include <cmath>

Environment::Environment(unsigned int p_numPegs, unsigned int p_numColors, unsigned int p_maxGuesses)
: maxGuesses(p_maxGuesses), numPegs(p_numPegs), numColors(p_numColors)
{
	numGames = pow(numColors, numPegs);

	guessesMade = 0;

	colorFrequency = new unsigned char[numColors];
}

/*
Calculate each peg color from an integer by dividing the integer by
progressively larger multipeles of the number of colors. This number
mod the number of colors is the peg color.
*/
State Environment::getGameByNumber(unsigned int gameNum) const
{
	StateData* secret = new StateData[numPegs];
	for (unsigned int i = 0; i < numPegs; i++) {
		unsigned int divisor = 1;
		for (unsigned j = 0; j < numPegs-1-i; j++) {
			divisor *= numColors;
		}
		secret[i] = (gameNum / divisor) % numColors;
	}
	return State(secret, numPegs);
}

void Environment::score(const State& a, const State& b, unsigned int& black, unsigned int& white)
{
	black = 0;
	white = 0;

	for (unsigned int i = 0; i < numColors; i++) {
		colorFrequency[i] = 0;
	}

	for (unsigned int i = 0; i < numPegs; i++) {
		if (a.data[i] == b.data[i]) {
			black++;
		}
		colorFrequency[a.data[i]]++;
	}

	for (unsigned int i = 0; i < numPegs; i++) {
		if (colorFrequency[b.data[i]] > 0){
			colorFrequency[b.data[i]]--;
			white++;
		}
	}

	white -= black;
}

bool Environment::guess(State guess, unsigned int& black, unsigned int& white)
{
	if (guessesMade < maxGuesses) {
		guessesMade++;
		score(secret, guess, black, white);
		return true;
	} else {
		return false;
	}
}
