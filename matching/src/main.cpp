#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// int main()
// {
//     cout << "Hello, World!";
//     return 0;
// }

// int main () {
//   ofstream myfile;
//   myfile.open ("example.txt");
//   myfile << "Writing this to a file.\n";
//   myfile.close();
//   return 0;
// }

// reading a text file

int main () {
  string line;
  
  ifstream myfile ("../data/sm-bbt-in.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      if (line.find("#") == std::string::npos)
      {
        cout << line << endl;
      }
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}
