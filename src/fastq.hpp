#include <string>
#include <vector>

class FastqRecord {
  private:
    vector<string> names;

  public:
    FastqRecord ();
    FastqRecord (string filename);

    // reads from file with given path
    // True if successfull reading, False else
    //bool read_from_file(string filename);
}

// normal constructor
FastqRecord::FastqRecord () {
  
}

// constructor with path file 
// starts loading everything rite away
FastqRecord::FastqRecord (string filename) {

  string line;
  unordered_set<string> names;

  ifstream in(filename, ios::in);
  //if (!in.is_open()) return EXIT_FAILURE;

  string name, seq, name2, qual;
  while (!in.eof()){
    if (!getline(in2, name, '\n')) break;
    if (!getline(in2, seq, '\n')) break;
    if (!getline(in2, name2, '\n')) break;
    if (!getline(in2, qual, '\n')) break;
  }
  in.close();

}

//FastqRecord::read_from_file(string filename){
  

  //return True
//}
