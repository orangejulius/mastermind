#include "State.h"

#include <cstring>

using std::min;

State::State()
{
	strncpy(data, "abcd", 4);
}

State::State(const char* s)
{
	strncpy(data,s,4);
}

ostream& operator << (ostream& out, const State& s)
{
	out<<(int)s.data[0]<<(int)s.data[1]<<(int)s.data[2]<<(int)s.data[3];

	return out;
}

bool State::operator == (const State& s) const
{
	return strncmp(s.data, data, 4) == 0;
}

bool State::operator = (const State& s)
{
	strncpy(data, s.data,4);
	return true;
}

void State::score(const State& s, int& black, int& white)
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
