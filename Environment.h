#ifndef MASTERMINDENVIRONMENT_H
#define MASTERMINDENVIRONMENT_H

#include "State.h"

/**
 * Class Environment represents the state of the world in which a game of Mastermind is played.
 * It stores the secret combination made by the codemaker and the number of guesses the codebreaker
 * has made.
 */
class Environment
{
public:
	/**
	 * Initialize the environment
	 * @param max	the maximum number of guesses the codebreaker can make before losing
	 */
	Environment(unsigned max=10);

	/**
	 * Set the secret combination that the codebreaker is trying to guess
	 * @param newSecret	the new secret combination
	 */
	void setSecret(State newSecret);

	/**
	 * Record a guess made by the codebreaker and return the score of the guess against the
	 * secret code
	 * @param g	the guess made the codebreaker
	 * @param black	a reference to the number of black key pegs in the score
	 * @param white	a reference to the number of white key pegs in the score
	 * @return bool	true if the codebreaker has not reached the maximum number of guesses
	 */
	bool guess(State g, int& black, int& white);
private:
	int guesses;
	int maxguesses;
	State secret;
};

#endif
