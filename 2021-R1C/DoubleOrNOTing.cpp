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
long long bin2n(string s) {
  long long res=0;
  for(int i=0; i<s.size(); ++i) {
    res=2LL*res+(s[i]=='1');
  }
  return res;
}
string n2bin(long long n) {
  if(n<0) dump(n);
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  if(res.empty()) res="0";
  return string(res.rbegin(), res.rend());
}
// $ cp-batch DoubleOrNOTing | diff DoubleOrNOTing.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DoubleOrNOTing.cpp && ./a.out

/*

 5/1/2021

 3:29-3:56 WA for dfs
 4:18 WA for BFS
 4:30 give up

 22:30-23:43 read editorials and got AC for test set 1

 https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c1139#analysis
 https://kmjp.hatenablog.jp/entry/2021/05/02/0930

 */

string S,E;
// 1e15 mle 1e13 TLE 1e12 WA 5e12 TLE
// 1e10 WA
const LL lb=5e12;
const int Inf=1e8;

void inv(string &s) {
  reverse(ALL(s));
  while(SZ(s)>0&&s.back()=='1') s.pop_back();
  if(s.empty()) s='1';
  REP(i,SZ(s)) s[i]='0'+(1-(s[i]-'0'));
  reverse(ALL(s));
}

int solve() {
  if(S==E) return 0;

  map<string,int> D;
  queue<string> Q;
  auto maypush=[&](string n, int step) {
    if(D.count(n)) return;
    Q.emplace(n),D[n]=step;
  };
  maypush(S,0);
  while(SZ(Q)) {
    string ss=Q.front(); Q.pop();
    int step=D[ss];
    if(SZ(ss)>=20) continue;
    //dump(ss,step);
    if(ss+'0'==E) return step+1;
    if(ss!="0") maypush(ss+'0',step+1);
    inv(ss);
    if(ss==E) return step+1;
    maypush(ss,step+1);
  }

  return Inf;
}

void solve_wa() {
  int res=Inf;
  auto dfs=[&](auto &&self, string &s, int step) {
    if(step>23) return;
    if(s==E) {
      SMIN(res,step);
      return;
    }

    s.push_back('0');
    self(self,s,step+1);
    s.pop_back();

    string ss=s;
    inv(ss);
    self(self,ss,step+1);
  };

  string s=S;
  dfs(dfs,s,0);
  if(res==Inf) {
    cout<<"IMPOSSIBLE"<<endl;
  } else {
    cout<<res<<endl;
  }
}
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*string x="0";
  inv(x);
  dump(x);*/

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>S>>E;

    cout<<"Case #"<<t<<": ";
    int res=solve();
    if(res>=Inf) {
      cout<<"IMPOSSIBLE"<<endl;
    } else {
      cout<<res<<endl;
    }
  }
  return 0;
}