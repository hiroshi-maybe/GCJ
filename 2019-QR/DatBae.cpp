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

// $ cp-batch DatBae | diff DatBae.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DatBae.cpp && ./a.out
//

/*
 
 4/6/2019
 
 18:58-21:00, 22:30-25:00 fucking interactive problem.
 
 4/9/2019
 
 18:25-19:50 read editorial and got AC with initial segment size=16
 
 No need to start from segment size 32. Start from 16.
 
 http://kmjp.hatenablog.jp/entry/2019/04/07/1000
 https://naoyat.hatenablog.jp/entry/GCJ2019QR
 https://codingcompetitions.withgoogle.com/codejam/round/0000000000051705/000000000008830b
 https://twitter.com/kyuridenamida/status/1114729292980572160
 https://twitter.com/_TTJR_/status/1114714878369980416
 https://twitter.com/kuuso1/status/1114712995030913024
 https://twitter.com/beet_aizu/status/1114712298948517889
 https://twitter.com/prd_xxx/status/1114712184372600832
 https://twitter.com/koyumeishi_/status/1114711588554989569
 https://twitter.com/gzlcp/status/1114710351570800640
 https://twitter.com/kojingharang/status/1114711298833506310
 
 4/10/2019
 
 Add solution with 4 queries
 
 */

// interactive (stdio)
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG DatBae.cpp && python testing_tool.py ./a.out
struct Solve {
public:
  int len=32,M=0;
  vector<int> cnt1;
  string make(int l) {
    assert(l>=1);
    string res;
    int p=0;
    REP(i,N) {
      res.push_back('0'+p);
      if(i%l==l-1) p^=1;
    }
    return res;
  }
  void update(string S) {
    int len2=len/2,MM=(N+len2-1)/len2;
    int j=0,k=0;
    VI cnt2(MM,0);
    dumpc(cnt1);
    for(int i=0; i<M; ++i) {
      int L=cnt1[i];
      int cnt[2]={0};
      REP(c,2) cnt[c]=count(S.begin()+k,S.begin()+k+L,'0'+c);
      cnt2[j++]=cnt[0];
      if(j<MM) cnt2[j++]=cnt[1];
      k+=L;
    }
    dump(len,M,len2,MM,S);
    dumpc(cnt2);
    assert(j==MM);
    len=len2,M=MM,cnt1=cnt2;
  }
  string ask() {
    string Q=make(len/2);
    dump(Q);
    cout<<Q<<endl;
    string res; cin>>res;
    dump(Q,res);
    //assert(res!="-1");
    if(res=="-1") exit(0);
    assert(SZ(res)==N-B);
//    update(res);
    return res;
  }
  Solve(int N, int B, int F): N(N),B(B),F(F) {
    M=(N+15)/16;
    cnt1=VI(M,0);
    
    string s=ask();
    int j=0;
    for(int i=0,x=0; i<N-B; ++i) {
      ++x;
      if(i==N-B-1||s[i+1]!=s[i]) cnt1[j++]=x,x=0;
    }
    assert(j==M);
    dumpc(cnt1);
    len/=2;
  }
  bool answer() {
    assert(SZ(cnt1)==N);
    VI res;
    REP(i,N) if(cnt1[i]==0) res.push_back(i);
    dumpc(res);
    assert(SZ(res)==B);
    REP(i,B) {
      cout<<res[i];
      if(i!=B-1) cout<<" ";
    }
    cout<<endl;
    
    int verd; cin>>verd;
    return verd==1;
  }
private:
  int N,B,F;
};

int main_org() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(0);
  int T; cin>>T;
  dump(T);
  for(int t = 1; t <= T; ++t) {
    int N,B,F; cin>>N>>B>>F;
    dump(N,B,F);
    Solve s(N,B,F);
    int q=4;
    while(q--) {
      string x=s.ask();
      s.update(x);
    }
    if(!s.answer()) exit(0);
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    int N,B,F; cin>>N>>B>>F;
    
    string Q[4],R[4];
    REP(i,N) REP(j,4) {
      int a=i%16;
      Q[j].push_back('0'+(a>>j)%2);
    }
    REP(i,4) {
      cout<<Q[i]<<endl;
      string r; cin>>r;
      if(r=="-1") exit(0);
      R[i]=r;
    }
    VI res;
    int k=0;
    REP(i,N) {
      bool ok=true;
      REP(j,4) {
        int a=R[j][k]-'0',b=((i%16)>>j)&1;
        if(a!=b) ok=false;
      }
      if(ok) ++k;
      else res.push_back(i);
    }
    assert(SZ(res)==B);
    REP(i,B) {
      cout<<res[i];
      if(i==B-1) cout<<endl;
      else cout<<' ';
    }
    int verd; cin>>verd;
    if(verd==-1) exit(0);
  }
  return 0;
}
