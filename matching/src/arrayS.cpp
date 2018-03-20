#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main (int argc, char* argv[]) {
  bool first = true;
  int n;
  bool odd = true;
  int at = 1;

  ifstream myfile (argv[1]);
  if (myfile.is_open()){
    while ( getline (myfile,line) ){
      if ( line.find("#") == std::string::npos ){ //Ignore comments
        if (first){
          first = !first;
          line.replace( 0, 2, "" );
          n = atoi( line.c_str() );
        }
        if ( at < n*2 ){                          //Read names
          if ( at < 10 ){                         //Remove unnessesary chars
            line.replace( 0, 2, "" );
          } else if ( at < 100 ) {
            line.replace( 0, 3, "" );
          } else {
            line.replace( 0, 4, "" );
          }
          if (odd){

          } else {

          }
        } else {                                  //read prefs

        }
      }
    }
  }
}
