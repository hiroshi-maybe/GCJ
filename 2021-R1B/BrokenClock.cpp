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
template<typename integer>
tuple<integer,integer,integer> extended_euclid(integer a, integer b) {
  if (b==0) return make_tuple(a, 1, 0);

  integer d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}
template<typename integer>
integer inverse(integer a, integer mod) {
  integer g,x,_; tie(g,x,_)=extended_euclid(a,mod);

  assert(g==1);
  return x;
}
// $ cp-batch BrokenClock | diff BrokenClock.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BrokenClock.cpp && ./a.out

/*

 4/25/2021

 9:01-10:20 small
 11:06-11:16 small 2
 12:30 pause
 13:40-17:15 read editorials and got AC

 https://twitter.com/satanic0258/status/1386387388310589441
 https://codingcompetitions.withgoogle.com/codejam/round/0000000000435baf/00000000007ae694#analysis
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.828z476qhjy2

 https://twitter.com/satanic0258/status/1386390660983394305
 https://twitter.com/tomerun/status/1386387352398925829
 https://twitter.com/kymn_/status/1386387249843953671
 https://twitter.com/kiri8128/status/1386389126375612416
 https://twitter.com/Rubikun_pro/status/1386388993281970178
 https://twitter.com/_primenumber/status/1386387773075066885

 */

LL A,B,C;

const LL hnano=3600000000000;
const LL mnano=60000000000;
const LL snano=1000000000;
const LL MOD=43200000000000;

void solve() {
  vector<LL> X={A,B,C};
  do {
    LL dx=(X[1]-X[0]+MOD)%MOD;
    LL i11=inverse(11LL,MOD);
    LL t=(LL)((__int128)dx*i11%MOD);
    LL base=(X[0]-t+MOD)%MOD;
    //dump(t,base);
    if((t*12+base)%MOD!=X[1]) continue;
    if((t*720+base)%MOD!=X[2]) continue;

    LL n=t%snano; t/=snano;
    LL s=t%60; t/=60;
    LL m=t%60; t/=60;
    LL h=t;
    assert(h<12);

    cout<<h<<" "<<m<<" "<<s<<" "<<n<<endl;
    return;

    /*
    REP(h,12)REP(m,60)REP(s,60) {
      LL tt=hnano*h+mnano*m+snano*s;

      REP(addM0,2)REP(addM1,2) {
        LL x0=MOD*h+X[0]+MOD*addM0;
        LL x1=MOD*m+X[1]+MOD*addM1;
        LL x0=X[0],x1=X[1];

        LL a=x1-x0;

        if(a%11!=0) continue;
        //dump(h,m,s,x0,x1,a,a%11);
        if(a<0) continue;
        LL n=a/11;
        //if(n>=snano) continue;
        LL base=x0-tt-n;
        //if(base<0) continue;
        //if(base>=MOD) continue;
        //dump(h,m,s,base);
        //assert(base<MOD);

        LL t=tt+n;
        //if((t*720+base)%MOD!=X[2]) continue;

        cout<<h<<" "<<m<<" "<<s<<" "<<n<<endl;

        return;
      }*/

/*
      LL base=(X[0]-tt+MOD)%MOD;
      if((tt*12+base)%MOD!=X[1]) continue;
      if((tt*720+base)%MOD!=X[2]) continue;

      //LL p0=tt+base,p1=MOD*h+X[0];
      //dump(p0,p1,p0-p1,abs(p0-p1)%MOD);
      //assert(p1==p0||p1==p0+MOD);

      //dump((t*12+base)%MOD,m);
      //dump(base,base+t*12,MOD*m+X[1]);
      //dump(base+t*12-(MOD*m+X[1]));

      LL dm1=tt*12,dm2=X[1]-base+MOD*(h);
      if(X[1]-base<0) dm2+=MOD;
      dump(X[1],base,X[1]-base);
      dump(h,m,s,base,(dm2-dm1)%MOD,(dm2-dm1)/MOD,double(dm1),double(dm2));
      assert(dm2-dm1==0);

      return;
    }*/

  } while(next_permutation(ALL(X)));
  assert(false);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>A>>B>>C;

    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
