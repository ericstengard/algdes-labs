#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class Person
{
	public:
		Person(string pname);
    Person(string pname, std::vector<int> v);
		string getName() const;
		void setName( string name );
		void print() const;

	private:
		string name;
    std::vector<int> v;
};

Person::Person (string pname)
{
	name = pname;
}

Person::Person (string pname, std::vector<int> pref)
{
	name = pname;
  v = pref;
}

string Person::getName() const
{
	return name;
}

void Person::print() const
{
	//cout << "Name : " << name << endl;
  cout << name << endl;
}

void Person::setName( string name )
{
	this->name = name;
}


int main () {
  string line;
  std::vector <Person> males;
  std::vector <Person> females;
  bool first = true;
  int count;

  ifstream myfile ("../data/sm-bbt-in.txt");
  if (myfile.is_open())
  {
    int i = 0;
    while ( getline (myfile,line) )
    {
      if (line.find("#") == std::string::npos && (i % 2 == 0))
      {
        if(first){
          line.erase(0,2);
          count = atoi(line.c_str());
          first = false;
        }
        // Line where we're looking to add the preferences
        if(line.find(":") != std::string::npos)
        {
          cout << "Should add the prefs here!" << endl;
          std::vector<int> v;
          for(char& c : str) {
              int add = atoi(line.c_str());
              v.push_back(add);
          }

        }
        else // In the file where we're adding persons.
        {
          line.erase(0,2);
          Person female = Person(line);
          females.push_back(female);
        }
      } else if (line.find("#") == std::string::npos && !(i % 2 == 0)){
        // Line where we're looking to add the preferences
        if(line.find(":") != std::string::npos)
        {
          cout << "Should add the prefs here!" << endl;
          std::vector<int> v;
        }
        else // In the file where we're adding persons.
        {
          line.erase(0,2);
          Person male = Person(line);
          males.push_back(male);
        }
      }
      i++;
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  //for (std::vector<Person>::const_iterator i = males.begin(); i != males.end(); ++i)
    //std::cout << *i.print() << endl;

  for( auto person : males ) {
      person.print();
    }

  for(auto person : females) {
    person.print();
  }

  return 0;
}
