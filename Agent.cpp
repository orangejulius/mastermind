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
		if (guesses == 1) {
			//the optimal first guess is 0101 for a 4 peg game. Extrapolate this alternating pattern
			StateData* guess1 = new StateData[env->getNumPegs()];
			for (unsigned int i = 0; i < env->getNumPegs(); i++) {
				guess1[i] = i % 2;
			}
			guess = State(env,guess1);
		} else {
			//for now, just pick the first remaining possible solution after the 1st guess
			guess = possibleSolutions.front();
		}

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
		list<State>::iterator i = possibleSolutions.begin();
		while (i != possibleSolutions.end()) {
			i->score(guess, black2, white2);
			//remove the current combination from the list of possible solutions or move to the next combination
			if (black2 != black || white2 != white) {
				i = possibleSolutions.erase(i);
			} else {
				i++;
			}
		}
	}
}
