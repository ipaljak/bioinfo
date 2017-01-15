#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<

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

  int loc;
  string kmer;
  vector <edge*> edges;

  void trace_dfs() {
    cout << "Backbone_id; " << loc << ", node_str: " << kmer << endl;
    for (auto e : edges) {
      assert(e != NULL);
      cout << "edge from id: " << e->src_loc << " with edge_str: " << e->s 
           << " and quality: " << e->quality << endl;
      e->dest->trace_dfs();
    }
  }

};

int k = 2, g = 3;

string backbone, read, read_quality;

node *kmer_graph;

map <pair<int, string>, node*> V;
map <pair<int, string>, edge*> E;

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
    root->edges.push_back(e);
    E[make_pair(root->loc, edge_str)] = e;

    root = e->dest;
  }
}

void add_path(int offset) {

  string kmer = read.substr(0, k);

  assert(V.find(make_pair(offset, kmer)) != V.end());
  assert(offset + read.size() <= backbone.size());

  node *curr = V[make_pair(offset, kmer)];

  int it = k;
  while (it + g <= read.size()) {

    TRACE(it);

    string edge_str = read.substr(it, g);
    string next_kmer = edge_str.substr(g - k, k);

    node* nxt = NULL;      
    edge* link = NULL;

    if (V.find(make_pair(it + g - k, next_kmer)) != V.end()) 
      nxt = V[make_pair(it + g - k, next_kmer)];

    if (nxt == NULL) {
      nxt = new node();
      nxt->loc = curr->loc + g;
      nxt->kmer = next_kmer;
      V[make_pair(nxt->loc, nxt->kmer)] = nxt;
    }

    for (auto e : curr->edges)
      if (e->s == edge_str)
        link = e;

    if (link == NULL) {
      link = new edge(curr->loc, 0, edge_str);
      link->dest = nxt;
      curr->edges.push_back(link);
    }
      
    link->quality++;

    curr = nxt;
    it += g;
      
  }

}

int main(void) {

  ios_base::sync_with_stdio(false);
  kmer_graph = new node();

  cin >> backbone;
  build_backbone(kmer_graph);

  int read_cnt;
  cin >> read_cnt;

  while (read_cnt --> 0) {
    int offset;
    cin >> read;
    cin >> read_quality;
    cin >> offset; 
    add_path(offset); 
  }

  kmer_graph->trace_dfs();

  return 0;

}
