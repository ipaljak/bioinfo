#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define _ << " " <<

struct edge;

struct node {

  int loc, quality;
  string kmer;
  vector <pair<string, node*>> edges;

  void trace_dfs() {
    cout << "Backbone_id; " << loc << ", quality: " << quality << ", node_str: " << kmer << endl;
    for (auto &e : edges) {
      cout << "edge from id: " << loc << " with edge_str: " << e.first << endl;
      e.second->trace_dfs();
    }
  }

  node () {
    quality = 0;
  }

};

int k = 2, g = 3;

string backbone, read, read_quality;

node *kmer_graph;

map <pair<int, string>, node*> V;
map <pair<int, string>, node*> E;

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
    it += g - k;

    node *nxt = new node();
    root->edges.emplace_back(edge_str, nxt);
    E[make_pair(root->loc, edge_str)] = nxt;

    root = nxt;
  }
}

void add_path(int offset) {

  string kmer = read.substr(0, k);

  assert(V.find(make_pair(offset, kmer)) != V.end());
  assert(offset + read.size() <= backbone.size());

  node *curr = V[make_pair(offset, kmer)];

  int it = k;
  while (it < read.size()) {
    
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
