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
  TrieNode* find(string &s, int p=0) {
    if(p==s.size()) return this;
    int i=index(s[p]);
    if(cs[i]==nullptr) return nullptr;
    return cs[i]->find(s,p+1);
  }
  int search(string s) {
    TrieNode* n=find(s);
    return (n!=nullptr&&n->ids.size())?*(n->ids.begin()):-1;
  }
  int prefix(string p) {
    TrieNode* n=find(p);
    return n!=nullptr?n->cnt:0;
  }
  
  int dfs() {
    int x=0,icnt=cnt;
    FORR(c,cs) if(c!=nullptr) x+=c->dfs();
    icnt-=x;
    int res=x+min(2,(icnt/2)*2);
    //    dump(x,icnt,res);
    return res;
  }
private:
  int index(char c) { return c-BASE; }
};

/*
 
 4/12/2019
 
 18:01-18:51 passed small & large test set
 
 https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e05
 http://kmjp.hatenablog.jp/entry/2019/04/15/1030
 http://drken1215.hatenablog.com/entry/2019/04/14/165100
 https://tatyam.hatenablog.com/entry/2019/04/13/131813
 
 */
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG AlienRhyme.cpp && ./a.out < AlienRhyme.in | diff AlienRhyme.out -
const int MAX_N=1e3+1;
string W[MAX_N];
int N;
void solve() {
  TrieNode* trie=new TrieNode();
  REP(i,N) {
    string w=W[i];
    reverse(w.begin(),w.end());
    trie->insert(i,w);
  }
  int res=0;
  FORR(c,trie->cs) if(c!=nullptr) res+=c->dfs();
  trie->release(), delete trie;
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>W[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
