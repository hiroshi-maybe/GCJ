#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch Elevanagram | diff Elevanagram.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Elevanagram.cpp && ./a.out

/*
 
 11/16/2019
 
 22:35-23:35 small AC
 23:50 give up
 
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edd/00000000001a286d
 https://twitter.com/hanseilimak/status/1196170404273872897
 https://twitter.com/ymatsux_game/status/1195995573234462722
 
 */

const int MAX_N=10;
LL D[MAX_N];
int N;

bool dp[10][200][11];
bool solve() {
  ZERO(dp);
  LL tot=accumulate(D,D+9,0LL);
  dp[0][0][0]=true;
  REP(i,9) {
    int d=i+1;
    REPE(x,90)REP(y,11) if(dp[i][x][y]) REPE(ncnt1,D[i]) {
      int dt = ncnt1*(11-d)%11+(D[i]-ncnt1)*d%11;
      dp[i+1][x+ncnt1][(y+dt)%11]=true;
//      dump(i,x,y,ncnt1,dt,x+ncnt1,(y+dt)%11);
    }
  }
//  dump(tot);
  return dp[9][tot/2][0];
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    REP(i,9) cin>>D[i];
    
    cout<<"Case #"<<t<<": ";
    cout<<(solve()?"YES":"NO")<<endl;
  }
  return 0;
}
