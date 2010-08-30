//
// C++ Implementation: Environment
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Environment.h"

inline int min(int a, int b)
{
	if (a<b) return a;
	else return b;
}

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
