#ifndef AGENT_H
#define AGENT_H

#include "Environment.h"

#include <list>

using std::list;

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
	bool play(unsigned int& guesses);
private:
	Environment* env;
	list<const State*> possibleSolutions;
};

#endif
