#include "Controller.h"

#include <cstdlib>

#include <boost/thread.hpp>

#include "Agent.h"

using boost::thread;
using std::cout;
using std::endl;

struct ThreadData
{
	unsigned threadId; //the id of this thread
};

//storage space for the number of moves each game takes to win
vector<unsigned> Controller::scores;

unsigned Controller::numThreads;

//storage for information to pass to threads
ThreadData* Controller::threadDataArray;

//any thread wanting to write to a global variable must wait on this semaphore
sem_t Controller::writeSem;

bool Controller::run()
{
	//let boost determine how many threads we can run
	numThreads = thread::hardware_concurrency();
	threadDataArray = new ThreadData[numThreads];

	playAllGames();
	return true;
}

void Controller::playAllGames()
{
	thread threads[numThreads];

	//limit number of threads accessing shared variables to 1
	sem_init(&writeSem, 0, 1);

	for (unsigned i = 0; i < numThreads; i++) {
		threadDataArray[i].threadId = i;
		threads[i] = thread(boost::ref(Controller::playGamesThread), threadDataArray[i]);
	}

	//wait until all threads are done running
	for (unsigned i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	//output interesting information
	cout<<"moves, games solved in that # of moves"<<endl;
	unsigned totalMoves = 0;
	unsigned totalGames = 0;
	for (unsigned i = 0; i < scores.size(); i++) {
		cout<<i+1<<": "<<scores[i]<<endl;
		totalMoves += (i+1) * scores[i];
		totalGames += scores[i];
	}
	cout<<"average: "<<totalMoves / (float)totalGames<<endl;
	cout<<"total games: "<<totalGames<<endl;
}

void* Controller::playGamesThread(ThreadData& threadData)
{
	//play through all the games assigned to this thread
	for (int i = threadData.threadId; i < 6*6*6*6; i += numThreads) {
		//initialize the state for this game
		unsigned guesses = 0;
		Environment e = Environment(50);
		Agent a = Agent(&e);
		char secret[4];
		secret[0] = (i/(6*6*6))%6;
		secret[1] = (i/(6*6))%6;
		secret[2] = (i/(6))%6;
		secret[3] = i%6;
		State s(secret);
		e.setSecret(s);

		//play this game
		a.play(guesses);

		///update the list of scores for all games
		sem_wait(&writeSem);
		while (scores.size() < guesses) {
			scores.push_back(0);
		}
		scores[guesses-1]++;
		sem_post(&writeSem);
	}
	return 0;
}
