//
// C++ Implementation: Agent
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Agent.h"

#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

//global variables
vector<unsigned> scores;
unsigned total=0;

//semaphores
sem_t writeSem;//any thread wanting to write to a global variable must wait on this semaphore
sem_t computing;
sem_t threadLimit; //limit the max number of threads

void *evenPlayGame(void* gameNum)
{
	for (int i=0;i<6*6*6*6;i+=2) {
		unsigned guesses=0;
		Environment e=Environment(50);
		Agent a=Agent(&e);
		char secret[4];
		secret[0]=(i/(6*6*6))%6;
		secret[1]=(i/(6*6))%6;
		secret[2]=(i/(6))%6;
		secret[3]=i%6;
		State s(secret);
		//cout<<secret<<endl;
		e.setSecret(s);
		a.play(guesses);
		sem_wait(&writeSem);
		while (scores.size()<guesses) {
			scores.push_back(0);
		}
		total+=guesses;
		scores[guesses-1]++;
		sem_post(&writeSem);
	}
	sem_post(&computing);
}

void *oddPlayGame(void* gameNum)
{
	for (int i=1;i<6*6*6*6;i+=2) {
		unsigned guesses=0;
		Environment e=Environment(50);
		Agent a=Agent(&e);
		char secret[4];
		secret[0]=(i/(6*6*6))%6;
		secret[1]=(i/(6*6))%6;
		secret[2]=(i/(6))%6;
		secret[3]=i%6;
		State s(secret);
		//cout<<secret<<endl;
		e.setSecret(s);
		a.play(guesses);
		sem_wait(&writeSem);
		while (scores.size()<guesses) {
			scores.push_back(0);
		}
		total+=guesses;
		scores[guesses-1]++;
		sem_post(&writeSem);
	}
	sem_post(&computing);
}

void stats()
{
	pthread_t threads[2];

	sem_init(&computing,0,-1);
	sem_init(&writeSem,0,1);//limit number of threads accessing global variables to 1
	int ignore = 0;
	pthread_create(&threads[0],NULL, evenPlayGame,(void*)ignore);
	pthread_create(&threads[1],NULL, oddPlayGame,(void*)ignore);

	sem_wait(&computing);
	cout<<"moves, games solved in that # of moves"<<endl;
	for (unsigned i = 0; i < scores.size(); i++) {
		cout<<i + 1<<": "<<scores[i]<<endl;
	}
	cout<<"average: "<<total/1296.<<endl;
}

Agent::Agent(Environment* e)
{
	env = e;
	//cout<<e->colors<<endl;
	for (int i = 0; i < 6*6*6*6; i++) {
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
		//cout<<endl;
		//cout<<"number of possible guesses: "<<possibleSolutions.size()<<endl;
		if (guesses == 1) {
			char g[] = {0,0,1,1};
			guess = g;
		} else {
			int r = rand() % possibleSolutions.size();
			guess = possibleSolutions[r];
		}
		//cout<<"guessing "<<guess<<endl;

		if (env->guess(guess, black, white)) {
			//cout<<"score is ("<<black<<", "<<white<<")\n";
			if (black == 4) {
				//cout<<"won in "<<guesses<<" guesses\n";
				return true;
			} else {
				int black2, white2;
				for (vector<State>::iterator i = possibleSolutions.begin(); i != possibleSolutions.end();) {
					i->score(guess,black2,white2);
					if ((black2!=black)||(white2!=white)) {
						//cout<<"score("<<*i<<", "<<guess<<") "<<black<<", "<<white<<"!="<<black2<<", "<<white2<<endl;
						//cout<<"removing "<<*i<<" with score ("<<black2<<", "<<white2<<")\n";
						possibleSolutions.erase(i);
					} else {
						//cout<<"keeping "<<*i<<" with score ("<<black<<", "<<white<<")\n";
						i++;
					}
				}
			}
		} else {
			//cout<<"lost in "<<guesses<<" guesses\n";
			return false;
		}
	}
}