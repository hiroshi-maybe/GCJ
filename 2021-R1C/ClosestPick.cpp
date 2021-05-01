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

// $ cp-batch ClosestPick | diff ClosestPick.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ClosestPick.cpp && ./a.out

/*

 5/1/2021

 2:01-2:47 WA
 3:01 AC

 https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c0f00#analysis
 https://twitter.com/ei1333/status/1388456164803842050

 */

const int MAX_N=31;
int N,P[MAX_N];
int K;
int solve() {
  VI ps(P,P+N);
  sort(ALL(ps));

  int res=0;

  {
    VI xs={0,0};
    if(ps[0]>1) {
      xs.push_back(ps[0]-1);
    }
    if(ps.back()<K) {
      xs.push_back(K-ps.back());
    }
    REP(k,N-1) {
      int l=ps[k],r=ps[k+1],med=(l+r)/2;
      int x=0;
      FORE(i,max(med-10,l+1),min(med+10,r-1)) {
        int lb=(i+l)/2+1,rb=(r+i+1)/2-1;
        SMAX(x,rb-lb+1);
      }
      xs.push_back(x);
    }
    sort(ALL(xs)),reverse(ALL(xs));
    //dumpc(xs);
    SMAX(res,xs[0]+xs[1]);
  }

  {
    REP(k,N-1) SMAX(res,ps[k+1]-ps[k]-1);
  }

  return res;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=genRandNum(1,30);
  K=genRandNum(1,30);
  VI ps=genRandSeq(N,1,K+1);
  REP(i,N) P[i]=ps[i];

  int exp=0;
  FORE(j,1,K) FOR(i,1,j) {
    int res=0;
    FORE(c,1,K) {
      int d1=min(abs(i-c),abs(j-c));
      int d2=K;
      REP(k,N) SMIN(d2,abs(P[k]-c));
      res+=d1<d2;
    }
    SMAX(exp,res);
  }

  cout<<N<<" "<<K<<endl;
  REP(i,N) cout<<P[i]<<" ";
  cout<<endl;
  int act=solve();
  dump(exp,act);
  assert(exp==act);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>K;
    REP(i,N) cin>>P[i];

    cout<<"Case #"<<t<<": ";
    int res=solve();
    double ans=(double)res/K;
    cout<<ans<<endl;
  }
  return 0;
}
