#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<

const int INF = (int) 1e9;

struct node;

struct edge {

  int src_loc, quality;
  string s;
      
  node* dest;

  edge() {
    quality = 0;
    dest = NULL;
  }

  edge(int _sl, int _qual, string _s) {
    src_loc = _sl;
    quality = _qual;
    s = _s;
  }

};

struct node {

  int loc, score;
  string kmer;
  vector <edge*> edges;

  void trace_dfs() {
    cerr << "Backbone_id; " << loc << ", node_str: " << kmer << endl;
    for (auto e : edges) {
      assert(e != NULL);
      cerr << "edge from id: " << e->src_loc << " with edge_str: " << e->s 
           << " and quality: " << e->quality << endl;
      if (e->dest != NULL)
        e->dest->trace_dfs();
    }
  }

  node () {
    score = -1;
  }

};

int k = 2, g = 3;
int skipped = 0;

string backbone, read, read_quality;

node *kmer_graph;

map <pair<int, string>, node*> V;
map <pair<int, string>, edge*> E;

map <node*, pair<node*, edge*>> dad;

void build_backbone(node *root) {
  int it = 0;
  while (it + k <= (int) backbone.size()) {

    root->loc = it;
    root->kmer = backbone.substr(it, k);

    V[make_pair(root->loc, root->kmer)] = root;

    it += k;
    if (it + g > (int) backbone.size())
      break;

    string edge_str = backbone.substr(it, g);
    edge* e = new edge(root->loc, 1, edge_str);

    it += g - k;

    e->dest = new node(); 
    e->quality = 1;
    root->edges.push_back(e);
    E[make_pair(root->loc, edge_str)] = e;

    root = e->dest;
  }
}

void add_path(int offset) {

  int read_offset = 0;
  while (offset % g != 0) {
    ++offset;
    ++read_offset;
  }

  node *curr;
  string kmer = read.substr(read_offset, k);

  if (V.find(make_pair(offset, kmer)) == V.end()) {
    curr = new node();
    curr->loc = offset;
    curr->kmer = kmer;
    V[make_pair(offset, kmer)] = curr;
  } else {
    curr = V[make_pair(offset, kmer)];
  }

//  cerr << "Building path with offset = " << offset << endl;

  int it = k + read_offset;
  while (it + g <= read.size()) {

    string edge_str = read.substr(it, g);
    string next_kmer = edge_str.substr(g - k, k);
    
    int edge_quality = 0;
    for (int i = 0; i < g; ++i)
      edge_quality += (int) read_quality[it + i];

    node* nxt = NULL;      
    edge* link = NULL;

    if (V.find(make_pair(curr->loc + g, next_kmer)) != V.end()) 
      nxt = V[make_pair(curr->loc + g, next_kmer)];

    if (nxt == NULL) {
      nxt = new node();
      nxt->loc = curr->loc + g;
      nxt->kmer = next_kmer;
      V[make_pair(nxt->loc, nxt->kmer)] = nxt;
    }

    for (auto e : curr->edges)
      if (e->s == edge_str)
        link = e;

//    if (link != NULL) {
//      TRACE(link->s _ nxt->kmer _ link->dest->kmer _ link->dest _ nxt _ link->dest->loc _ nxt->loc);
//      assert(link->dest == nxt);
//    }

    if (link == NULL) {
      link = new edge(curr->loc, 0, edge_str);
      link->dest = nxt;
      curr->edges.push_back(link);
    }
      
    link->quality += 5; //edge_quality;

    curr = nxt;
    it += g;
      
  }

//  cerr << "Path with offset: " << offset << " built successfully!" << endl;

}

string reconstruct_genome(node *root) {

  string ret;

  node *leaf = new node();

  queue <node*> Q;
  Q.push(root);
  root->score = 0;
  
  while (!Q.empty()) {

    node *curr = Q.front();
    Q.pop();
    
    if (curr->score > leaf->score) 
      leaf = curr;

    for (auto e : curr->edges) {
      if (e->dest->score == -1)
        Q.push(e->dest);
      if (e->dest->score < curr->score + e->quality) {
        e->dest->score = curr->score + e->quality;
        dad[e->dest] = make_pair(curr, e);
      }
    }

  }

//  cerr << "Found path with quality = " << leaf->score << endl;

  stack <string> S;
  while (dad.find(leaf) != dad.end()) {
    auto p = dad[leaf];
    S.push(p.second->s);
    assert(p.first->loc < leaf->loc);
    leaf = p.first;
  }
  
  ret += leaf->kmer;
  while (!S.empty()) {
    ret += S.top();
    S.pop();
  }

  return ret;

}

int main(void) {

  ios_base::sync_with_stdio(false);
  kmer_graph = new node();

  cin >> backbone;
  build_backbone(kmer_graph);
  
  TRACE(V.size());

//  cerr << "Backbone built successfully!" << endl;  

  int cnt = 0;
  while (cin >> read) {
    int offset;
    cin >> read_quality;
    cin >> offset; 
    --offset;
    add_path(offset); 
    ++cnt;
//    for (int i = 0; i < read.size(); ++i)
//      cerr << read[i] << " " << backbone[i + offset] << endl;
  }

  TRACE(V.size());
  TRACE(cnt);
  cout << ">final" << endl;
  
  string ret = reconstruct_genome(kmer_graph);
  for (int i = 0; i < ret.size(); ++i)
    if (ret[i] != '-')
      cout << ret[i];

  cout << endl;

  return 0;

}
