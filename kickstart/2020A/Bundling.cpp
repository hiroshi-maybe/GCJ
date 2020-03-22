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

int N,K;
int res=0;

class TrieNode {
public:
  const char C_SIZE=26;
  const char BASE='A';
  int cnt=0; // # of strs in subtree
  set<int> ids; // str ending here
  vector<TrieNode*> cs;
  TrieNode() { this->cs=vector<TrieNode*>(C_SIZE,nullptr); }
  void release() { for(auto c : cs) if(c!=nullptr) c->release(), delete c; }
  void insert(int id, string &s, int p=0) {
    ++cnt;
    if(p==s.size()) {
      ids.emplace(id);
      return;
    }
    int i=index(s[p]);
    auto x=cs[i];
    if(x==nullptr) x=new TrieNode(),cs[i]=x;
    x->insert(id,s,p+1);
  }
  int dfs(int d) {
    int used=0;
    for(auto c : cs)if(c!=nullptr) used+=c->dfs(d+1);
    int cur=this->cnt-used;
    res+=(cur/K)*d;
    int used2=cur-(cur%K);
//    dump(d,cur,cur/K,used2);

    return used2+used;
  }
  // true: erase success, false: failure, id:-1=>wildcard
  bool erase(int id, string &s, int p=0) {
    if(p==s.size()) {
      bool res=false;
      if(ids.count(id)) ids.erase(id),res=true;
      else if(id==-1) { // wildcard
        if(ids.size()) res=true,ids.erase(ids.begin());
        return res;
      }
      return res;
    }
    int i=index(s[p]);
    auto x=cs[i];
    if(x==nullptr) return false;
    bool res=x->erase(id,s,p+1);
    if(res) --cnt;
    return res;
  }
  TrieNode* find(string &s, int p=0) {
    if(p==s.size()) return this;
    int i=index(s[p]);
    if(cs[i]==nullptr) return nullptr;
    return cs[i]->find(s,p+1);
  }
  // success: id, failure: -1
  int search(string s) {
    TrieNode* n=find(s);
    return (n!=nullptr&&n->ids.size())?*(n->ids.begin()):-1;
  }
  // # of strs with prefix `p`
  int prefix(string p) {
    TrieNode* n=find(p);
    return n!=nullptr?n->cnt:0;
  }
private:
  int index(char c) {
    int i=c-BASE;
    assert(0<=i&&i<C_SIZE);
    return i;
  }
};
// $ cp-batch Bundling | diff Bundling.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Bundling.cpp && ./a.out

/*
 
 3/21/2020
 
 21:45-22:22 AC
 
 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3
 
 */

const int MAX_N=1e5+1;
string S[MAX_N];

void solve() {
  res=0;
  TrieNode* trie=new TrieNode();
  REP(i,N) {
//    dump(i,S[i]);
    trie->insert(i,S[i]);
  }
  trie->dfs(0);
  trie->release();
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>K;
    REP(i,N) cin>>S[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
