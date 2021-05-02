#include <bits/stdc++.h>
using namespace std;
// type alias
typedef uint64_t LL;
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

// $ cp-batch RoaringYears | diff RoaringYears.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RoaringYears.cpp && ./a.out

/*

 5/1/2021

 3:03-3:27 small AC

 13:15-14:00, 21:00-22:21 read editorial and got AC with uint64_t

 https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c0f01#analysis

 https://twitter.com/ei1333/status/1388456164803842050
 https://twitter.com/ei1333/status/1388456523689431050
 https://twitter.com/kuuso1/status/1388457593924767745

 */

LL Y;
string build(LL st, int cnt) {
  string cur;
  REP(k,cnt) {
    cur+=to_string(st+k);
  }
  if(st==97&&cnt==8) dump(cur);
  //dump(st,cnt,SZ(cur));
  return cur;
}
LL toN(string s) {
  if(SZ(s)>19) return numeric_limits<LL>::max();
  LL res=0;
  REP(i,SZ(s)) res=res*10+(s[i]-'0');
  return res;
}

bool ok(LL st, int cnt) {
  string s=build(st,cnt);
  if(SZ(s)>19) return true;
  LL n=toN(s);
  if(st==98&&cnt==7) dump(st,cnt,s,n);
  return n>Y;
}
LL f(int cnt) {
  LL bad=0,good=1e10;
  while(good-bad>1) {
    LL mid=(good+bad)/2;
    bool res=ok(mid, cnt);
    if(cnt==7) dump(mid,res);
    (res?good:bad)=mid;
  }

  LL res= toN(build(good,cnt));
  dump(cnt,good,res);
  return res;
}
LL solve() {
  LL res=numeric_limits<LL>::max();
  FORE(cnt,2,14) SMIN(res,f(cnt));
  assert(res>Y);
  return res;
}

bool ok(LL n) {
  string s=to_string(n);
  int N=SZ(s);
  FORE(l,1,N/2) {
    LL cur=stoll(s.substr(0,l));

    bool ok=true;
    int p=l;
    while(ok&&p<N) {
      LL nxt=cur+1;
      string nxts=to_string(nxt);
      if(SZ(nxts)>N-p) ok=false;
      else {
        string t=s.substr(p,SZ(nxts));
        ok&=t==nxts;
        cur=nxt,p+=SZ(nxts);
      }
    }
    if(ok) return true;
  }
  return false;
}
LL solve_small() {
  LL n=Y+1;
  while(true) {
    bool res=ok(n);
    //dump(n,res);
    if(res) return n;
    n+=1;
  }
  assert(false);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>Y;

    cout<<"Case #"<<t<<": ";
    cout<<solve()<<endl;
  }
  return 0;
}
