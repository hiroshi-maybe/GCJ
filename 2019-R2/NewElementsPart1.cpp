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

// $ cp-batch NewElementsPart1 | diff NewElementsPart1.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NewElementsPart1.cpp && ./a.out

/*
 
 5/18/2019
 
 7:01-8:11 give up
 
 I tried to reduce to dp. However no luck.

 5/22/2019
 
 16:00-17:10 Read editorials and small test set passed
 21:00-23:40 read editorials and hidden test set passed
 
 http://kyopro.hateblo.jp/entry/2019/05/20/101835
 http://kmjp.hatenablog.jp/entry/2019/05/20/0900
 https://scrapbox.io/snuke/GCJ_2019_R2
 http://phyllo-algo.hatenablog.com/entry/2019/05/19/133047
 https://twitter.com/kuuso1/status/1129787825744957442
 https://twitter.com/a3VtYQo/status/1129790270688468992
 https://twitter.com/tempura_cpp/status/1129791739252752385
 https://twitter.com/a3VtYQo/status/1129790270688468992
 https://twitter.com/satanic0258/status/1129787423129387008
 https://twitter.com/satanic0258/status/1129790596409749504
 https://twitter.com/n_vip/status/1129787028193857536
 
 For (a,b) and (c,d), weight(a,b)<weight(c,d) or weight(a,b)>weight(c,d) determines upper-bound or lower-bound of ratio `k`=y/x
 
 Suppose we get K={k_0,..,k_l} from all the pairs of (A[i],B[i]).
 If k<k_i or k_i<k is fixed, relative order of pairs of (A[i],B[i]) which forms k_i is determined.
 For example...
  1<k for (1,4),(4,1),(2,3) => w(1,4)<w(2,3)<w(4,1) holds
  k<1 for (1,4),(4,1),(2,3) => w(4,1)<w(2,3)<w(1,4) holds
 
 Thus we can always determine order for below relation
 0<k<k_0<k_1<..<k_l<∞
   ^
 0<k_0<k<k_1<..<k_l<∞
       ^
 ...
 0<k_0<k_1<..<k_{l-1}<k<k_l<∞
                      ^
 0<k_0<k_1<..<k_{l-1}<k_l<k<∞
                          ^
 
 Thus res = l+1 for k∈{k_0,..,k_l}
 
 Key:
  - If ratio is determined, real value of weight of each atom doesn't matter <=> we can consider only one parameter
 
 Summary:
  - Consider to map two parameters to one parameter to simplify problem
  - Try to consider graph for inequality
 
 */

struct Frac {
public:
  // numerator / denominator
  int n,d;
  Frac(): n(0),d(1) {}
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
  Frac abs() {
    Frac res(n<0?-n:n,d);
    return res;
  }
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

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG NewElementsPart1.cpp && ./a.out < NewElementsPart1.in | diff NewElementsPart1.out -
const int MAX_N=300+1;
const int Inf=1e9+10;
int A[MAX_N],B[MAX_N];
int N;
void solve() {
  set<II> S;
  REP(i,N)REP(j,N) {
    int a=A[i],b=B[i],c=A[j],d=B[j];
    if((LL)(d-b)*(c-a)<0) {
      Frac x=Frac(d-b,a-c);
      S.emplace(x.n,x.d);
    }
  }
//  dumpc(S);
  cout<<(SZ(S)+1)<<endl;
}
void solve_small() {
  VI perm(N,0);
  REP(i,N) perm[i]=i;
  LL res=0;
  do {
    vector<II> X;
    REP(i,N) X.emplace_back(A[perm[i]],B[perm[i]]);
    Frac l(0,1),r(Inf,1);
    bool ok=true;
    REP(j,N)REP(i,j) {
      int a=X[i].first,b=X[i].second,c=X[j].first,d=X[j].second;
      if(b==d) ok&=c>a;
//      else if(c==a) ok&=b<d;
      else if(d>b) {
        Frac x(a-c,d-b);
        SMAX(l,x);
      } else {
        Frac x(a-c,d-b);
        SMIN(r,x);
      }
    }
    if(ok&&l<r) {
      ++res;
//      dumpc(X);
//      dump(l,r);
    }
  } while(next_permutation(ALL(perm)));
  cout<<res<<endl;
}
int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>A[i]>>B[i];
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
