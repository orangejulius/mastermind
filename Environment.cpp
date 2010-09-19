#include "Environment.h"

#include <cmath>

Environment::Environment(unsigned int p_numPegs, unsigned int p_numColors, unsigned int p_maxGuesses): secret(State(this))
{
	numPegs = p_numPegs;
	numColors = p_numColors;
	maxGuesses = p_maxGuesses;

	guessesMade = 0;
}

void Environment::setSecret(State newSecret)
{
	secret = newSecret;
}

void Environment::newGame()
{
	secret = State(this);
	guessesMade = 0;
}

unsigned Environment::getNumPegs() const
{
	return numPegs;
}

unsigned Environment::getNumColors() const
{
	return numColors;
}

unsigned int Environment::getNumGames() const
{
	return pow(numColors, numPegs);
}

/*
Calculate each peg color from an integer by dividing the integer by
progressively larger multipeles of the number of colors. This number
mod the number of colors is the peg color.
*/
State Environment::getGameByNumber(unsigned int gameNum) const
{
	StateData secret(numPegs);
	for (unsigned int i = 0; i < numPegs; i++) {
		unsigned int divisor = pow(numColors,numPegs-1-i);
		secret[i] = (gameNum / divisor) % numColors;
	}
	return State(this, secret);
}

bool Environment::guess(State guess, unsigned int& black, unsigned int& white)
{
	if (guessesMade < maxGuesses) {
		guessesMade++;
		secret.score(guess, black, white);
		return true;
	} else {
		return false;
	}
}
