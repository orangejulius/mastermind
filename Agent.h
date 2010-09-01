#ifndef AGENT_H
#define AGENT_H

#include "Environment.h"

#include <vector>

using std::vector;

/**
 * Display statistics from the playing of each of the 1296 games of Mastermind
 */
void stats();

/**
 * Class Agent represents the AI entitity that is playing Mastermind
 */
class Agent
{
public:
	/**
	 * Construct an agent to play Mastermind
	 * @param e the environment in which the agent will play
	 */
	Agent(Environment* e);

	/**
	 * Have the agent play a game of mastermind
	 * @param guesses	reference that after execution will contain the number of guesses made
	 * @return bool		true if the agent won the game
	 */
	bool play(unsigned& guesses);
private:
	Environment* env;
	vector<State> possibleSolutions;
};

#endif
