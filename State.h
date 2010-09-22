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
	 */
	State();

	/**
	 * Create a state by copying another state
	 * @param	s	the other state to copy
	 */
	State(const State& s);

	/**
	 * Destroy a State object
	 */
	~State();

	/**
	 * Create a state with a specific combination of code pegs
	 * @param	s	the combination to set
	 */
	State(StateData* s, unsigned int p_numPegs);

	/**
	 * Set the current state to another state
	 * @param s	the new state
	 */
	void operator = (const State& s);

	/**
	 * Outputs the current combination to an output buffer
	 * @param out   the output buffer to write to
	 * @param s     the state object to write
	 **/
	friend ostream& operator << (ostream& out, const State& s);

	friend class Environment;

private:
	StateData* data;
	unsigned char numPegs;
};

#endif
