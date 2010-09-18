#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Controller.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	State s1("abcd");
	State s2("abcd");
	State s3("bcde");
	int black = -1;
	int white = -1;

	//expect (4,0)
	s1.score(s1,black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect(4,0)
	s1.score(s2,black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;

	//expect (0,3)
	s1.score(s3,black, white);
	cout<<"black: "<<black<<" white: "<<white<<endl;
	return 0;
}
