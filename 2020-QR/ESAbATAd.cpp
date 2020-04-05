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

// interactive
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG ESAbATAd.cpp && python local_testing_tool.py ./a.out
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG ESAbATAd.cpp && python interactive_runner.py python local_testing_tool.py 0 -- ./a.out

/*
 
 4/4/2020
 
 14:44-15:42 make local test tool work
 16:00 pause
 17:00-18:20 AC
 
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/0000000000209a9e
 
 */

struct Solve {
public:
  string res;
  Solve(int B) {
    res=string(B,'?');
  }
  char ask(int p) {
    cout<<p+1<<endl;
    char c; cin>>c;
//    dump(c);
    assert(c!='N');
    return c;
  }
  void ans() {
    cout<<res<<endl;
    char verd; cin>>verd;
//    dump(verd);
    if(verd=='N') exit(0);
  }
private:
//  int B;
};

int main() {
  int T; scanf("%d", &T);
  int B; scanf("%d", &B);
  for(int t=1; t<=T; ++t) {
    Solve s(B);
    int invi=-1,revi=-1;
    int cnt=0;
    bool invasked=false,revasked=false;
    bool inverted=false;
    while(count(ALL(s.res),'?')) {
//      dump(s.res);
      if(cnt%10==0) invasked=false,revasked=false;
      if(!invasked&&invi>-1) {
        char c=s.ask(invi);
        if(c!=s.res[invi]) {
          // inverted
          REP(i,B)if(s.res[i]!='?') {
            int a=s.res[i]-'0';
            s.res[i]='0'+a^1;
          }
          inverted=true;
        } else inverted=false;
        invasked=true;
//        dump(invi,c,inverted);
        ++cnt;
        continue;
      } else if(!revasked&&revi>-1) {
        char c=s.ask(revi);
        if(c!=s.res[revi]) {
          // reversed
          reverse(ALL(s.res));
        }
//        dump(revi,c,inverted,c!=s.res[revi]);
        revasked=true;
        ++cnt;
        continue;
      }

      int l=0,r=B-1;
      while(l<r&&s.res[l]!='?'&&s.res[r]!='?') {
        ++l,--r;
      }
      int p=-1;
      if(s.res[l]=='?') p=l;
      else if(s.res[r]=='?') p=r;
      if(p==-1) break;
      char c=s.ask(p);
//      dump(p,c);
      s.res[p]=c;
      
      if(s.res[l]!='?'&&s.res[r]!='?') {
        if(s.res[l]!=s.res[r]) {
          if(revi==-1) revasked=true;
          revi=l;
        } else {
          if(invi==-1) invasked=true;
          invi=l;
        }
      }
      ++cnt;
    }
    s.ans();
  }
  return 0;
}
