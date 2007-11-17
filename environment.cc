#include "environment.h"

int min(int a, int b)
{
    if (a<b) return a;
    else return b;
}

void Environment::score(string guess, string secret, int& black, int& white)
{
    black=0;
    white=0;
    for (int i=0;i<4;i++)
    {
        if (secret[i]==guess[i])
        {
            black++;
        }
    }

    for (int i=0;i<6;i++)
    {
        int c=0;
        int g=0;
        for (int j=0;j<4;j++)
        {
            if (colors[i]==secret[j])
            {
                c++;
            }
            if (colors[i]==guess[j])
            {
                g++;
            }
        }
        white=white+min(c,g);
    }
    white=white-black;
}

char randomColor()
{
    //TODO
}

Environment::Environment(unsigned max)
{
    colors="abcdef";
    secret="abcd";
    guesses=0;
    maxguesses=max;
}

void Environment::setSecret(string newSecret)
{
    secret=newSecret;
}

bool Environment::guess(string guess, int& black, int& white)
{
    if (guesses<maxguesses)
    {
        guesses++;
        score(guess,secret,black,white);
        return true;
    }
    else
    {
        return false;
    }
}

