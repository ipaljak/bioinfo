#include <fstream>
#include <iostream>
#include <string>

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

  // TODO: return struct or smth with all the data
  return r;
}

string read_backbone(ifstream & in){

  string name;
  string backbone;

  getline(in, name);
  getline(in, backbone);

  return backbone;
}

int main(){
  // open files for reading
  ifstream in("../data/lambda_reads.fastq", ios::in);
  ifstream backbone_in("../data/lambda_layout.fasta", ios::in);
  
  Read read;

  string backbone = read_backbone();
  cout << backbone << endl;

  for (int i = 0;; ++i){
    // end of file // it's here cuz i can't cpp
    if (!in)
      break;

    read = read_one_read(in);

    // else: do something with that read
    //cout << read.name << endl;
    //cout << read.direction << endl;

  }

  return 0;

}
