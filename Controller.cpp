#include "Controller.h"

#include <cstdlib>

#include "Agent.h"

using boost::thread;
using std::cout;
using std::endl;

struct ThreadData
{
	unsigned int threadId; //the id of this thread
};

//storage space for the number of moves each game takes to win
vector<unsigned int> Controller::scores;

unsigned int Controller::numThreads;

//storage for information to pass to threads
ThreadData* Controller::threadDataArray;

//any thread wanting to write to the scores must wait on this mutex
mutex Controller::scoresMutex;

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

	for (unsigned int i = 0; i < numThreads; i++) {
		threadDataArray[i].threadId = i;
		threads[i] = thread(boost::ref(Controller::playGamesThread), threadDataArray[i]);
	}

	//wait until all threads are done running
	for (unsigned int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	//output interesting information
	cout<<"moves, games solved in that # of moves"<<endl;
	unsigned int totalMoves = 0;
	unsigned int totalGames = 0;
	for (unsigned int i = 0; i < scores.size(); i++) {
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
		unsigned int guesses = 0;
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
		scoresMutex.lock();
		while (scores.size() < guesses) {
			scores.push_back(0);
		}
		scores[guesses-1]++;
		scoresMutex.unlock();
	}
	return 0;
}
