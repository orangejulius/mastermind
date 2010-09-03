#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <boost/thread.hpp>

#include <vector>

#include "Environment.h"

using boost::mutex;
using std::vector;

//Struct for passing information to threads
struct ThreadData;

/**
 * Class Controller handles the user interface
 */
class Controller
{
public:
	/**
	 * The basic user interface loop that handles user input
	 */
	static bool run();

private:
	/**
	 * Play every game of Mastermind and output statistics about how many guesses each game took to solve
	 */
	static void playAllGames();

	/**
	 * Function that is run in a thread to play all games of Mastermind
	 */
	static void* playGamesThread(ThreadData& threadData);

	//storage space for the number of moves each game takes to win
	static vector<unsigned> scores;

	static unsigned numThreads;

	//storage for information to pass to threads
	static ThreadData* threadDataArray;

	//any thread wanting to write to a global variable must wait on this semaphore
	static mutex scoresMutex;
};

#endif
