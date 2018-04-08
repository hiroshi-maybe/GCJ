//#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

const double PI = 3.14159265358979323846;
const double PI_4 = PI/4.0;
const double EPS=1e-8;

vector<double> mult(vector<vector<double>> T, vector<double> A) {
  vector<double> res(3, 0.0);
  REP(i,3) REP(j,3) {
    res[i]+=A[j]*T[i][j];
  }
  return res;
}

vector<double> rotate(double radZ, double radX, vector<double> base) {
  vector<vector<double>> TX={
    {      1.0,        0.0,       0.0},
    {      0.0,  cos(radX), sin(radX)},
    {      0.0, -sin(radX), cos(radX)}
  };
  vector<vector<double>> TZ={
    { cos(radZ), sin(radZ),       0.0},
    {-sin(radZ), cos(radZ),       0.0},
    {      0.0,        0.0,       1.0}
  };
  
  auto m1=mult(TX,base);
  auto m2=mult(TZ,m1);
  return m2;
}

double area2d(double rad) {
  return sqrt(2.0)*cos(PI_4-rad);
}

double area3d(double rad) {
  return sqrt(2.0)*cos(rad)+sin(rad);
}

double solve2d(double A) {
  double good=0,bad=PI_4;
  REP(_, 1000) {
    double mid=0.5*(good+bad);
//    dump4(A,good,bad,area(mid));
    if(area2d(mid)<=A) good=mid;
    else bad=mid;
  }
  dump2(good,area2d(good));
  return good;
}

double solve3d(double A) {
  double good=0,bad=0.615335786;
  REP(_, 1000) {
    double mid=0.5*(good+bad);
    //    dump4(A,good,bad,area(mid));
    if(area3d(mid)<=A) good=mid;
    else bad=mid;
  }
  dump2(good,area3d(good));
  return good;
}

vector<vector<double>> solve(double A) {
  vector<vector<double>> base={
    {0.5,  0,  0},
    {  0,0.5,  0},
    {  0,  0,0.5}
  };
  if(A<=sqrt(2.0)) {
    double rad=solve2d(A);
    vector<vector<double>> res(3);
    REP(i,3) res[i]=rotate(rad,0,base[i]);
    return res;
  }

  double rad=solve3d(A);
  vector<vector<double>> res(3);
  REP(i,3) res[i]=rotate(PI_4,rad,base[i]);
  return res;
}

double deg2rad(double deg) {
  return deg*M_PI/180.0;
}

// http://cplussplussatplay.blogspot.com/2012/01/3d-object-rotation.html
// 15:20-18:20
int main() {
  dump2(area3d(deg2rad(0)),area3d(0.615335786));
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    double A;
    cin >> A;
    cout << "Case #" << t << ":" << endl;
    auto res = solve(A);
    REP(i,3) {
      cout << res[i][0] << " " << res[i][1] << " " << res[i][2] << endl;
    }
  }
  return 0;
}
