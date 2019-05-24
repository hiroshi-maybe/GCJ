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

// $ cp-batch NewElementsPart2 | diff NewElementsPart2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NewElementsPart2.cpp && ./a.out
struct Frac {
public:
  // numerator / denominator
  int n,d;
  Frac(): n(0),d(1) {}
  Frac(int nn) : n(nn), d(1) {}
  Frac(long long nn, long long dd) { norm(nn,dd); }
  Frac(int nn, int dd) { norm(nn,dd); }
  Frac& norm(long long nn, long long dd) {
    assert(dd!=0);
    if(dd<0) nn*=-1,dd*=-1;
    bool neg=nn<0;
    nn=neg?-nn:nn;
    long long g=gcd(nn,dd);
    nn/=g,dd/=g;
    assert(nn<numeric_limits<int>::max()&&dd<numeric_limits<int>::max());
    this->n=nn;
    if(neg) this->n=-1*this->n;
    this->d=dd;
    return *this;
  }
  Frac abs() { return Frac(n<0?-n:n,d); }
  Frac inv() { return Frac(d,n); }
  Frac &operator -() { n=-n; return *this; }
  Frac &operator += (Frac that) { long long nn=(long long)n*that.d+(long long)that.n*d,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator -= (Frac that) { *this+=-that; return *this; }
  Frac &operator *=(Frac that) { long long nn=(long long)n*that.n,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator /= (Frac that) { *this*=Frac(that.d,that.n); return *this; }
  Frac operator+(Frac that) const { return Frac(*this)+=that; }
  Frac operator-(Frac that) const { return Frac(*this)-=that; }
  Frac operator*(Frac that) const { return Frac(*this)*=that; }
  Frac operator/(Frac that) const { return Frac(*this)/=that; }
  bool operator < (Frac that) { return (long long)n*that.d<(long long)that.n*d; }
  bool operator > (Frac that) { return that<Frac(*this); }
  bool operator == (Frac that) { return n==that.n&&d==that.d; }
  bool operator <= (Frac that) { return Frac(*this)<that||Frac(*this)==that; }
  bool operator >= (Frac that) { return Frac(*this)>that||Frac(*this)==that; }
  friend ostream& operator<<(ostream& os, const Frac& that) { return os<<that.n<<"/"<<that.d; }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
};
/*
 
 5/18/2019
 
 8:11-9:13 WA
 
 5/23/2019
 
 9:35-11:00 read editorials and visible test set passed
 
 22:20-23:10 read an article of Stern Brocot Tree
 
 5/24/2019
 
 10:10-11:00, 12:00-13:40 learned Stern Brocot Tree and got AC
 
 Stern Brocot Tree
 http://satashun.hatenablog.com/entry/2018/12/13/163524
 https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree
 
 Continued fraction
 https://en.wikipedia.org/wiki/Continued_fraction#Best_rational_within_an_interval
 
 hidden:
 https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146184
 http://kmjp.hatenablog.jp/entry/2019/05/22/0900
 https://twitter.com/tempura_cpp/status/1129788474851090432
 https://scrapbox.io/snuke/GCJ_2019_R2
 https://twitter.com/osrehun/status/1129787443530436610
 https://twitter.com/osrehun/status/1129796161835896832
 https://twitter.com/kakira9618/status/1129788831685861377
 https://twitter.com/chokudai/status/1129787506017226752
 visible:
 https://twitter.com/xuzijian629/status/1129787683323170816
 https://twitter.com/n_vip/status/1129787028193857536
 https://twitter.com/mistter_gp/status/1129788197708283905
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG NewElementsPart2.cpp && ./a.out < NewElementsPart2.in | diff NewElementsPart2.out -
const int MAX_N=100+1;
int A[MAX_N],B[MAX_N];
int N;

const int Inf=2e9;
Frac f(Frac lb, Frac hb) {
  if(lb<Frac(1,1)&&Frac(1,1)<hb) return Frac(1,1);
  Frac res;
  if(hb<=Frac(1,1)) {
    // lb<hb<=1
    if(lb.n==0) lb=Frac(1,Inf);
    if(hb.n==0) hb=Frac(1,Inf);
    res=f(hb.inv(),lb.inv());
    if(res.n==0) res=Frac(Inf,1);
    res=res.inv();
  } else {
    // 1<=lb<hb
    int x=lb.n/lb.d;
    lb-=x,hb-=x;
    res=f(lb,hb);
    res+=x;
  }
  return res;
}

string solve() {
  Frac lb(0,1),rb(Inf,1);
  bool ok=true;
  REP(j,N)REP(i,j) {
    int a=A[i],b=B[i],c=A[j],d=B[j];
    if(a==c) ok&=d>b;
    else {
      if(a>c) {
        Frac x(d-b,a-c);
        SMIN(rb,x);
      } else {
        Frac x(d-b,a-c);
        SMAX(lb,x);
      }
    }  }
  ok&=lb<rb;
  if(!ok) return "IMPOSSIBLE";
  
  auto res=f(lb,rb);
  return to_string(res.n)+" "+to_string(res.d);
}

string solve_small2() {
  FORE(x,1,1000)FORE(y,1,1000) {
    bool ok=true;
    REP(i,N-1) {
      LL a=A[i],b=B[i],c=A[i+1],d=B[i+1];
      ok&=(a*x+b*y<c*x+d*y);
    }
    if(ok) {
      return to_string(x)+" "+to_string(y);
    }
  }
  return "IMPOSSIBLE";
}

string solve_small1() {
  Frac lb(0,1),rb(101,1);
  bool ok=true;
  REP(j,N)REP(i,j) {
    int a=A[i],b=B[i],c=A[j],d=B[j];
    if(a==c) ok&=d>b;
    else /*if((LL)(a-c)*(d-b)>0) */{
      if(a>c) {
        Frac x(d-b,a-c);
        SMIN(rb,x);
      } else {
        Frac x(d-b,a-c);
        //      dump(i,j,x);
        SMAX(lb,x);
      }
    }/* else if(b-d!=0) {
      dump(a,b,c,d);
      ok=false;
    }*/
  }
//  dump(lb,rb);
  ok&=lb<rb;
  if(ok) {
    const int Inf=1e9;
    II res={Inf,Inf};
    FORE(x,1,1000)FORE(y,1,1000) {
      Frac a(x,y);
      if(lb<a&&a<rb) SMIN(res,{x,y});
    }
    assert(res.first!=Inf);
    return to_string(res.first)+" "+to_string(res.second);
  } else {
    return "IMPOSSIBLE";
  }
}

