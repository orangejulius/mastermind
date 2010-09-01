#include "Environment.h"

Environment::Environment(unsigned max)
{
	secret="abcd";
	guesses=0;
	maxguesses=max;
}

void Environment::setSecret(State newSecret)
{
	secret=newSecret;
}

bool Environment::guess(State guess, int& black, int& white)
{
	if (guesses<maxguesses) {
		guesses++;
		secret.score(guess,black,white);
		return true;
	} else {
		return false;
	}
}
