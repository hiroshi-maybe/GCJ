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

// $ cp-batch JoinTheRanks | diff JoinTheRanks.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address JoinTheRanks.cpp && ./a.out

/*
 
 4/19/2020
 
 10:51-11:31 small WA
 
 4/20/2020
 
 9:20-10:15 read editorial
 21:00-21:15 got AC
 
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef2/00000000002d5b64
 https://twitter.com/yosupot/status/1251942969868824576
 https://twitter.com/snuke_/status/1251944053261787136
 https://twitter.com/gzlcp/status/1251941260195033089
 
 */

int R,S;

vector<II> arr(vector<II> &cur, int pref, int suf) {
  vector<II> A,B,C;
//  dumpc(cur);
//  dump(pref,suf);
  assert(pref<suf);
  REPE(i,pref) A.push_back(cur[i]);
//  dumpc(A);
  FORE(i,pref+1,suf) B.push_back(cur[i]);
//  dumpc(B);
  FOR(i,suf+1,R*S) {
//    dump(i,R*S);
    C.push_back(cur[i]);
  }
//  dumpc(C);
  vector<vector<II>> xs={B,A,C};
  vector<II> res;
  FORR(ps,xs) FORR(p,ps) res.push_back(p);
  return res;
}

int score(VI &cur) {
  int res=0;
  REP(i,SZ(cur)-1) if(cur[i]!=cur[i+1]) ++res;
  return res;
}

void solve() {
  VI cur(R*S);
  REP(i,R*S) cur[i]=i%R;
  assert(score(cur)==S*R-1);
  map<VI, vector<II>> viz;
  queue<VI> Q;
  Q.emplace(cur),viz[cur]={};
  int N=R*S;
  vector<II> res;
  while(SZ(Q)) {
    auto a=Q.front(); Q.pop();
    int scorea=score(a);
    if(scorea==R-1) {
      res=viz[a];
      dumpc(a);
      break;
    }
    FOR(l1,1,N)FOR(l2,1,N) if(l1+l2<N) {
      VI x;
      FOR(i,l1,l1+l2) x.push_back(a[i]);
      REP(i,l1) x.push_back(a[i]);
      FOR(i,l1+l2,N) x.push_back(a[i]);
      if(score(x)<scorea&&!viz.count(x)) {
        vector<II> res=viz[a]; res.emplace_back(l1,l2);
        viz[x]=res;
        Q.push(x);
      }
    }
  }
  cout<<SZ(res)<<endl;
  FORR(p,res) cout<<p.first<<" "<<p.second<<endl;
}

void solve_wrong() {
  vector<II> cur(R*S);
  REP(i,R*S) cur[i]={i%R,i/R};
  vector<II> res;
  for(int r=R-1; r>=0; --r) {
    while(true) {
      int st=R*S-(R-1-r)*S-1;
      int cnt=0;
      for(int i=st; i>st-S; --i) {
        if(cur[i].first==r) cnt++;
        else break;
      }
      if(cnt==S) break;
      int p=-1;
      REP(i,R*S) if(cur[i].first==r) {
        int j=i;
        while(cur[j].first==r) {
          p=j;
          ++j;
        }
        break;
      }
      assert(p!=-1);
      
      assert(p<st-cnt);
      res.emplace_back(p+1,st-cnt-p);
      cur=arr(cur,p,st-cnt);
    }
  }
  dumpc(cur);
  cout<<SZ(res)<<endl;
  FORR(p,res) cout<<p.first<<" "<<p.second<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>R>>S;
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
