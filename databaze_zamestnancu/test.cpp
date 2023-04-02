
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;


struct zamestnanec
{
  string name;
  string surname;
  string email;
  unsigned int salary;
};

class CPersonalAgenda
{
public:
  CPersonalAgenda(void)
  {
  }
  ~CPersonalAgenda(void)
  {
  }
  bool add(const string &name, const string &surname, const string &email, unsigned int salary)
  {
      if (JeVDatabazi(zamestnanec_databaze_email, email) != zamestnanec_databaze_email.end() || JeVDatabazi(zamestnanec_databaze, name, surname) != zamestnanec_databaze.end())
      {
        // cout << "spatny jmeno nebo prijmeni či email" << endl;
        return false; // V databazi je již clovek se stejnym emailem nebo clovek co m stejný jmeno + prijmeni
      }
      else
      {
        zamestnanec_databaze.push_back({name, surname, email, salary});
        SeradZamestance();
        zamestnanec_databaze_email.clear();
        zamestnanec_databaze_email = zamestnanec_databaze;
        SeradPodleEmailu();

        return true; // Zamestanenc uspesne pridan
      }
  }

  bool del(const string &name, const string &surname)
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }

    auto it = JeVDatabazi(zamestnanec_databaze, name, surname);

    if (it == zamestnanec_databaze.end()) // neni tam
    {
      return false;
    }
    auto it2 = JeVDatabazi(zamestnanec_databaze_email, it->email);

    zamestnanec_databaze.erase(it);
    zamestnanec_databaze_email.erase(it2);
    return true;
  }

  bool del(const string &email)
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }

    auto it = JeVDatabazi(zamestnanec_databaze_email, email);
    if (it == zamestnanec_databaze_email.end()) // neni tam
    {
      return false;
    }
    auto it2 = JeVDatabazi(zamestnanec_databaze, it->name, it->surname);

    zamestnanec_databaze_email.erase(it);
    zamestnanec_databaze.erase(it2);
    return true;
  }

  bool changeName(const string &email, const string &newName, const string &newSurname)
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }
    auto it = JeVDatabazi(zamestnanec_databaze_email, email);
    if (it == zamestnanec_databaze_email.end())
    {
      return false;
    }
    if (JeVDatabazi(zamestnanec_databaze, newName, newSurname) != zamestnanec_databaze.end())
    {
      return false;
    }

    auto it2 = JeVDatabazi(zamestnanec_databaze, it->name, it->surname);

    it->name = newName;
    it->surname = newSurname;
    // nastaveni nového jmena do databaze
    it2->name = newName;
    it2->surname = newSurname;
    SeradZamestance();

    return true;
  }

  bool changeEmail(const string &name, const string &surname, const string &newEmail)
  {
    if (zamestnanec_databaze.empty()) // je prazdna
    {
      return false;
    }
    auto it = JeVDatabazi(zamestnanec_databaze, name, surname);
    if (it == zamestnanec_databaze.end()) // neni tam
    {
      return false;
    }

    if (JeVDatabazi(zamestnanec_databaze_email, newEmail) != zamestnanec_databaze_email.end())
    {
      return false;
    }
    auto it2 = JeVDatabazi(zamestnanec_databaze_email, it->email);

    it->email = newEmail;
    it2->email = newEmail;
    SeradPodleEmailu();

    return true;
  }

  bool setSalary(const string &name, const string &surname, unsigned int salary)
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }
    auto it = JeVDatabazi(zamestnanec_databaze, name, surname);
    if (it == zamestnanec_databaze.end())
    {
      return false;
    }
    it->salary = salary;

    auto it2 = JeVDatabazi(zamestnanec_databaze_email, it->email);
    it2->salary = salary;

    return true;
  }

  bool setSalary(const string &email, unsigned int salary)
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }
    auto it = JeVDatabazi(zamestnanec_databaze_email, email);
    if (it == zamestnanec_databaze_email.end())
    {
      return false;
    }
    it->salary = salary;
    // in email database is right salary
    auto it2 = JeVDatabazi(zamestnanec_databaze, it->name, it->surname);
    it2->salary = salary;
    // in name_surname database is right salary

    return true;
  }

  unsigned int getSalary(const string &name, const string &surname) const
  {
    if (zamestnanec_databaze.empty())
    {
      return 0; // prazdna databáze
    }
    auto it = JeVDatabaziConst(zamestnanec_databaze, name, surname);
    if (it == zamestnanec_databaze.end())
    {
      return 0; // zamestnanec tam není
    }
    return it->salary;
  }

  unsigned int getSalary(const string &email) const
  {
    if (zamestnanec_databaze_email.empty())
    {
      return 0; // prazdná databáze
    }
    auto it = JeVDatabaziConst(zamestnanec_databaze_email, email);
    if (it == zamestnanec_databaze_email.end())
    {
      return 0;
    }
    return it->salary;
  }

  bool getRank(const string &name, const string &surname, int &rankMin, int &rankMax) const
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }
    unsigned int numberOfLowestSalary = 0;
    unsigned int numberOfSameSalary = 0;
    auto it = JeVDatabaziConst(zamestnanec_databaze, name, surname);
    if (it == zamestnanec_databaze.end())
    {
      return false;
    }

    for (const auto &plat : zamestnanec_databaze)
    {
      if (plat.salary < it->salary)
      {
        numberOfLowestSalary++;
      }
      if (plat.salary == it->salary)
      {
        numberOfSameSalary++;
      }
    }
    rankMin = numberOfLowestSalary;
    rankMax = numberOfLowestSalary + numberOfSameSalary - 1;

    return true;
  }

  bool getRank(const string &email, int &rankMin, int &rankMax) const
  {

    if (zamestnanec_databaze_email.empty())
    {
      return false;
    }
    unsigned int numberOfLowestSalary = 0;
    unsigned int numberOfSameSalary = 0;
    unsigned int salary = 0;
    auto it = JeVDatabaziConst(zamestnanec_databaze_email, email);

    if (it == zamestnanec_databaze_email.end())
    {
      return false;
    }
    salary = it->salary;
    for (const auto &plat : zamestnanec_databaze)
    {
      if (plat.salary < salary)
      {
        numberOfLowestSalary++;
      }
      if (plat.salary == salary)
      {
        numberOfSameSalary++;
      }
    }

    rankMin = numberOfLowestSalary;
    rankMax = numberOfLowestSalary + numberOfSameSalary - 1;
    return true;
  }

  bool getFirst(string &outName, string &outSurname) const
  {
    if (zamestnanec_databaze.empty())
    {
      return false;
    }
    auto it = zamestnanec_databaze.front();
    outName = it.name;
    outSurname = it.surname;
    return true;
  }

  bool getNext(const string &name, const string &surname, string &outName, string &outSurname) const
  {
    if (zamestnanec_databaze.empty())
    {

      return false; // prazdna databáze
    }
    auto it = JeVDatabaziConst(zamestnanec_databaze, name, surname);

    if (it == prev(zamestnanec_databaze.end()) || it == zamestnanec_databaze.end())
    {
      return false; // posledni zamestanenc
    }
    // cout << next(it)->name << "--" << next(it)->surname << endl;
    outName = next(it)->name;
    outSurname = next(it)->surname;
    return true;
  }

