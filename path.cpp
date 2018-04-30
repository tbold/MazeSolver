#include "path.h"
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

// used to initialize member variable pathPts.
// called by constructor to create path if it
// exists.
void path::BFS(){
  vector<vector<bool>> V (image.height(), vector<bool> (image.width(),false));
  vector<vector<pair<int,int>>> P (image.height(), vector<pair<int,int>> (image.width(),end));

  queue<pair<int, int>> q;
  pair<int, int> s = start;
  V[s.second][s.first] = true; //start pos is visited
  P[s.second][s.first] = s; //start's predecessor is itself
  q.push(s);  //enqueue start

  while (!q.empty()){
    pair<int, int> curr = q.front(); //what if curr is endpoint?
    if (curr.first == end.first && curr.second == end.second){
      break;
    }
    q.pop(); //dequeue current
    vector<pair<int, int>> adjacent = neighbors(curr);
    vector<pair<int, int>> goodAdjacentV = goodAdjacent(curr, adjacent, V);

    for (int i=0; i< ((int)goodAdjacentV.size());i++){ //loop through neighbors
      if (!V[goodAdjacentV[i].second][goodAdjacentV[i].first]){ //if unvisited
        V[goodAdjacentV[i].second][goodAdjacentV[i].first] = true;
        P[goodAdjacentV[i].second][goodAdjacentV[i].first] = curr;
        q.push(goodAdjacentV[i]); //enqueue neighbors
      }
    }
  }
	pathPts = assemble(P,start,end);

}

vector<pair<int,int>> path::goodAdjacent(pair<int,int> curr, vector<pair<int,int>> v, vector<vector<bool>> V){
  vector<pair<int,int>> returnVector;
  for (int i=0; i<((int) v.size()); i++){
    if (good(V, curr, v[i])){
      returnVector.push_back(v[i]);
    }
  }
  return returnVector;
}


//draws path points in red on a copy of the image and returns it
PNG path::render(){

  PNG returnImage = PNG(image);
  for (int i=0; i< ((int)pathPts.size()); i++){
    RGBAPixel *pixel = returnImage.getPixel(pathPts[i].first, pathPts[i].second);
    pixel->r = 255;
    pixel->g = 0;
    pixel->b =0;
  }
  return returnImage;

}
//returns path of points
vector<pair<int,int>> path::getPath() { return pathPts;}

//returns length of shortest path of points
int path::length() { return pathPts.size();}

// tests a neighbor (adjacent vertex) to see if it is
// 1. within the image, 2. unvisited, and 3. close in color to curr. An entry in table V is true if a cell has previously been
// visited.
bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
  if (next.first >= (int) image.width() || next.first < 0 || next.second < 0 || next.second >=(int) image.height()){
    return false;
  }
  if (v[next.second][next.first] == true){
    return false;
  }
  if (!closeEnough(*image.getPixel(curr.first, curr.second), *image.getPixel(next.first, next.second))){
    return false;
  }
  return true;

}

// builds a vector containing the locations of the
// four vertices adjacent to curr: above, left, right, below.
vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;
  n.push_back(make_pair(curr.first-1, curr.second));//left

  n.push_back(make_pair(curr.first, curr.second+1));//below
  n.push_back(make_pair(curr.first+1, curr.second));//right
  n.push_back(make_pair(curr.first, curr.second-1));//above
  return n;
}


// returns the set of points on the shortest path from s to e, if
// it exists.
vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
  vector<pair<int,int>> path;
  stack<pair<int,int>> stack;
  while (p[e.second][e.first] != e){
    stack.push(p[e.second][e.first]);
    e = p[e.second][e.first];
  }
  int size = stack.size();
  while (!stack.empty()){
    pair<int,int> temp = stack.top();
    path.push_back(temp);
    stack.pop();
  }
  if (size < 1){
    path.push_back(s);
  } else {
    path.push_back(end);
  }
  path.push_back(end);

  return path;



}


// tests whether p1 and p2 are near in color. returns
// true if the sum of squared difference over color channels
// is less than or equal to 80.
bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
