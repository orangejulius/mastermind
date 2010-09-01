#include "Agent.h"

#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

using std::cout;
using std::endl;

#define NUM_THREADS 4

// Struct for passing information to threads
struct ThreadData
{
	unsigned threadId; //the id of this thread starting at 0
};

//global storage space for the number of moves each game takes to win
vector<unsigned> scores;

//global storage for information to pass to threads
ThreadData threadData[NUM_THREADS];

//any thread wanting to write to a global variable must wait on this semaphore
sem_t writeSem;

//the thread parent will wait on this semaphore until all threads are done computing
sem_t computing;

void* playGame(void* p_threadData)
{
	//convert the void pointer to useful data
	struct ThreadData* threadData;
	threadData = (struct ThreadData* ) p_threadData;

	//play through all the games assigned to this thread
	for (int i=threadData->threadId;i<6*6*6*6;i+=NUM_THREADS) {
		//initialize the state for this game
		unsigned guesses=0;
		Environment e=Environment(50);
		Agent a=Agent(&e);
		char secret[4];
		secret[0]=(i/(6*6*6))%6;
		secret[1]=(i/(6*6))%6;
		secret[2]=(i/(6))%6;
		secret[3]=i%6;
		State s(secret);
		e.setSecret(s);

		//play this game
		a.play(guesses);

		///update the list of scores for all games
		sem_wait(&writeSem);
		while (scores.size()<guesses) {
			scores.push_back(0);
		}
		scores[guesses-1]++;
		sem_post(&writeSem);
	}
	sem_post(&computing);

	return 0;
}

void stats()
{
	pthread_t threads[NUM_THREADS];

	//this semaphore should be at 1 when all threads have finished running
	sem_init(&computing,0,1-NUM_THREADS);

	//limit number of threads accessing global variables to 1
	sem_init(&writeSem,0,1);

	for (unsigned i=0; i<NUM_THREADS; i++) {
		threadData[i].threadId = i;
		pthread_create(&threads[i],NULL, playGame,(void*) &threadData[i]);
	}

	//wait until all threads are done running
	sem_wait(&computing);

	//output interesting information
	cout<<"moves, games solved in that # of moves"<<endl;
	unsigned totalMoves = 0;
	unsigned totalGames = 0;
	for (unsigned i = 0; i < scores.size(); i++) {
		cout<<i+1<<": "<<scores[i]<<endl;
		totalGames += scores[i];
		totalMoves += (i+1) * scores[i];
	}
	cout<<"total games: "<<totalGames<<endl;
	cout<<"average: "<<totalMoves/(float)totalGames<<endl;
}

Agent::Agent(Environment* e)
{
	env = e;

	//initially all games are possible
	for (int i = 0; i < 6*6*6*6;i ++) {
		char secret[4];
		secret[0] = (i/(6*6*6))%6;
		secret[1] = (i/(6*6))%6;
		secret[2] = (i/(6))%6;
		secret[3] = i%6;
		State s(secret);
		possibleSolutions.push_back(s);
	}
}

bool Agent::play(unsigned& guesses)
{
	guesses = 0;
	int black, white;
	State guess;
	while (1) {
		guesses++;
		//make a guess
		//first guess a specific state, and then after that a random possible solution
		if (guesses == 1) {
			char g[] = {0,0,1,1};
			guess = g;
		} else {
			int r = rand() % possibleSolutions.size();
			guess = possibleSolutions[r];
		}

		//ask the environment to score the guess
		if (env->guess(guess, black, white)) {
			//4 black pins means victory
			if (black==4) {
				return true;
			} else {
				int black2, white2;
				//iterate through all possible solutions
				//since Mastermind guess scores are symmetric, only combinations that score the same
				//against the current guess as the current guess does against the solution are
				//possible solutions
				for (vector<State>::iterator i=possibleSolutions.begin();i!=possibleSolutions.end();) {
					i->score(guess,black2,white2);
					//remove the current combination from the list of possible solutions or move to the next combination
					if ((black2!=black)||(white2!=white)) {
						possibleSolutions.erase(i);
					} else {
						i++;
					}
				}
			}
		} else {
			return false;
		}
	}
}
