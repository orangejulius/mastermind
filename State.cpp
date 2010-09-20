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

bool State::operator == (const State& s) const
{
	if (env == s.env) {
		for (unsigned int i = 0; i < env->getNumGames(); i++) {
			if (data[i] != s.data[i]) {
				return false;
			}
		}
		return true;
	} else {
		return false;
	}
}

void State::operator = (const State& s)
{
	env = s.env;
	data = s.data;
}

bool State::score(const State& s, unsigned int& black, unsigned int& white)
{
	if (env != s.env) {
		return false;
	}

	black = 0;
	white = 0;

	unsigned int numPegs = env->getNumPegs();
	unsigned int numColors = env->getNumColors();

	for (unsigned int i = 0; i < numColors; i++) {
		colorFrequency[i] = 0;
	}

	for (unsigned int i = 0; i < numPegs; i++) {
		if (data[i] == s.data[i]) {
			black++;
		}
		colorFrequency[data[i]]++;
	}

	for (unsigned int i = 0; i < numPegs; i++) {
		if ( colorFrequency[s.data[i]] > 0 ){
			colorFrequency[s.data[i]]--;
			white++;
		}
	}

	white -= black;

	return true;
}