private:
  vector<zamestnanec> zamestnanec_databaze;
  vector<zamestnanec> zamestnanec_databaze_email;

  void vypisLidi(const vector<zamestnanec> &zamestnanec_databaze) const
  {
    for (const auto &zamestnanec : zamestnanec_databaze)
    {
      cout << zamestnanec.name << " " << zamestnanec.surname << " " << zamestnanec.email << " " << zamestnanec.salary << endl;
    }
    cout << "----------" << endl;
  }

  void SeradZamestance()
  {
    sort(zamestnanec_databaze.begin(), zamestnanec_databaze.end(), [](const zamestnanec &a, const zamestnanec &b)
         {
            if (a.surname != b.surname) {
                return a.surname < b.surname;
            }
            return a.name < b.name; });
  }

  void SeradPodleEmailu()
  {
    sort(zamestnanec_databaze_email.begin(), zamestnanec_databaze_email.end(), [](zamestnanec &a, zamestnanec &b)
         { return a.email < b.email; });
  }

  vector<zamestnanec>::iterator JeVDatabazi(vector<zamestnanec> &zamestnanec_databaze, string email)
  {
    auto it = lower_bound(zamestnanec_databaze.begin(), zamestnanec_databaze.end(), email, [](const zamestnanec &zamestnanec, const string &HledanyEmail)
                          { return zamestnanec.email < HledanyEmail; });

    if (it != zamestnanec_databaze.end() && it->email == email)
    {
      return it;
    }
    else
    {
      return zamestnanec_databaze.end();
    }
  }

  vector<zamestnanec>::const_iterator JeVDatabaziConst(const vector<zamestnanec> &zamestnanec_databaze, const string email) const
  {
    auto it = lower_bound(zamestnanec_databaze.begin(), zamestnanec_databaze.end(), email, [](const zamestnanec &zamestnanec, const string &HledanyEmail)
                          { return zamestnanec.email < HledanyEmail; });
    if (it != zamestnanec_databaze.end() && it->email == email)
    {
      return it;
    }
    else
    {
      return zamestnanec_databaze.end();
    }
  }

  vector<zamestnanec>::iterator JeVDatabazi(vector<zamestnanec> &zamestnanec_databaze, string name, string surname)
  {
    auto it = lower_bound(zamestnanec_databaze.begin(), zamestnanec_databaze.end(), make_pair(name, surname), [](const zamestnanec &zamestnanec, const pair<string, string> &nameAndSurname)
                          { return make_pair(zamestnanec.name, zamestnanec.surname) < nameAndSurname; });
    if (it != zamestnanec_databaze.end() && it->name == name && it->surname == surname)
    {
      return it;
    }
    else
    {
      return zamestnanec_databaze.end();
    }
  }

  vector<zamestnanec>::const_iterator JeVDatabaziConst(const vector<zamestnanec> &zamestnanec_databaze, const string name, const string surname) const
  {

    auto it = lower_bound(zamestnanec_databaze.begin(), zamestnanec_databaze.end(), make_pair(name, surname), [](const zamestnanec &zamestnanec, const pair<string, string> &nameAndSurname)
                          {       if (zamestnanec.name == nameAndSurname.first)
                        {
                          return zamestnanec.surname < nameAndSurname.second;
                        }
                        return zamestnanec.name < nameAndSurname.first; });

    if (it != zamestnanec_databaze.end() && it->name == name && it->surname == surname)
    {
      return it;
    }
    else
    {
      return zamestnanec_databaze.end();
    }
  }
};


