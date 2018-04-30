
#ifndef _PATH_H
#define _PATH_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>
using namespace std;
using namespace cs221util;

class path {

public:

	path(const PNG & im,pair<int,int> s,pair<int,int> e);

	PNG render();

	vector<pair<int,int> > getPath();

	int length();

private:

    
   void BFS();

   
	bool good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next);

    
	vector<pair<int,int>> neighbors(pair<int,int> curr) ;


	vector<pair<int,int>> assemble(vector<vector<pair<int,int>>> & p,
		pair<int,int> s, pair<int,int> e);
		vector<pair<int,int>> goodAdjacent(pair<int,int> curr, vector<pair<int,int>> v, vector<vector<bool>> V);

    
    bool closeEnough(RGBAPixel p1, RGBAPixel p2);


	vector <pair<int,int>> pathPts;

	pair<int,int> start;
	pair<int,int> end;
	PNG image;

};

#endif
