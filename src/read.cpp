#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv){
  string line;
  unordered_set<string> names;

  ifstream in("../data/lambda_reads.fastq", ios::in);
  if (!in.is_open()) return EXIT_FAILURE;
  while (getline(in, line, '\n'))
    names.insert(line);
  in.close();

  string name, seq, name2, qual;
  unordered_set<string>::iterator r;
  ifstream in2("/dev/stdin", ios::in);

  //for (r = names.begin(); r != names.end(); r++)
    //cout << *r << endl;

  int i = 0;
  while(!names.empty()){
    if (!getline(in2, name, '\n')) break;
    if (!getline(in2, seq, '\n')) break;
    if (!getline(in2, name2, '\n')) break;
    if (!getline(in2, qual, '\n')) break;
    r = names.find(name);
    cout << "qwer" << endl;
    names.erase(r); // names are unique
    cout << name << "\n" << seq << "\n" << name2 << "\n" << qual << endl;
    i++;
    if (i == 5)
      break;
  }




  return 0;
}