pair<Frac,Frac> ok(LL x) {
  const LL Inf=5e9;
  pair<Frac,Frac> inv={Frac(100,1),Frac(1,1)};
  Frac l(1LL,2LL),r(Inf,1LL);
  REP(i,N-1) {
    LL a=A[i]*x-A[i+1]*x,b=B[i+1]-B[i];
    if(b==0) {
      if(a<=0) continue;
      if(a>0) return inv;
    } else if(b>0) {
      if(a<=0) continue;
      Frac lb(a,b);
      if(lb>=l) l=lb;
    } else if(b<0) {
      dump(i,a,b);
      if(a>=0) return inv;
      Frac rb(-a,-b);
      if(rb<=r) r=rb;
    }
  }
  dump(x);
//  l.debug(),r.debug();
  return {l,r};
}
bool valid(pair<Frac,Frac> x) {
  Frac a=x.first,b=x.second;
  LL l=(a.n)/a.d,r=(b.n+b.d-1)/b.d;
  return r-l>=2;
}
void solve_wrong() {
  LL good=Inf, bad=0;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    pair<Frac,Frac> res=ok(m);
    (valid(res)?good:bad)=m;
  }
  pair<Frac,Frac> x=ok(good);
  if(valid(x)) {
    Frac a=x.first;
    LL l=a.n/a.d+1;
    cout<<good<<" "<<l<<endl;
  } else {
    cout<<"IMPOSSIBLE"<<endl;
  }
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=4;//genRandNum(2,10);
  VI as=genRandSeq(N,1,10),bs=genRandSeq(N,1,10);
  REP(i,N) A[i]=as[i],B[i]=bs[i];
  
  string a=solve_small2(),b=solve();
  if(a!=b) {
    dump(a,b);
    dumpc(as);
    dumpc(bs);
  }
  assert(a==b);
}

int main(int argc, char* argv[]) {
//  while(true) test();
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>A[i]>>B[i];
    cout<<"Case #"<<t<<": ";
    cout<<solve()<<endl;
  }
  return 0;
}
