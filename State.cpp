#include "State.h"

#include <cstring>

using std::min;

State::State()
{
	strncpy(array, "abcd", 4);
}

State::State(const char* s)
{
	strncpy(array,s,4);
}

ostream& operator << (ostream& out, const State& s)
{
	out<<(int)s.array[0]<<(int)s.array[1]<<(int)s.array[2]<<(int)s.array[3];

	return out;
}

bool State::operator == (const State& s) const
{
	return strncmp(s.array, array, 4) == 0;
}

bool State::operator = (const State& s)
{
	strncpy(array, s.array,4);
	return true;
}

void State::score(const State& s, int& black, int& white)
{
	black = 0;
	white = 0;
	for (int i = 0; i < 4; i++) {
		if (array[i] == s.array[i]) {
			black++;
		}
	}

	for (int i = 0; i < 6; i++) {
		int c = 0;
		int g = 0;
		for (int j = 0; j < 4; j++) {
			if (i == array[j]) {
				c++;
			}
			if (i == s.array[j]) {
				g++;
			}
		}
		white = white + min(c,g);
	}
	white = white - black;
}
