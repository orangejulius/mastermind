#include "Agent.h"

#include <cstdlib>

Agent::Agent(Environment* e)
{
	env = e;

	//initially all games are possible
	for (int i = 0; i < 6*6*6*6;i ++) {
		char secret[4];
		secret[0] = (i/(6*6*6))%6;
		secret[1] = (i/(6*6))%6;
		secret[2] = (i/(6))%6;
		secret[3] = i%6;
		State s(secret);
		possibleSolutions.push_back(s);
	}
}

bool Agent::play(unsigned& guesses)
{
	guesses = 0;
	int black, white;
	State guess;
	while (1) {
		guesses++;
		//make a guess
		//first guess a specific state, and then after that a random possible solution
		if (guesses == 1) {
			char g[] = {0,0,1,1};
			guess = g;
		} else {
			int r = rand() % possibleSolutions.size();
			guess = possibleSolutions[r];
		}

		//ask the environment to score the guess
		//false return value means no more guesses are allowed
		if (env->guess(guess, black, white) == false) {
			return false;
		}
		//4 black pins means victory
		if (black == 4) {
			return true;
		}
		int black2, white2;
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
