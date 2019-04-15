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

// $ cp-batch GolfGophers | diff GolfGophers.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GolfGophers.cpp && ./a.out

/*
 
 4/12/2019
 
 20:01-20:25 passed small test set
 
 4/15/2019
 
 10:45-11:45, 13:15-15:30 read editorials and passed large test set
 
 https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104f1a
 http://drken1215.hatenablog.com/entry/2019/04/14/161400
 https://twitter.com/uwitenpen/status/1116908648381308928
 
 Key:
  - guess # from modulo <=> Chinese Remainder Theorem
  - X satisfies ∀i=1..7, X≡B[i] (mod M[i])
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && python testing_tool.py ./a.out
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG GolfGophers.cpp && python interactive_runner.py python testing_tool.py 0 -- ./a.out

const int MAX_N=1e6+1;
int M[7]={17,16,15,13,11,7,5};
int main() {
  int T,N,_M; cin>>T>>N>>_M;
  for(int t=1; t<=T; ++t) {
    VI B(MAX_N,0);
    REP(i,7) {
      int m=M[i];
      REP(i,18) {
        cout<<m;
        if(i==17) cout<<endl;
        else cout<<" ";
      }
      int sum=0;
      REP(i,18) {
        int a; cin>>a;
        sum+=a;
      }
      sum%=m;
      for(int i=sum; i<=MAX_N; i+=m) B[i]++;
    }
    int res=-1;
    REP(i,MAX_N) if(B[i]==7) {
      res=i;
      break;
    }
    assert(res!=-1);
    cout<<res<<endl;
    int verd; cin>>verd;
    if(verd==-1) exit(0);
  }
  return 0;
}

