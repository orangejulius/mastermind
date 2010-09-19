#include "Environment.h"

Environment::Environment(unsigned max)
{
	secret = State("abcd");

	guessesMade = 0;
	maxGuesses = max;
}

void Environment::setSecret(State newSecret)
{
	secret = newSecret;
}

bool Environment::guess(State guess, int& black, int& white)
{
	if (guessesMade < maxGuesses) {
		guessesMade++;
		secret.score(guess, black, white);
		return true;
	} else {
		return false;
	}
}
