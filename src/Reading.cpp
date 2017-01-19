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
//

map <int, string> insertions;

pair<string, string> cigar2align(string backbone, int backbone_pos, string cigar, string seq, string qual){

  string retstr = "";
  string retqual = "";

  backbone_pos--; // position is 1 indexed in sam

  int pos = 0;
  const char *cig = cigar.c_str();
  while(*cig != '\0'){
    char *c;
    int n = strtol(cig, &c, 10);
    
//    cerr << n << " " << *c << endl;

    switch(*c){
      case 'M':{
        while (n > 0){
          retstr += seq[pos];
          retqual += qual[pos++];
          --n;
        }
        break;
        }
      case 'D':{
        while(n > 0){
          retstr += '-';
          retqual += (char) 1;
          --n;
        }
        break;
        }
      case 'I':{
//        while (n > 0){
//          retstr += seq[pos];
//          retqual += qual[pos++];
//          --n;
//        }
        insertions[pos] = seq.substr(pos, n);
        pos += n;
        break;
        }
      case 'P':{
        // ignore
        break;
        }
      case 'S':{
        pos += n;
        break;
        }
    }
    cig = c + 1;
  }

  //cerr << pos << " " << seq.size() << endl;
  //cerr << retstr.size() << endl;

  return make_pair(retstr, retqual);
}

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

  string backbone_file = "../data/lambda_layout.fasta";
  string mappings_file = "../data/lambda_mappings.sam";
  string output_file   = "../data/lambda_nas.format";
  if (argc != 4){
    cerr << "Usage:\n\t./reading layout.fa mappings.sam output" << endl;;
  }
  else {
    backbone_file = argv[1];
    mappings_file = argv[2];
    output_file   = argv[3];
  }

  // open files for reading

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
  string aligned_read, aligned_qual;
  for (i = 1; ; ++i){
    if (!in)
      break;

    sam = read_mapping(in);
    // TODO: maybe skip just when == 4
    if (sam.flag != 0)
      continue;

    insertions.clear();
    pair<string, string> p = cigar2align(backbone, sam.pos, sam.cigar, sam.read, sam.quality);

    aligned_read = p.first;
    aligned_qual = p.second;

    if (sam.read == "")
      continue;
    out << aligned_read << endl;
    out << aligned_qual << endl;
    out << (int) insertions.size() << endl;
    for (map <int, string> :: iterator it = insertions.begin(); it != insertions.end(); ++it)
      out << it->first << " " << it->second << endl;
    out << sam.pos << endl;


  }

  return 0;

}
