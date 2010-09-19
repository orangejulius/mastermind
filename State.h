#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>

using std::ostream;
using std::vector;

typedef vector<unsigned char> StateData;

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
	 * @param	pegs	the number of pegs in this state
	 * @param	colors	the number of possible colors
	 */
	State(unsigned int pegs = 4, unsigned int colors = 6);

	/**
	 * Create a state with a specific combination of code pegs
	 * @param	g	the combination to set
	 * @param	colors	the number of colors allowed
	 */
	State(const StateData s, unsigned int colors = 6);

	/**
	 * Outputs the current combination to an output buffer
	 * @param out	the output buffer to write to
	 * @param s	the state object to write
	 **/
	friend ostream& operator << (ostream& out, const State& s);

	/**
	 * Compare this state to another
	 * @param s	the state to compare
	 * @return	true if the two states are equal
	 */
	bool operator == (const State& s) const;

	/**
	 * Set the current state to another state
	 * @param s	the new state
	 */
	void operator = (const State& s);

	/**
	 * Compare two states and return the Mastermind score. Note that Mastermind scores are
	 * symmetric meaning that the score of A against B and the score of B against A are
	 * always the same.
	 * @param s	the state to score this state against
	 * @param black	a reference to the number of black key pegs in the score
	 * @param white	a reference to the number of white key pegs in the score
	 */
	void score(const State& s, unsigned int& black, unsigned int& white);
private:
	StateData data;
	unsigned numColors;
};

#endif
