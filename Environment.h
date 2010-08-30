#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>

#include "State.h"

using namespace std;

int min(int a, int b);

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
