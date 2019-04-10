#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
template<class T> using VV=vector<vector<T>>;
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
#define ALL(c) (c).begin(),(c).end()
#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
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

/*
 
 4/6/2019
 
 17:48-18:51 RE
 
 4/9/2019
 
 9:20-11:30 investigate reason of RE
 14:00-15:30 Figured out a bug and got AC
 16:30-17:07 Implemented hard test set with Ruby
 
 http://kmjp.hatenablog.jp/entry/2019/04/07/0930
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Cryptopangrams.cpp && ./a.out < Cryptopangrams.in | diff Cryptopangrams.out -

const int MAX_N=1001;
string S[MAX_N];

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }

vector<LL> primeFactors(LL n) {
  assert(n>=1);
//  if(n<1) return {1,1};
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) while(n%p==0) {
    res.push_back(p);
    n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}

string solve_bruteforce(string N, int L) {
  //  LL NN=stoll(N);
  vector<LL> ns(L);
  REP(i,L) ns[i]=stoll(S[i]);
  vector<LL> C;
  FORR(n,ns) {
    vector<LL> ps=primeFactors(n);
    FORR(p,ps) C.push_back(p);
  }
  UNIQUE(C);
  assert(SZ(C)==26);
  map<LL,int> M;
  REP(i,26) M[C[i]]=i;
  
  vector<LL> ps0=primeFactors(ns[0]);
  FORR(x,ps0) {
//  FORR(x,C) if(ns[0]%x==0) {
    vector<LL> X;
    X.push_back(x);
    bool ok=true;
    REP(i,L) {
      LL a=ns[i];
      if(a%X.back()!=0) {
        ok=false;
        break;
      }
      X.push_back(a/X.back());
    }
//    dumpc(X);
    if(!ok) continue;
    assert(SZ(X)==L+1);
    string ans(L+1,'?');
    REP(i,L+1) ans[i]='A'+M[X[i]];
    dump(ans);
    return ans;
  }
  assert(false);
}

string solve(string N, int L) {
  //  LL NN=stoll(N);
  vector<LL> ns(L);
  REP(i,L) ns[i]=stoll(S[i]);
  vector<LL> X(L+1);
  int k=-1;
  dumpc(ns);
  REP(i,L-1) if(ns[i]!=ns[i+1]) {
    /*
    vector<LL> ps0=primeFactors(ns[i]),ps1=primeFactors(ns[i+1]);
    dumpc(ps0);
    dumpc(ps1);
    assert(SZ(ps0)==2&&SZ(ps1)==2);
    if(ps0[0]==ps1[0]||ps0[0]==ps1[1]) X[i+1]=ps0[0];
    else if(ps0[1]==ps1[0]||ps0[1]==ps1[1]) X[i+1]=ps0[1];
    else assert(false);
     */
    LL x=gcd(ns[i],ns[i+1]);
    X[i+1]=x;
    
    k=i+1;
    for(int j=k-1; j>=0; --j) {
      assert(ns[j]%X[j+1]==0);
      X[j]=ns[j]/X[j+1];
    }
    break;
  }
  dump(k);
  
  dumpc(X);
  FOR(i,k,L) {
    LL a=ns[i];
    assert(a%X[i]==0);
    dump(i,a,X[i]);
    X[i+1]=a/X[i];
  }
  vector<LL> C=X;
  UNIQUE(C);
  //  dumpc(C);
  assert(SZ(C)==26);
//  dump(SZ(C));
  map<LL,int> M;
  REP(i,26) M[C[i]]=i;
  
  string ans(L+1,'?');
  REP(i,L+1) ans[i]='A'+M[X[i]];
  dump(ans);
  return ans;
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
vector<int> primes;
void test() {
  int L=genRandNum(25,101);
  vector<int> X(L+1,-1);
  REP(c,26) {
    while(true) {
      int i=genRandNum(0,L);
      if(X[i]==-1) {
        X[i]=c;
        break;
      }
    }
  }
  REP(i,L+1)if(X[i]==-1) X[i]=genRandNum(0,26);
  string exp(L+1,'?'); REP(i,L+1) exp[i]='A'+X[i];
  dump(exp);
  
  set<LL> ps;
  while(SZ(ps)<26) {
    int i=genRandNum(0,SZ(primes));
    ps.emplace(primes[i]);
  }
  vector<LL> Y(L+1);
  vector<LL> ps2(ps.begin(),ps.end());
  dumpc(ps2);
  REP(i,L+1) Y[i]=ps2[X[i]];
  dumpc(Y);
  REP(i,L) S[i]=to_string(Y[i]*Y[i+1]);
  dump(L);
  dumpC(S,S+L);
  
  string a=solve_bruteforce("",L),b=solve("",L);
  assert(a==b);
}

vector<int> sieve(int N) {
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(int p=2; p*p<=N; ++p) if(fs[p]) {
    for(int q=p*p; q<=N; q+=p) fs[q]=false;
  }
  vector<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.push_back(n);
  return res;
}
int main(int argc, char* argv[]) {
//  primes=sieve(10000);
//  while(true) test();

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    string N; int L; cin>>N>>L;
    REP(i,L) cin>>S[i];
    
    cout<<"Case #"<<t<<": ";
    cout<<solve(N,L)<<endl;
  }
  return 0;
}
