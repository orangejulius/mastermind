#include "State.h"

#include "Environment.h"

#include <cstdio>

using std::min;

State::State(const Environment* e)
{
	data = 0;
	env = e;

	if (env) {
		unsigned int numColors = env->getNumColors();
		colorFrequency = new unsigned char[numColors];
	}
}

State::State(const Environment* e, StateData* s)
{
	env = e;
	data = s;

	if (env) {
		unsigned int numColors = env->getNumColors();
		colorFrequency = new unsigned char[numColors];
	}
}

ostream& operator << (ostream& out, const State& s)
{
	for (unsigned i = 0; i < s.env->getNumPegs(); i++) {
		out<<(int)s.data[i];
	}

	return out;
}

void State::operator = (const State& s)
{
	env = s.env;
	data = s.data;
}
