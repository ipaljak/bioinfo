/*
 * Our preprocessing.
 * read in backbone, reads and mhap file and
 * output our format file
*/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

struct Read {
  string name;
  string read;
  string direction;
  string quality;
};

Read read_one_read(ifstream & in){
  Read r;
  // one Read data is written in 4 lines
  string name, read, direction, quality;
  getline(in, r.name);
  getline(in, r.read);
  getline(in, r.direction);
  getline(in, r.quality);

  return r;
}

string read_backbone(string backbone_file){

  ifstream in(backbone_file.c_str(), ios::in);

  string name;
  string backbone;

  getline(in, name);
  getline(in, backbone);

  return backbone;
}

struct Mhap {
  int id;
  // id_backbone -> irrelevant
  int idb;
  // the fraction of bases covered by seeds
  // TODO: skuzi jel error ili 1/error
  float error;
  // seeds which survived filtering
  int seeds;
  int a_direction;
  int a_start;
  int a_end;
  int a_length;
  int b_direction;
  int b_start;
  int b_end;
  int b_length;
};

map<int, Mhap> read_overlaps(string overlaps_file){

  FILE * in = fopen(overlaps_file.c_str(), "r");

  map<int, Mhap> ret_map;
  // struct
  Mhap m;

  while(fscanf(in, "%d %d %f %d %d %d %d %d %d %d %d %d",
        &(m.id), &(m.idb), &(m.error), &(m.seeds),
        &(m.a_direction), &(m.a_start), &(m.a_end), &(m.a_length),
        &(m.b_direction), &(m.b_start), &(m.b_end), &(m.b_length)) != EOF){

    ret_map[m.id] = m;
  }

  return ret_map;
}

int main(int argc, char ** argv){

  // open files for reading
  string backbone_file = "../data/lambda_layout.fasta";
  string overlaps_file = "../data/lambda_overlaps.mhap";
  ifstream in("../data/lambda_reads.fastq", ios::in);
  

  // the backbone
  string backbone = read_backbone(backbone_file);
  
  ofstream out("../data/nas.format", ios::out);

  out << backbone << endl;

  // get overlaps into some structure
  map<int, Mhap> m = read_overlaps(overlaps_file);

  out << m.size() << endl;

  //map<int, Mhap>::iterator it = m.find(7);
  //cout << (it->second).error << endl;;


  // struct that represents one read
  Read read;
  int id;
  map<int, Mhap>::iterator it;
  
  for (int i = 0;; ++i){
    // end of file // it's here cuz i can't cpp
    if (!in)
      break;

    read = read_one_read(in);

    if (read.name == "") continue;

    id = atoi(read.name.substr(1, read.name.length() - 1).c_str());
    it = m.find(id);

    string str = read.read;
    reverse(str.begin(), str.end());


  }

  return 0;

}
