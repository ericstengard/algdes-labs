#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

class Person
{
	public:
    Person(string pname, int pid);
		Person(string pname, std::vector<int> pref);
		string getName() const;
		void setName( string name );
		void setPref( std::vector<int> pref );
    void setId( int id );
		std::vector<int> getPref() const;
    void addPref(int n);
		void print() const;

	private:
    int id;
		string name;
		std::vector<int> pref; //If 0 is unknown.
};

Person::Person(string pname, int pid)
{
  name = pname;
  id = pid;
}

Person::Person (string pname, std::vector<int> ppref)
{
	name = pname;
	pref = ppref;
}

void Person::setId( int id )
{
  this->id = id;
}

string Person::getName() const
{
	return name;
}

std::vector<int> Person::getPref() const
{
	return pref;
}

void Person::print() const
{
	cout << name << endl;
}

void Person::setName( string name )
{
	this->name = name;
}

void Person::setPref( std::vector<int> pref )
{
  this->pref = pref;
}

void Person::addPref( int n )
{
  pref.push_back(n);
}

// class Couple
// {
//   public:
//     Couple();
//     Couple( Person male, Person female );
//
// }

int main () {
  string line;
  int n;
  int at = 0;
  int index = 0;
  int id = 1;
  bool first = true; //This is for n
  bool odd = true;
  std::vector<string> males;
  std::vector<string> females;
  std::vector<string> prefM;
  std::vector<string> prefF;
  std::vector<Person> humans;
  ifstream myfile ("../data/sm-bbt-in.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      if ( line.find("#") == std::string::npos )
      {
        if (first)
        {
          first = !first;
          line.replace(0,2,"");
          n = atoi(line.c_str());
        }
        odd = !odd;
        if (odd && at <= n*2)
        {
          line.replace(0,2,"");
          males.push_back(line);
        }
        else if (!odd && at <= n*2)
        {
          line.replace(0,2,"");
          females.push_back(line);
        }
        if (!odd && at >= n*2+1)
        {
          line.replace(0,2,"");
          try {
            Person p = Person( males.at(index-1), id );
            humans.push_back( p );
          } catch (const std::exception& e) {

          }
          prefM.push_back(line);
          id = 1 + id;
        }
        else if (odd && at >= n*2+1)
        {
          line.replace(0,2,"");
          try {
            Person p = Person( females.at(index), id );
            humans.push_back(p);
          } catch (const std::exception& e) {

          }
          prefF.push_back(line);
          index = 1 + index;
          id = id + 1;
        }
        at = at + 1;
      }
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  // while (males.size() > 0)
  // {
  //
  // }

  for (std::vector<string>::const_iterator i = males.begin(); i != males.end(); ++i)
    std::cout << *i << endl;

  for (std::vector<string>::const_iterator i = females.begin(); i != females.end(); ++i)
    std::cout << *i << endl;

  for (std::vector<string>::const_iterator i = prefM.begin(); i != prefM.end(); ++i)
    std::cout << *i << endl;

  for (std::vector<string>::const_iterator i = prefF.begin(); i != prefF.end(); ++i)
    std::cout << *i << endl;

  for ( auto human : humans )
  {
    human.print();
  }


  return 0;
}
