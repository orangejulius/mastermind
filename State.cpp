#include "State.h"

#include "Environment.h"

using std::min;

State::State(const Environment* e)
{
	env = e;
}

State::State(const Environment* e, const StateData s)
{
	env = e;
	data = s;
}

ostream& operator << (ostream& out, const State& s)
{
	for (unsigned i = 0; i < s.data.size(); i++) {
		out<<(int)s.data[i];
	}

	return out;
}

bool State::operator == (const State& s) const
{
	if (env == s.env) {
		return data == s.data;
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
	for (unsigned int i = 0; i < numPegs; i++) {
		if (data[i] == s.data[i]) {
			black++;
		}
	}

	for (unsigned int i = 0; i < numColors; i++) {
		int c = 0;
		int g = 0;
		for (unsigned int j = 0; j < numPegs; j++) {
			if (i == data[j]) {
				c++;
			}
			if (i == s.data[j]) {
				g++;
			}
		}
		white += min(c, g);
	}
	white = white - black;

	return true;
}
