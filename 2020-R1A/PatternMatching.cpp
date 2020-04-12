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
// note that the last empty element is trimmed
vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}

// $ cp-batch PatternMatching | diff PatternMatching.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PatternMatching.cpp && ./a.out

/*
 
 4/10/2020
 
 18:01-18:54 AC
 
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b3034
 
 */

const int MAX_N=1e6+1;
string P[MAX_N];
int N;

int prefpos(string &s) {
  int p=s.find('*');
  assert(p!=string::npos);
  return p;
}

string maxpref(vector<string> ss) {
  int L=0;
  REP(i,SZ(ss)) SMAX(L,SZ(ss[i]));
  dumpc(ss);
  string res="";
  REP(i,L) {
    set<char> cs;
    REP(j,SZ(ss)) {
      if(i<SZ(ss[j])) cs.emplace(ss[j][i]);
    }
    dump(i,SZ(cs));
    if(SZ(cs)>1) return "*";
    res.push_back(*cs.begin());
  }
  dump(L,res);
  return res;
}

void solve() {
  vector<string> ps,ms,ss;
  REP(i,N) {
    string s=P[i];
    int prefp=prefpos(s);
    dump(i,prefp);
    string pref=s.substr(0,prefp);
    string revs=s; reverse(ALL(revs));
    int sufp=prefpos(revs);
    string suf=revs.substr(0,sufp);

    dump(pref,suf);
    
    string mid="";
    if(count(ALL(s),'*')>1) {
      s=s.substr(prefp+1);
      dump(i,s);
      reverse(ALL(s));
      s=s.substr(sufp+1);
      dump(i,s);
      reverse(ALL(s));
      REP(i,SZ(s)) if(s[i]!='*') mid.push_back(s[i]);
    }
        
    if(SZ(pref)) ps.push_back(pref);
    if(SZ(suf)) ss.push_back(suf);
    if(SZ(mid)) ms.push_back(mid);
  }
  
  string pref=maxpref(ps);
  if(pref=="*") {
    cout<<pref<<endl;
    return;
  }
  string suf=maxpref(ss);
  if(suf=="*") {
    cout<<suf<<endl;
    return;
  }
  reverse(ALL(suf));
  string mid="";
  FORR(s,ms) mid+=s;
  string res=pref+mid+suf;
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>P[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
