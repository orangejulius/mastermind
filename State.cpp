#include "State.h"

#include "Environment.h"

#include <cstdio>

State::State()
{
	numPegs = 0;
	data = 0;
}

State::State(StateData* s, unsigned int p_numPegs)
{
	numPegs = p_numPegs;
	data = s;
}

void State::operator = (const State& s)
{
	numPegs = s.numPegs;
	data = s.data;
}

ostream& operator << (ostream& out, const State& s)
{
	for (unsigned i = 0; i < s.numPegs; i++) {
		out<<(int)s.data[i];
	}
	return out;
}
