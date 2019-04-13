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

class TrieNode {
public:
  bool isroot=false;
  int cnt=0;
  bool hasWord = false;
  vector<TrieNode *> children;
  // Initialize your data structure here.
  TrieNode() {
    this->children = vector < TrieNode * > (26, NULL);
  }
  int dfs(string s) {
    int x=0,icnt=cnt;
    REP(i,26) if(children[i]!=nullptr) {
      char c='A'+i;
      string t=s; t.push_back(c);
      dump(s,i,c,t);
      int y=children[i]->dfs(t);
      dump(y);
      x+=y;
    }
    if(isroot) {
//      dump(s,x);
      return x;
    }
    icnt-=x;
    int res=x+min(2,(icnt/2)*2);
    dump(s,cnt,x,icnt,res);
    return res;
  }
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }
  
  // Inserts a word into the trie.
  void insert(string word) {
    TrieNode *n = root;
    n->isroot=true;
    n->cnt++;
    for(int i=0; i<word.size(); i++) {
      int w = word[i]-'A';
      TrieNode *next = n->children[w];
      if (next==NULL) {
        next = new TrieNode();
        n->children[w] = next;
      }
      n = next;
      n->cnt++;
    }
    n->hasWord = true;
  }
  
  int dfs() {
    return root->dfs("");
  }
  
  // Returns if the word is in the trie.
  bool search(string word) {
    TrieNode *n = find(word);
    
    return n!=NULL ? n->hasWord : false;
  }
  
  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {
    TrieNode *n = find(prefix);
    
    return n!=NULL;
  }
  
  TrieNode* find(string s) {
    TrieNode *n = root;
    for(int i=0; i<s.size(); i++) {
      int w = s[i]-'a';
      TrieNode *next = n->children[w];
      if (next==NULL) {
        return NULL;
      }
      n = next;
    }
    
    return n;
  }
  
  void release() {
    releaseNode(root);
  }
private:
  TrieNode* root;
  void releaseNode(TrieNode* n) {
    if (!n) return;
    for(auto &c : n->children) releaseNode(c);
    delete n;
  }
};

/*
 
 4/12/2019
 
 18:01-18:51 submit
 
 */
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG AlienRhyme.cpp && ./a.out < AlienRhyme.in | diff AlienRhyme.out -
const int MAX_N=1e3+1;
string W[MAX_N];
int N;
void solve() {
  Trie* T=new Trie();
  REP(i,N) {
    string w=W[i];
    reverse(w.begin(),w.end());
    T->insert(w);
  }
  int res=T->dfs();
  T->release();
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    N; cin>>N;
    REP(i,N) cin>>W[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
