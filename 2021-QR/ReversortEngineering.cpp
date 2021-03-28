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

// $ cp-batch ReversortEngineering | diff ReversortEngineering.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ReversortEngineering.cpp && ./a.out

/*

 3/26/2021

 20:28-21:11 sample failed
 21:13 AC

 https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d12d7
 https://kmjp.hatenablog.jp/entry/2021/03/28/0900

 */

int N,C;

LL calccost(VI &A) {
  LL res=0;
  REP(i,N-1) {
    int p=min_element(A.begin()+i,A.end())-A.begin();
    //dump(i,p,A[p]);
    res+=p-i+1;
    reverse(A.begin()+i,A.begin()+p+1);
  }
  //dumpC(A,A+N);
  REP(i,N) assert(A[i]==i+1);
  return res;
}

void solve() {
  int c=C-(N-1);
  if(c<0) {
    cout<<"IMPOSSIBLE"<<endl;
    return;
  }

  VI ord(N); REP(i,N) ord[i]=i;
  VI A(N,0);
  REP(i,N) {
    int cap=N-1-i;
    int offset=min(cap,c);
    assert(i+offset<N);
    int p=ord[i+offset];
    //dump(i,offset,p);
    assert(A[p]==0);
    A[p]=i+1;
    c-=offset;
    reverse(ord.begin()+i,ord.begin()+i+offset+1);
    //dumpc(ord);
    //dumpc(A);
  }

  if(c>0) {
    cout<<"IMPOSSIBLE"<<endl;
    return;
  }

  REP(i,N) cout<<A[i]<<" \n"[i==N-1];
  LL cost=calccost(A);
  assert(cost==C);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
void test() {
  N=genRandNum(2,10),C=genRandNum(N-1,(N-1)*(N+2)/2);
  //dump(N,C);
  solve();
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>C;
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
