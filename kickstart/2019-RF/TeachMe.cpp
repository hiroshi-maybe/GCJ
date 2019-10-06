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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch TeachMe | diff TeachMe.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TeachMe.cpp && ./a.out

/*
 
 9/29/2019
 
 11:55-12:14 small AC
 
 10/5/2019
 
 17:35-18:15 read editorial and got AC
 
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edc/00000000001864bc
 https://twitter.com/hanseilimak/status/1180653076509708288
 
 */

const int MAX_N=1e5+1;
VI A[MAX_N];
int N,S;

void solve() {
  map<VI,int> cnt;
  REP(i,N) cnt[A[i]]++;
  LL res=0;
  REP(j,N) {
    VI B=A[j];
    int M=SZ(B);
    LL sum=0;
    REP(mask,1<<M) {
      VI x;
      REP(i,M) if((mask>>i)&1) {
        x.push_back(B[i]);
      }
      sum+=cnt[x];
    }
    res+=N-sum;
  }
  cout<<res<<endl;
}

void solve_small() {
  LL res=0;
  REP(j,N) {
    SETI T(ALL(A[j]));
    REP(i,N) if(i!=j) {
      bool ok=false;
      FORR(s,A[i]) if(T.count(s)==0) ok=true;
      res+=ok;
      if(ok) {
        dump(i,j);
        dumpc(A[i]);
        dumpc(A[j]);
      }
    }
  }
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>S;
    REP(i,N) {
      int M; cin>>M;
      REP(_,M) {
        int x; cin>>x;
        A[i].push_back(x);
      }
      sort(ALL(A[i]));
    }
    
    cout<<"Case #"<<t<<": ";
    solve();
    REP(i,N) A[i].clear();
  }
  return 0;
}
