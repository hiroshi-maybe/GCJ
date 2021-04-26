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

// $ cp-batch Subtransmutation | diff Subtransmutation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Subtransmutation.cpp && ./a.out

/*

 4/25/2021

 10:22-11:06 give up
 17:15-18:00 read editorial and got AC

 https://codingcompetitions.withgoogle.com/codejam/round/0000000000435baf/00000000007ae4aa#problem
 https://twitter.com/tomerun/status/1386387352398925829
 https://twitter.com/satanic0258/status/1386387388310589441
 https://twitter.com/satanic0258/status/1386387988427337733
 https://twitter.com/kymn_/status/1386387249843953671
 https://twitter.com/DEGwer3456/status/1386392213613998080
 https://twitter.com/kiri8128/status/1386389126375612416
 https://twitter.com/_primenumber/status/1386387773075066885

 */

const int MAX_N=21;
int U[MAX_N];
int N,A,B;

bool f(LL st) {
  VI rem(U,U+N);
  map<int,int> S; S[st]=1;
  for(int cur=st; cur>=0; --cur) {
    //dump(st,cur);
    //dumpc(rem);
    //dumpc(S);
    if(accumulate(ALL(rem),0)==0) return true;
    if(S.count(cur)==0) continue;
    int cnt=S[cur];
    auto move=[&](int cnt) {
      if(cur>=A) S[cur-A]+=cnt;
      if(cur>=B) S[cur-B]+=cnt;
      S.erase(cur);
    };
    if(cur>=SZ(rem)||rem[cur]==0) {
      move(cnt);
    } else {
      if(rem[cur]>cnt) return false;
      //dump(cnt,rem[cur],cnt-rem[cur]);
      cnt-=rem[cur];
      rem[cur]=0;
      move(cnt);
    }
  }
  return accumulate(ALL(rem),0)==0;
}

void solve() {
  int res=-1;
  REP(a,410) {
    if(f(a)) {
      res=a;
      break;
    }
  }
  string ans=res==-1?"IMPOSSIBLE":to_string(res+1);
  cout<<ans<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>A>>B;
    REP(i,N) cin>>U[i];

    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}