#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <string>

using namespace std;

int min(int a, int b);



char randomColor();

class Environment
{
    public:
        Environment(unsigned max=10);
        void setSecret(string newSecret);
        bool guess(string guess, int& black, int& white);
        void score (string guess, string secret, int& black, int& white);
        string colors;
    private:
        int guesses;
        int maxguesses;
        string secret;
};

#endif
