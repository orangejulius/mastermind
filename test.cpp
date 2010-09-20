#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Controller.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	Environment e1(4,6,10);
	StateData* sd1 = new unsigned char[4];
	sd1[0] = 0;
	sd1[1] = 1;
	sd1[2] = 2;
	sd1[3] = 3;
	State s1(&e1, sd1);

	StateData* sd2 = new unsigned char[4];
	sd2[0] = 0;
	sd2[1] = 1;
	sd2[2] = 2;
	sd2[3] = 3;
	State s2(&e1, sd2);

	StateData* sd3 = new unsigned char[4];
	sd3[0] = 1;
	sd3[1] = 2;
	sd3[2] = 3;
	sd3[3] = 4;
	State s3(&e1, sd3);

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

	cout<<"s1 num games: "<<e1.getNumGames()<<endl;
	State s1a = e1.getGameByNumber(5);
	cout<<"s1 game 5: "<<s1a<<endl;

	return 0;
}
