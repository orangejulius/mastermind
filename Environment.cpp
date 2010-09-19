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
