//
// C++ Interface: State
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STATE_H
#define STATE_H

#include <iostream>

using namespace std;

/**
	@author 
*/
class State
{
	public:
		State();
		State(char g[4]);

		friend ostream& operator<<(ostream& out, const State& s);
		bool operator==(const State& s);
		bool operator=(const State& s);

		void score(const State& s, int& black, int& white);
	private:
		char array[4];
};

#endif
