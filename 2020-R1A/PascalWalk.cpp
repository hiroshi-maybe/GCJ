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

// $ cp-batch PascalWalk | diff PascalWalk.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PascalWalk.cpp && ./a.out

/*
 
 4/10/2020
 
 18:55-19:25 visible WA
 19:35 visible AC
 
 4/11/2020
 
 12:30-13:52 read editorials and got AC
 
 https://twitter.com/hanseilimak/status/1249432372396691456
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b1353
 
 */

int NN;
int N;

VV<LL> C(510,vector<LL>(510));
void choose(LL N, vector<vector<LL>> &C) {
  for(int i=0; i<=N; ++i) {
    C[i][0]=1;
    for(int j=1; j<=i; ++j) {
      // i chooses j
      C[i][j] = C[i-1][j]+C[i-1][j-1];
    }
  }
}

void print(vector<II> &res) {
  assert(SZ(res)<=500);
  LL sum=0;
  FORR(p,res) sum+=C[p.first-1][p.second-1];
  assert(sum==NN);
  FORR(p,res) cout<<p.first<<" "<<p.second<<endl;
}
bool ith(int a, int i) {
  return (a>>i)&1;
}
void solve() {
  vector<II> res;
  NN=N;
  if(N<=30) {
    REP(i,N) res.emplace_back(i+1,1);
    print(res);
    return;
  }
  int M=N-30;
  int r=1,c=1;
  for(; M>0; ++r) {
    dump(r,c,M%2);
    if(M%2) {
      N-=1<<(r-1);
      int delta=c==1?1:-1;
      if(c!=1) c=r;
      res.emplace_back(r,c);
      REP(i,r-1) {
        c+=delta;
        res.emplace_back(r,c);
      }
    } else {
      N-=1;
      res.emplace_back(r,c==1?1:r);
    }
    M/=2;
  }
  assert(N>=0);
  while(N--) {
    res.emplace_back(r,c==1?1:r);
    ++r;
  }
  print(res);
}
void solve_small() {
  vector<II> res(1,{1,1});
  LL sum=1;
  if(N==1) {
    print(res);
    return;
  }
  sum+=1,res.emplace_back(2,1);
  while(sum<N) {
    int prevr=res.back().first,prevc=res.back().second;
    int r=prevr+1;
    if(sum+r-1<=N) {
      sum+=r-1,res.emplace_back(r,2);
    } else {
      sum+=1,res.emplace_back(prevc==2?prevr:r,1);
    }
  }
  assert(sum==N);
  print(res);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  choose(500,C);
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    cout<<"Case #"<<t<<":\n";
    solve();
  }
  return 0;
}
