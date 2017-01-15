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

//struct Read {
  //string name;
  //string read;
  //string direction;
  //string quality;
//};

string read_backbone(string backbone_file){

  ifstream in(backbone_file.c_str(), ios::in);

  string name;
  string backbone;

  getline(in, name);
  getline(in, backbone);

  return backbone;
}

struct Sam {
  int id;
  // 0 OK, else IGNORE
  int flag;
  // position in the backbone (layout)
  int pos;
  // quality of mapping -> seems irrelevant
  int mq;
  // insertions/deletions/etc to get the mapping
  string cigar;
  // actual ACTGCAGT 
  string read;
  // fastq quality of the read
  string quality;
};

Sam read_mapping(ifstream &in){
  Sam sam;


  string str;

  in >> sam.id >> sam.flag;
  in >> str >> sam.pos >> sam.mq >> 
    sam.cigar >> str >> str >> str >> sam.read >> sam.quality
    >> str >> str >> str >> str >> str >> str >> str;
  if (sam.flag == 4)
    return sam;

  in >> str;

  return sam;
}

int main(int argc, char ** argv){

  // open files for reading
  string backbone_file = "../data/lambda_layout.fasta";
  string mappings_file = "../data/lambda_overlaps.sam";
  string output_file   = "../data/nas.format";

  ofstream out(output_file.c_str(), ios::out);
  ifstream in(mappings_file.c_str(), ios::in);

  // the backbone
  string backbone = read_backbone(backbone_file);
  
  out << backbone << endl;

  string str;
  // ignoring first 3 lines of input
  getline(in, str);
  getline(in, str);
  getline(in, str);

  int i;
  Sam sam;
  for (i = 1; ; ++i){
    if (!in)
      break;

    sam = read_mapping(in);
    // TODO: maybe skip just when == 4
    if (sam.flag != 0)
      continue;

    if (sam.read == "")
      continue;
    out << sam.read << endl;
    out << sam.quality << endl;
    out << sam.pos << endl;


  }

  return 0;

}
