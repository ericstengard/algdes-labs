#include <iostream>
#include <fstream>
#include <sstream>
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
    Person();
		Person(string pname, std::vector<int> pref, int pid);
		string getName() const;
		void setName( string name );
		void setPref( std::vector<int> pref );
    void setId( int id );
    int getId() const;
		std::vector<int> getPref() const;
    void addPref(int n);
		void print() const;
    bool compare(int current, int candidate);
    int nextId();

	private:
    int id;
		string name;
		std::vector<int> pref; //If 0 is unknown.
    int at;
};
Person::Person(){
  id=0;
}
Person::Person (string pname, std::vector<int> ppref, int pid){
	name = pname;
	pref = ppref;
  id = pid;
  at = 0;
}
void Person::setId( int id ){
  this->id = id;
}
int Person::getId() const{
  return this->id;
}
string Person::getName() const{
	return name;
}
std::vector<int> Person::getPref() const{
	return pref;
}
void Person::print() const{
	cout << name << ' ';
  for (auto pre : pref)
    std::cout << pre << ' ';
  std::cout << '\n';
}
void Person::setName( string name ){
	this->name = name;
}
void Person::setPref( std::vector<int> pref ){
  this->pref = pref;
}
void Person::addPref( int n ){
  pref.push_back(n);
}
bool Person::compare(int current, int candidate){
  for ( auto number : pref ){
    if ( number == current ){
      return false;
    } else if ( number == candidate ){
      return true;
    }
  }
  // std::cout << "You seem to have a number not specified in the prefs!" << '\n';
  return false;
}
int Person::nextId(){
  int ret = pref.at(at);
  at = at + 1;
  return ret;
}

class Couple
{
  public:
    Couple( Person pfemale );
    Couple( Person pmale, Person pfemale );
    void setMale( Person pmale );
    int getFid() const;
    void print();
    Person tryMate( Person pmale );

  private:
    Person male;
    Person female;
};

Couple::Couple(Person pfemale){
  female = pfemale;
}
Couple::Couple(Person pmale, Person pfemale){
  male = pmale;
  female = pfemale;
}
void Couple::setMale( Person pmale ){
  male = pmale;
}
void Couple::print(){
  std::cout << male.getName() << " -- " << female.getName()<< '\n';
}
Person Couple::tryMate( Person pmale ){
  if ( male.getId() != 0 ){
    if ( female.compare( male.getId(), pmale.getId() ) ){
      Person prev = male;
      male = pmale;
      return prev;
    }
    else {
      return pmale;
    }
  }
  Person prev = male;
  male = pmale;
  return prev;
}
int Couple::getFid() const{
  return female.getId();
}



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
  std::vector<Person> humansF;
  std::vector<Person> humansM;
  std::vector<Couple> couples;
  ifstream myfile ("../data/sm-friends-in.txt");
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
          int number;
          std::vector<int> prefs;
          std::stringstream iss( line );
          while ( iss >> number )
            prefs.push_back( number );
          try {
            Person p = Person( males.at(index-1), prefs, id-1 );
            humansM.push_back( p );
          } catch (const std::exception& e) {

          }
          prefM.push_back(line);
          id = 1 + id;
        }
        else if (odd && at >= n*2+1)
        {
          line.replace(0,2,"");
          int number;
          std::vector<int> prefs;
          std::stringstream iss( line );
          while ( iss >> number )
            prefs.push_back( number );
          try {
            Person p = Person( females.at(index), prefs, id-1 );
            humansF.push_back(p);
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

  humansF.erase(humansF.begin());

  // for (std::vector<string>::const_iterator i = males.begin(); i != males.end(); ++i)
  //   std::cout << *i << endl;
  //
  // for (std::vector<string>::const_iterator i = females.begin(); i != females.end(); ++i)
  //   std::cout << *i << endl;
  //
  // for (std::vector<string>::const_iterator i = prefM.begin(); i != prefM.end(); ++i)
  //   std::cout << *i << endl;
  //
  // for (std::vector<string>::const_iterator i = prefF.begin(); i != prefF.end(); ++i)
  //   std::cout << *i << endl;
  //
  // for ( auto human : humansM ){
  //   human.print();
  // }
  for ( auto female : humansF ){
    Couple c = Couple(female);
    couples.push_back(c);
  }
  // for ( auto couple : couples ){
  //   couple.print();
  // }

  while (humansM.size() > 0){
    Person focus = humansM.back();
    humansM.pop_back();
    int temp = 0;
    int target = focus.nextId();
    while (couples.at(temp).getFid() != target){
      temp = 1 + temp;
    }
    Person back = couples.at(temp).tryMate(focus);
    if (back.getId() != 0){
      humansM.push_back(back);
    }
    // for ( auto couple : couples ){
    //   couple.print();
    //   if ( couple.getFid() == target ){
    //     Person back = couple.tryMate(focus);
    //     if (back.getId() != 0){
    //       humansM.push_back(back);
    //     }
    //     break;
    //   }
    // }

  }
  for ( auto couple : couples ){
    couple.print();
  }

  return 0;
}
