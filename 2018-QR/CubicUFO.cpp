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

/*
 
 4/7/2018 GCJ Qualification Round
 
 13:30-15:00 Sm ACC, Lg WA
 
 I figured out below area formula:
 
 area(𝛩) = sin𝛩 + √2*cos𝛩
 
 https://www.google.com/search?client=safari&rls=en&ei=m2rJWqz5F4K2sAWE0r_ICg&q=sqrt%282%29*cos%28x%29%2Bsin%28x%29&oq=sqrt%282%29*cos%28x%29%2Bsin%28x%29&gs_l=psy-ab.3..35i39k1j0i8i30k1l3.18718.22771.0.22991.9.8.1.0.0.0.117.686.4j3.7.0....0...1.1.64.psy-ab..1.5.436....0.BsiOo_VgHec
 
 However I couldn't figure out that area is maximal when 𝛩 = atan(1/√2)
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/00000000000000cb/analysis/00000000000079cc
  - http://kmjp.hatenablog.jp/entry/2018/04/08/0900
  - https://twitter.com/tanakh/status/982903856433586176
  - https://twitter.com/kuuso1/status/982815766104817665
  - https://twitter.com/rickytheta/status/982816374102736896
  - https://togetter.com/li/1215911
 
 From Trigonometric Addition Formulas, addition of sin and cos is shown as below:
 
 sin(𝛂+𝛃) = sin𝛂*cos𝛃 + cos𝛂*sin𝛃
 
 Thus formula of sin and cos is shown by single sin.
 
 From the theorem...
 
   area(𝛩)
 = sin𝛩 + √2*cos𝛩
 = √3*(sin𝛩*1/√3 + cos𝛩*√2/√3)
 = √3*sin(𝛩+𝛂) where 𝛂=atan √2
 
 Now we figured out that maximal of area(𝛩) is √3 when 𝛩 = 𝜋/2-𝛂
 Let's define 𝛂' = 𝜋/2-𝛂.
 𝛂 forms right triangle with which tan𝛂=√2
 Now right triangle with 𝛂' is obvious. tan𝛂'=1/√2 => 𝛂'=atan(1/√2)
 
 Trigonometric Addition Formulas
  - http://mathworld.wolfram.com/TrigonometricAdditionFormulas.html
  - http://www.geisya.or.jp/~mwm48961/kou3/trigonometric24.htm
 
 Key:
  - [1,√2] is possible by rotation of single axis. √2 is achievable by 𝛩 = 𝜋/4
  - [√2,√3] is possible by rotating the other axis. √3 is obtained for 𝛩 = atan(1/√2) by trigonometric addition formulas
 
 Summary:
  - I didn't have rotation matrix handy. I needed to search, understand and apply it
  - I completely forgot trigonometric addition formulas. Thus I couldn't figure out radian which gives maximal area. Eventually I got WA in Large test case.
  - `atan2(x,y)` is neat 👍
 
 */

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
