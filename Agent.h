#ifndef AGENT_H
#define AGENT_H

#include "Environment.h"

#include <vector>

using namespace std;

void stats();

class Agent
{
public:
	Agent(Environment* e);
	bool play(unsigned& guesses);
private:
	Environment* env;
	vector<State> possibleSolutions;
};

#endif
