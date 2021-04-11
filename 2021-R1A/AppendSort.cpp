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

// $ cp-batch AppendSort | diff AppendSort.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AppendSort.cpp && ./a.out

/*

 4/9/2021

 18:01-18:45 WA
 19:00 AC

 https://codingcompetitions.withgoogle.com/codejam/round/000000000043585d/00000000007549e5#analysis
 https://kmjp.hatenablog.jp/entry/2021/04/10/0900

 https://twitter.com/tanakh/status/1380726244585611267
 https://twitter.com/laycrs/status/1380724825300168705
 https://twitter.com/semiexp/status/1380725808935755778
 https://twitter.com/yamerarenaku/status/1380726505299271680

 */

const int MAX_N=1e6+1;
string A[MAX_N];
int N;

int comp(string a, string b) {
  if(SZ(a)<SZ(b)) return 1;
  if(SZ(a)>SZ(b)) return -1;
  REP(i,SZ(a)) if(a[i]!=b[i]) return a[i]<b[i]?1:-1;
  return 0;
}

string add1(string s) {
  string res;
  reverse(ALL(s));
  int c=1;
  REP(i,SZ(s)) {
    int d=s[i]-'0'+c;
    res.push_back('0'+d%10);
    c=d/10;
  }
  if(c>0) res.push_back('1');
  reverse(ALL(res));
  return res;
}

void solve() {
  int res=0;
  vector<string> B(A,A+N+1);
  FORE(i,1,N) {
    string pre=B[i-1],cur=B[i];
    if(comp(pre,cur)==1) continue;

    int preflen=SZ(cur),suflen=SZ(pre)-preflen;
    string pref=pre.substr(0,preflen);
    int c=comp(pref,cur);
    //dump(i,pre,pref,cur,suflen,c);
    string app;
    if(c==-1) {
      // pref > cur
      app=string(suflen+1,'0');
    } else if(c==1) {
      // pref < cur
      app=string(suflen,'0');
    } else {
      string suf1=pre.substr(preflen,suflen);
      string suf2=add1(suf1);
      if(SZ(suf2)==suflen) app=suf2;
      else app=string(suflen+1,'0');
      //dump(suf1,suf2,app);
    }

    B[i]=cur+app;
    res+=SZ(app);
    //dump(news);
    assert(comp(B[i-1],B[i])==1);
  }
  //dump(res);
  //dumpc(B);
  cout<<res<<endl;
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
  N=genRandNum(2,100);
  VI as=genRandSeq(N,1,10);
  REP(i,N) A[i]=to_string(as[i]);
  solve();
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>A[i+1];

    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}