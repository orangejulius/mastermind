#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Controller.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	unsigned char d1[4] = {0,1,2,3};
	StateData sd1(&d1[0], &d1[4]);
	State s1(sd1);

	unsigned char d2[4] = {0,1,2,3};
	StateData sd2(&d2[0], &d2[4]);
	State s2(sd2);

	unsigned char d3[4] = {1,2,3,4};
	StateData sd3(&d3[0], &d3[4]);
	State s3(sd3);

	unsigned int black = -1;
	unsigned int white = -1;

	//expect (4,0)
	s1.score(s1,black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect(4,0)
	s1.score(s2,black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect (0,3)
	s1.score(s3,black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	cout<<"s1 num games: "<<s1.getNumGames()<<endl;
	State s1a = s1.getGameByNumber(5);
	cout<<"s1 game 5: "<<s1a<<endl;

	return 0;
}
