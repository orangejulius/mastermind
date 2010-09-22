#include "Environment.h"

#include <cmath>

Environment::Environment(unsigned int p_numPegs, unsigned int p_numColors, unsigned int p_maxGuesses)
: maxGuesses(p_maxGuesses), numPegs(p_numPegs), numColors(p_numColors)
{
	numGames = pow(numColors, numPegs);

	guessesMade = 0;

	colorFrequency = new unsigned char[numColors];

	allStates = new State[numGames];
	/*
	Calculate each peg color from an integer by dividing the integer by
	progressively larger multipeles of the number of colors. This number
	mod the number of colors is the peg color.
	*/
	for (unsigned int i = 0; i < numGames; i++) {
		StateData* secret = new StateData[numPegs];

		for (unsigned int j = 0; j < numPegs; j++) {
			unsigned int divisor = 1;
			for (unsigned k = 0; k < numPegs-1-j; k++) {
				divisor *= numColors;
			}
			secret[j] = (i / divisor) % numColors;
		}
		allStates[i] = State(secret, numPegs);
	}
}

Environment::~Environment() {
	delete[] colorFrequency;
	delete[] allStates;
}

const State* Environment::getGameByNumber(unsigned int gameNum) const
{
	return &allStates[gameNum];
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

bool Environment::guess(State& guess, unsigned int& black, unsigned int& white)
{
	if (guessesMade < maxGuesses) {
		guessesMade++;
		score(*secret, guess, black, white);
		return true;
	} else {
		return false;
	}
}
