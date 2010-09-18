#include "Environment.h"

Environment::Environment(unsigned int max)
{
	guessesMade = 0;
	maxGuesses = max;
}

void Environment::setSecret(State newSecret)
{
	secret = newSecret;
}

void Environment::newGame()
{
	secret = State();
	guessesMade = 0;
}

unsigned Environment::getNumPegs() const
{
	return secret.getNumPegs();
}

unsigned Environment::getNumColors() const
{
	return secret.getNumColors();
}

unsigned int Environment::getNumGames() const
{
	return secret.getNumGames();
}

State Environment::getGameByNumber(unsigned int gameNum) const
{
	return secret.getGameByNumber(gameNum);
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
