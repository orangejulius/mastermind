#ifndef STATE_H
#define STATE_H

#include <iostream>

using std::ostream;

typedef unsigned char StateData;

class Environment;

/**
 * Class State stores one combination of code pegs for Mastermind. It could be the codemaker's
 * secret combination, a guess made by the codebreaker, or just a temporary representation
 * used by the codebreaker AI
 */
class State
{
public:
	/**
	 * Create a state without specifying the combination
	 * @param	e	a pointer to the environment in which this state is valid
	 */
	State(const Environment* e);

	/**
	 * Create a state with a specific combination of code pegs
	 * @param	e	a pointer to the environment in which this state is valid
	 * @param	s	the combination to set
	 */
	State(const Environment* e, StateData* s);

	/**
	 * Outputs the current combination to an output buffer
	 * @param out	the output buffer to write to
	 * @param s	the state object to write
	 **/
	friend ostream& operator << (ostream& out, const State& s);

	/**
	 * Set the current state to another state
	 * @param s	the new state
	 */
	void operator = (const State& s);

	friend class Environment;

private:
	StateData* data;
	const Environment* env;
	unsigned char* colorFrequency;
};

#endif
