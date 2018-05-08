#include "path.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{

	PNG origIm1;
	origIm1.readFromFile("images/maze.png");
	pair<int,int> start(150,3);
  	pair<int,int> end(164,321);
	path maze(origIm1,start,end);
	PNG out1 = maze.render();
	out1.writeToFile("images/testOut.png");

  return 0;
}
