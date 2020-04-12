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
#define dumpc(ar) { FORR(x,(ar)) { cerr << x << ' '; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch SquareDance | diff SquareDance.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SquareDance.cpp && ./a.out

/*
 
 4/10/2020
 
 19:36-20:08 visible AC
 
 4/11/2020
 
 14:50-16:33 read editorials and got AC
 
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.e5md8xipyhfy
 https://twitter.com/hanseilimak/status/1249460887670280192
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b1355
 https://en.wikipedia.org/wiki/Dancing_Links
 
 */

VV<int> A;
int R,C;

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
bool calc(int i, int j, VV<int> &A) {
  assert(A[i][j]!=-1);
  VI xs;
  for(auto m : moves) {
    int ii=i+m.first,jj=j+m.second;
    while(!(ii<0||ii>=R||jj<0||jj>=C)) {
      if(A[ii][jj]!=-1) {
        xs.push_back(A[ii][jj]);
        break;
      }
      ii+=m.first,jj+=m.second;
    }
  }
  if(xs.empty()) return false;
  LL a=A[i][j];
  dump(i,j,a,a*SZ(xs),accumulate(ALL(xs),0LL));
  dumpc(xs);
  return a*SZ(xs)<accumulate(ALL(xs),0LL);
}

LL solve_small() {
  LL res=0;
  while(true) {
    REP(i,R)REP(j,C)if(A[i][j]!=-1) res+=A[i][j];
    dump(res);
    VV<int> AA=A;
    bool died=false;
    REP(i,R)REP(j,C) if(A[i][j]!=-1) {
      bool res=calc(i,j,A);
      dump(i,j,res);
      died|=res;
      AA[i][j]=res?-1:A[i][j];
      if(!res) res+=A[i][j];
    }
    if(!died) break;
    swap(A,AA);
    REP(i,R) dumpc(A[i]);
  }
  return res;
}

LL solve() {
  LL res=0,sum=0;
  REP(i,R)REP(j,C) sum+=A[i][j];
  vector<list<int>> rlist(R),clist(C);
  map<int,list<int>::iterator> rlink,clink;
  set<int> Q;
  REP(i,R)REP(j,C) rlist[i].push_back(j);
  REP(j,C)REP(i,R) clist[j].push_back(i);
  REP(i,R) {
    auto it=rlist[i].begin();
    REP(j,C) rlink[i*C+j]=it++;
  }
  REP(j,C) {
    auto it=clist[j].begin();
    REP(i,R) clink[i*C+j]=it++;
  }
  REP(i,R)REP(j,C) Q.emplace(i*C+j);
  
  while(SZ(Q)) {
    set<int> QQ;
    res+=sum;
    VI del;
    FORR(p,Q) {
      int i=p/C,j=p%C;
      list<int>::iterator it1=rlink[p],it2=clink[p];
      VI neighs;
      auto it=it1;
      if(it!=rlist[i].begin()) {
        --it;
        neighs.push_back(i*C+(*it));
      }
      it=it1,++it;
      if(it!=rlist[i].end()) {
        neighs.push_back(i*C+(*it));
      }
      it=it2;
      if(it2!=clist[j].begin()) {
        --it;
        neighs.push_back((*it)*C+j);
      }
      it=it2,++it;
      if(it!=clist[j].end()) {
        neighs.push_back((*it)*C+j);
      }
      LL sumsum=0; FORR(p,neighs)sumsum+=A[p/C][p%C];
      
      dump(i,j,A[i][j],SZ(neighs),sumsum,A[i][j]*SZ(neighs)<sumsum);
      if(A[i][j]*SZ(neighs)<sumsum) {
        sum-=A[i][j];
        FORR(p,neighs)QQ.emplace(p);
        del.push_back(i*C+j);
      }
    }
    FORR(p,del) {
      int i=p/C,j=p%C;
      auto it1=rlink[p],it2=clink[p];
      rlist[i].erase(it1),clist[j].erase(it2);
      if(QQ.count(p)) QQ.erase(p);
    }
    dump(sum,res);
    swap(Q,QQ);
  }
  return res;
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
  R=genRandNum(1,10),C=genRandNum(1,10);
  A=VV<int>(R,VI(C));
  REP(i,R) A[i]=genRandSeq(C,1,10);
  println("%d %d",R,C);
  REP(i,R) dumpc(A[i]);
  LL exp=solve(),act=solve_small();
  dump(exp,act);
  assert(exp==act);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>R>>C;
    A=VV<int>(R,VI(C));
    REP(i,R)REP(j,C) cin>>A[i][j];
    
    cout<<"Case #"<<t<<": ";
    cout<<solve()<<endl;
  }
  return 0;
}
