#include "path.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{

	PNG origIm1;
	origIm1.readFromFile("images/test.png");
	pair<int,int> start(796,0);
  pair<int,int> end(803,1601);
	path maze(origIm1,start,end);
	PNG out1 = maze.render();
	out1.writeToFile("images/testOut.png");

  return 0;
}
