#include "Agent.h"

#include <cstdlib>

Agent::Agent(Environment* e)
{
	env = e;

	//initially all games are possible
	for (unsigned int i = 0; i < env->getNumGames(); i++) {
		State s = env->getGameByNumber(i);
		possibleSolutions.push_back(s);
	}
}

bool Agent::play(unsigned int& guesses)
{
	guesses = 0;
	unsigned int black, white;
	State guess(env);

	while (1) {
		guesses++;
		//make a guess
		//simply take the first guess that is still consistent with the known information
		guess = possibleSolutions[0];

		//ask the environment to score the guess
		//false return value means no more guesses are allowed
		if (env->guess(guess, black, white) == false) {
			return false;
		}
		//4 black pins means victory
		if (black == env->getNumPegs()) {
			return true;
		}
		unsigned int black2, white2;
		//iterate through all possible solutions
		//since Mastermind guess scores are symmetric, only combinations that score the same
		//against the current guess as the current guess does against the solution are
		//possible solutions
		vector<State>::iterator i = possibleSolutions.begin();
		while (i != possibleSolutions.end()) {
			i->score(guess, black2, white2);
			//remove the current combination from the list of possible solutions or move to the next combination
			if (black2 != black || white2 != white) {
				possibleSolutions.erase(i);
			} else {
				i++;
			}
		}
	}
}
