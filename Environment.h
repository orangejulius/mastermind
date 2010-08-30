//
// C++ Interface: Environment
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MASTERMINDENVIRONMENT_H
#define MASTERMINDENVIRONMENT_H

#include "State.h"

using namespace std;

int min(int a, int b);

/**
	@author 
*/
class Environment
{
public:
	Environment(unsigned max=10);
	void setSecret(State newSecret);
	bool guess(State g, int& black, int& white);
private:
	int guesses;
	int maxguesses;
	State secret;
};

#endif
