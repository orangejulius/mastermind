#include "State.h"

using std::min;

State::State(unsigned int pegs, unsigned int colors)
{
	data = StateData(pegs);
	numColors = colors;
}

State::State(const StateData s, unsigned int colors)
{
	data = s;
	numColors = colors;
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
	if (numColors == s.numColors) {
		return data == s.data;
	} else {
		return false;
	}
}

void State::operator = (const State& s)
{
	data = s.data;
	numColors = s.numColors;
	return true;
}

void State::score(const State& s, unsigned int& black, unsigned int& white)
{
	black = 0;
	white = 0;
	for (int i = 0; i < 4; i++) {
		if (data[i] == s.data[i]) {
			black++;
		}
	}

	for (int i = 0; i < 6; i++) {
		int c = 0;
		int g = 0;
		for (int j = 0; j < 4; j++) {
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
}
