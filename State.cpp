#include "State.h"

#include <cmath>

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

unsigned int State::getNumPegs() const
{
	return data.size();
}

unsigned int State::getNumColors() const
{
	return numColors;
}

/*
The number of possible games is the c^p, where c is the number of possible colors
and p is the number of pegs
*/
unsigned int State::getNumGames() const
{
	return pow(numColors, data.size());
}

/*
Calculate each peg color from an integer by dividing the integer by
progressively larger multipeles of the number of colors. This number
mod the number of colors is the peg color.
*/
State State::getGameByNumber(unsigned int gameNum) const
{
	unsigned numPegs = getNumPegs();
	StateData secret(numPegs);
	for (unsigned i = 0; i < numPegs; i++) {
		unsigned divisor = pow(numColors,numPegs-1-i);
		secret[i] = (gameNum / divisor) % numColors;
	}
	return State(secret);
}

bool State::score(const State& s, unsigned int& black, unsigned int& white)
{
	if (numColors != s.numColors) {
		return false;
	}

	if (data.size() != s.data.size()) {
		return false;
	}

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

	return true;
}
