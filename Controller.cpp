#include "Controller.h"

#include <cstdlib>

#include "Agent.h"

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

//the thread parent will wait on this semaphore until all threads are done computing
sem_t Controller::computing;

bool Controller::run()
{
	numThreads = 4;
	threadDataArray = new ThreadData[numThreads];

	playAllGames();
	return true;
}

void Controller::playAllGames()
{
	pthread_t threads[numThreads];

	//this semaphore should be at 1 when all threads have finished running
	sem_init(&computing, 0, 1 - numThreads);

	//limit number of threads accessing shared variables to 1
	sem_init(&writeSem, 0, 1);

	for (unsigned i = 0; i < numThreads; i++) {
		threadDataArray[i].threadId = i;
		pthread_create(&threads[i], NULL, &Controller::playGamesThread, (void*) &threadDataArray[i]);
	}

	//wait until all threads are done running
	sem_wait(&computing);

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

void* Controller::playGamesThread(void* p_threadData)
{
	//convert the void pointer to useful data
	struct ThreadData* threadData;
	threadData = (struct ThreadData* ) p_threadData;

	//play through all the games assigned to this thread
	for (int i = threadData->threadId; i < 6*6*6*6; i += numThreads) {
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
	sem_post(&computing);

	return 0;
}