int main(void)
{
  string outName, outSurname;
  int lo, hi;
  
    CPersonalAgenda b1;
    assert(b1.add("John", "Smith", "john", 30000));
    assert(b1.add("John", "Miller", "johnm", 35000));
    assert(b1.add("Peter", "Smith", "peter", 23000));
    assert(b1.getFirst(outName, outSurname) && outName == "John" && outSurname == "Miller");
    assert(b1.getNext("John", "Miller", outName, outSurname) && outName == "John" && outSurname == "Smith");
    assert(b1.getNext("John", "Smith", outName, outSurname) && outName == "Peter" && outSurname == "Smith");
    assert(!b1.getNext("Peter", "Smith", outName, outSurname));

    assert(b1.setSalary("john", 32000));
    assert(b1.getSalary("john") == 32000);
    assert(b1.getSalary("John", "Smith") == 32000);
    assert(b1.getRank("John", "Smith", lo, hi) && lo == 1 && hi == 1);
    assert(b1.getRank("john", lo, hi) && lo == 1 && hi == 1);
    assert(b1.getRank("peter", lo, hi) && lo == 0 && hi == 0);
    assert(b1.getRank("johnm", lo, hi) && lo == 2 && hi == 2);
    assert(b1.setSalary("John", "Smith", 35000));
    assert(b1.getSalary("John", "Smith") == 35000);
    assert(b1.getSalary("john") == 35000);
    assert(b1.getRank("John", "Smith", lo, hi) && lo == 1 && hi == 2);
    assert(b1.getRank("john", lo, hi) && lo == 1 && hi == 2);
    assert(b1.getRank("peter", lo, hi) && lo == 0 && hi == 0);
    assert(b1.getRank("johnm", lo, hi) && lo == 1 && hi == 2);
    assert(b1.changeName("peter", "James", "Bond"));
    assert(b1.getSalary("peter") == 23000);
    assert(b1.getSalary("James", "Bond") == 23000);
    assert(b1.getSalary("Peter", "Smith") == 0);
    assert(b1.getFirst(outName, outSurname) && outName == "James" && outSurname == "Bond");
    assert(b1.getNext("James", "Bond", outName, outSurname) && outName == "John" && outSurname == "Miller");
    assert(b1.getNext("John", "Miller", outName, outSurname) && outName == "John" && outSurname == "Smith");
    assert(!b1.getNext("John", "Smith", outName, outSurname));
    assert(b1.changeEmail("James", "Bond", "james"));
    assert(b1.getSalary("James", "Bond") == 23000);
    assert(b1.getSalary("james") == 23000);
    assert(b1.getSalary("peter") == 0);
    assert(b1.del("james"));
    assert(b1.getRank("john", lo, hi) && lo == 0 && hi == 1);
    assert(b1.del("John", "Miller"));
    assert(b1.getRank("john", lo, hi) && lo == 0 && hi == 0);
    assert(b1.getFirst(outName, outSurname) && outName == "John" && outSurname == "Smith");
    assert(!b1.getNext("John", "Smith", outName, outSurname));
    assert(b1.del("john"));
    assert(!b1.getFirst(outName, outSurname));
    assert(b1.add("John", "Smith", "john", 31000));
    assert(b1.add("john", "Smith", "joHn", 31000));
    assert(b1.add("John", "smith", "jOhn", 31000));

   

 

  return EXIT_SUCCESS;
}

