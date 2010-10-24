#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Controller.h"
#include <list>

using std::list;

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Environment e1(4,6,10);
	StateData* sd1 = new StateData[4];
	sd1[0] = 0;
	sd1[1] = 1;
	sd1[2] = 2;
	sd1[3] = 3;
	State s1(sd1, e1.getNumPegs());

	StateData* sd2 = new StateData[4];
	sd2[0] = 0;
	sd2[1] = 1;
	sd2[2] = 2;
	sd2[3] = 3;
	State s2(sd2, e1.getNumPegs());

	StateData* sd3 = new StateData[4];
	sd3[0] = 1;
	sd3[1] = 2;
	sd3[2] = 3;
	sd3[3] = 4;
	State s3(sd3, e1.getNumPegs());


	StateData* sd4 = new StateData[4];
	sd4[0] = 2;
	sd4[1] = 6;
	sd4[2] = 3;
	sd4[3] = 4;
	State s4(sd4, e1.getNumPegs());
	unsigned int black = -1;
	unsigned int white = -1;

	//expect (4,0)
	e1.score(s1,s1, black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect(4,0)
	e1.score(s1, s2, black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect (0,3)
	e1.score(s1, s3, black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect (2,1)
	e1.score(s3, s4, black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	cout<<"s1 num games: "<<e1.getNumGames()<<endl;
	State s1a = e1.getGameByNumber(5);

	State s5=s4;

	State s6;

	s6 = s5;

	list<State> l;
	l.push_back(s6);
	l.push_back(s1);
	std::list<State>::iterator i = l.begin();
	cout<<"i address: "<<&(*i)<<endl;
	l.push_back(s2);
	l.erase(i);

	return 0;
}
