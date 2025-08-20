const int alphabet = 26;
const int mod = 998244353;
 
int sum( int a, int b ){
  return (a + b)%mod;
}
 
class AhoCorasick{
private:
  struct Node{
    int suffix_link, output, pai, pai_ch, mask;
    vector<int> go, adj;
    Node( int pai = 0, int pai_ch = 0 ) : pai(pai), pai_ch(pai_ch), suffix_link(-1), output(-1), mask(-1) {
      go = adj = vector<int>(alphabet, -1);
    }
  };
 
  vector<Node> t;
 
  int create( int pai, int pai_ch ){
    t.emplace_back( pai, pai_ch );
    return (int)t.size() - 1;
  }
 
  int get_adj( int node, int c ){
    if( t[node].adj[c] == -1 ){ int aux = create( node, c ); t[node].adj[c] = aux; }
    return t[node].adj[c];
  }
 
public:
 
  AhoCorasick(){ create(0, 0); }
 
  void add_string( string &s, int id ){
    int node = 0;
    for( char c : s ) node = get_adj( node, c - 'a');
    t[node].output = id;
  }
 
  int suffix_link( int node ){
    if( t[node].suffix_link != -1 ) return t[node].suffix_link;
    if( node == 0 || t[node].pai == 0 ) return t[node].suffix_link = 0;
    return t[node].suffix_link = go( suffix_link(t[node].pai), t[node].pai_ch );
  }
 
  int go( int node, int c ){
    if( t[node].go[c] != -1 ) return t[node].go[c];
    if( t[node].adj[c] != -1 ) return t[node].go[c] = t[node].adj[c];
    return t[node].go[c] = (( node == 0 ) ? 0 : go( suffix_link(node), c ) );
  }
 
  int mask( int node ){
    if( t[node].mask != -1 ) return t[node].mask;
    if( node == 0 ) return 0;
    return t[node].mask = (mask(suffix_link(node))|(( t[node].output == -1 ) ? 0 : (1<<t[node].output)));
  }
 
  int size(){
    return (int)t.size();
  }
};
