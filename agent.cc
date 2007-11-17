#include "agent.h"

#include <cstdlib>

void stats()
{
    vector<string> possibleSolutions;
    vector<unsigned> scores;
    unsigned total=0;
    for (int i=0;i<6*6*6*6;i++)
    {
        unsigned guesses=0;
        if (i%10==0)
        {
            cout<<i<<endl;
        }//*/
        Environment e=Environment(50);
        Agent a=Agent(&e);
        string secret;
        secret[0]=e.colors[(i/(6*6*6))%6];
        secret[1]=e.colors[(i/(6*6))%6];
        secret[2]=e.colors[(i/(6))%6];
        secret[3]=e.colors[i%6];
        //cout<<secret<<endl;
        e.setSecret(secret);
        a.play(guesses);
        while (scores.size()<=guesses)
        {
            scores.push_back(0);
        }
        total+=guesses;
        scores[guesses]++;
    }

    cout<<"moves, games solved in that # of moves"<<endl;
    for (unsigned i=0;i<scores.size();i++)
    {
        cout<<i<<": "<<scores[i]<<endl;
    }
    cout<<"average: "<<total/1296.<<endl;
}

Agent::Agent(Environment* e)
{
    env=e;
    //cout<<e->colors<<endl;
    for (int i=0;i<6*6*6*6;i++)
    {
        string secret="abcd";
        secret[0]=e->colors[(i/(6*6*6))%6];
        secret[1]=e->colors[(i/(6*6))%6];
        secret[2]=e->colors[(i/(6))%6];
        secret[3]=e->colors[i%6];
        possibleSolutions.push_back(secret);
    }
}

bool Agent::play(unsigned& guesses)
{
    guesses=0;
    int black, white;
    string t;
    string guess;
    while (1)
    {
        guesses++;
        //cout<<endl;
        //cout<<"number of possible guesses: "<<possibleSolutions.size()<<endl;
        if (guesses==1)
        {
            guess="aabb";
        }
        else
        {
            int r=rand()%(possibleSolutions.size());
            guess=possibleSolutions[r];
        }
        //cout<<"guessing "<<guess<<endl;

        if (env->guess(guess,black,white))
        {
            //cout<<"score is ("<<black<<", "<<white<<")\n";
            if (black==4)
            {
                //cout<<"won in "<<guesses<<" guesses\n";
                return true;
            }
            else
            {
                for (vector<string>::iterator i=possibleSolutions.begin();i!=possibleSolutions.end();)
                {
                    int black2, white2;
                    t=(*i);
                    env->score(t,guess,black2,white2);
                    if ((black2!=black)||(white2!=white))
                    {
                        //cout<<"score("<<t<<", "<<guess<<") "<<black<<", "<<white<<"!="<<black2<<", "<<white2<<endl;
                        //cout<<"removing "<<t<<" with score ("<<black2<<", "<<white2<<")\n";
                        possibleSolutions.erase(i);
                    }
                    else
                    {
                        //cout<<"keeping "<<t<<" with score ("<<black<<", "<<white<<")\n";
                        i++;
                    }
                }
            }
        }
        else
        {
            //cout<<"lost in "<<guesses<<" guesses\n";
            return false;
        }
    }
}
