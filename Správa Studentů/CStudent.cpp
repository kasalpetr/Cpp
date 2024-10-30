#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
// #include <compare>
using namespace std;

class CDate
{
public:
  CDate(int y, int m, int d) : m_Y(y), m_M(m), m_D(d)
  {
  }

  // strong_ordering operator<=>(const CDate &other) const = default;

  // friend ostream &operator<<(ostream &os, const CDate &d)
  // {
  //   return os << d.m_Y << '-' << d.m_M << '-' << d.m_D;
  // }

private:
  int m_Y;
  int m_M;
  int m_D;
};
enum class ESortKey
{
  NAME,
  BIRTH_DATE,
  ENROLL_YEAR
};
#endif /* __PROGTEST__ */
using namespace std;

class CStudent
{
public:
  CStudent(const string &name, const CDate &born, int enrolled) : Realname(name), born(born), enrolled(enrolled)
  {
    // Rozdělíme jméno na slova a převedeme všechna písmena na malá písmena
    istringstream iss(name);
    set<string> words;
    string word;
    while (iss >> word)
    {
      transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                { return tolower(c); });
      words.insert(word);
    }

    // Spojíme seřazená slova do Smallname
    Smallname.reserve(name.size());
    for (const string &word : words)
    {
      Smallname += word + " ";
    }
  }
  bool operator==(const CStudent &other) const
  {
    // if (Realname == other.Realname && born == other.born && enrolled == other.enrolled)
    // {
    //   return true;
    // }
    return false;
  }
  bool operator!=(const CStudent &other) const
  {
    return !(*this == other);
  }

  // Porovnání studentů pro třídění
  bool operator<(const CStudent &other) const
  {
    // if (enrolled != other.enrolled)
    //   return enrolled < other.enrolled;

    // // if (born != other.born)
    //   return born < other.born;

    // return Realname < other.Realname;
  }

  const string &getRealname() const
  {
    return Realname;
  }
  const string &getSmallname() const
  {
    return Smallname;
  }
  const CDate &getBorn() const
  {
    return born;
  }
 const int &getEnrolled() const
  {
    return enrolled;
  }

private:
  string Realname;
  string Smallname;
  CDate born;
  int enrolled;
};

class CFilter
{
public:
  CFilter() {}

  CFilter &name(const string &name)
  {
    // Rozdělíme jméno na slova a převedeme všechna písmena na malá písmena
    istringstream iss(name);
    set<string> words;
    string word;
    while (iss >> word)
    {
      transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                { return tolower(c); });
      words.insert(word);
    }

    // Spojíme seřazená slova do Smallname
    string Smallname;
    Smallname.reserve(name.size());
    for (const string &word : words)
    {
      Smallname += word + " ";
    }

    m_Name.push_back(Smallname);
    return *this;
  }

  CFilter &bornBefore(const CDate &date)
  {
    m_BornBefore = date;
    return *this;
  }

  CFilter &bornAfter(const CDate &date)
  {
    m_BornAfter = date;
    return *this;
  }

  CFilter &enrolledBefore(int year)
  {
    m_EnrolledBefore = year;
    return *this;
  }

  CFilter &enrolledAfter(int year)
  {
    m_EnrolledAfter = year;
    return *this;
  }

  bool isEmpty() const
  {
    return m_Name.empty() && m_BornBefore == CDate(INT_MAX, 12, 31) && m_BornAfter == CDate(INT_MIN, 1, 1) && m_EnrolledBefore == INT_MIN && m_EnrolledAfter == INT_MAX;
  }

  const std::vector<std::string> &getName() const
  {
    return m_Name;
  }
  const CDate &getBornBefore() const
  {
    return m_BornBefore;
  }
  const CDate &getBornAfter() const
  {
    return m_BornAfter;
  }
  const int &getEnrolledBefore() const
  {
    return m_EnrolledBefore;
  }
  const int &getEnrolledAfter() const
  {
    return m_EnrolledAfter;
  }

private:
  vector<string> m_Name;
  CDate m_BornBefore = CDate(INT_MAX, 12, 31); // Nejnižší možné datum
  CDate m_BornAfter = CDate(INT_MIN, 1, 1);    // Nejvyšší možné datum
  int m_EnrolledBefore = INT_MAX;              // Nejnižší možný rok
  int m_EnrolledAfter = INT_MIN;               // Nejvyšší možný rok
};

class CSort
{
public:
  CSort() {}

  CSort &addKey(ESortKey key, bool ascending)
  {
    m_Keys.push_back(make_pair(key, ascending));
    return *this;
  }

  // Metoda pro porovnání dvou studentů podle klíčů řazení
  bool compareStudents(const CStudent &a, const CStudent &b) const
  {
    auto sortByKey = [&](const CStudent &a, const CStudent &b)
    {
      for (const auto &key : m_Keys)
      {
        bool ascending = key.second;
        switch (key.first)
        {
        case ESortKey::NAME:
          if (a.getRealname() != b.getRealname())
            return ascending ? a.getRealname() < b.getRealname() : b.getRealname() < a.getRealname();
          break;
        case ESortKey::BIRTH_DATE:
          if (a.getBorn() != b.getBorn())
            return ascending ? a.getBorn() < b.getBorn() : b.getBorn() < a.getBorn();
          break;
        case ESortKey::ENROLL_YEAR:
          if (a.getEnrolled() != b.getEnrolled())
            return ascending ? a.getEnrolled() < b.getEnrolled() : b.getEnrolled() < a.getEnrolled();
          break;
        }
      }
      // Pokud žádné kritérium neprovede řazení, použije se třídění podle ID
      return false;
    };

    return sortByKey(a, b);
  }

private:
  vector<pair<ESortKey, bool>> m_Keys;
};

class CStudyDept
{
public:
  CStudyDept() {}
  bool addStudent(const CStudent &x)
  {

    pair<CStudent, size_t> studentPair(x, Student_id); // Předpokládáme, že student má člen id
    // Vytvoříme pár pro přidání do setu StudyDept

    // Pokusíme se přidat studenta do StudyDept
    auto result = StudyDept.insert(studentPair);

    // Pokud student byl úspěšně přidán do StudyDept (nebyl tam ještě)
    if (result.second)
    {
      // Přidáme ho také do StudyDept_by_id
      StudyDept_by_id.insert(studentPair);
      Student_id++;
      return true;
    }

    // Student již byl v setu StudyDept
    return false;
  }

  bool delStudent(const CStudent &x)
  {
    // Vytvoření dočasného objektu pro vyhledání ve struktuře std::set
    std::pair<CStudent, size_t> tempPair(x, 0);

    // Hledání studenta ve struktuře std::set
    auto it = StudyDept.find(tempPair);

    // Pokud student nebyl nalezen, vrátíme false
    if (it == StudyDept.end())
    {
      return false;
    }

    // Získání id studenta
    size_t studentId = it->second;
    tempPair.second = studentId;
    // Odstranění studenta ze setu StudyDept
    StudyDept.erase(it);

    // Odstranění studenta i ze setu StudyDept_by_id pomocí jeho id
    StudyDept_by_id.erase(tempPair);

    return true; // Student byl úspěšně smazán
  }

  list<CStudent> search(const CFilter &flt, const CSort &sortOpt) const
  {
    list<CStudent> result;

    // Získání seznamu studentů z StudyDept_by_id
    if (flt.isEmpty())
    { // beru vsechny studenty jak prisly
      for (const auto &student : StudyDept_by_id)
      {
        result.push_back(student.first);
      }
    }
    else
    {
      for (const auto &student : StudyDept_by_id)
      {
        if (student.first.getBorn() > flt.getBornAfter() && student.first.getBorn() < flt.getBornBefore() && student.first.getEnrolled() > flt.getEnrolledAfter() && student.first.getEnrolled() < flt.getEnrolledBefore())
        {
          // Kontrola jména studenta
          if (flt.getName().empty())
          {
            result.push_back(student.first);
          }
          else
          {
            for (const std::string &filterName : flt.getName())
            {
              if (student.first.getSmallname() == filterName)
              {
                result.push_back(student.first);
                break;
              }
            }
          }
        }
      }
    }

    // Seřazení studentů podle specifikace v objektu CSort
    result.sort([&](const CStudent &a, const CStudent &b)
                { return sortOpt.compareStudents(a, b); });

    return result;
  }

  set<string> suggest(const string &name) const
  {
    set<string> suggestedNames;

    // Převedeme všechna písmena na malá písmena a rozdělíme jméno na slova
    istringstream iss(name);
    vector<string> words;
    string word;
    while (iss >> word)
    {
      transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                { return tolower(c); });
      words.push_back(word + " ");
    }

    // Projdeme všechny studenty ve StudyDept_by_id
    for (const auto &student : StudyDept_by_id)
    {
      bool nameMatches = true;
      // Pro každé slovo z jména
      for (const string &word : words)
      {
        // Kontrola, zda normalizované jméno studenta obsahuje dané slovo
        if (student.first.getSmallname().find(word) == string::npos)
        {
          nameMatches = false;
          break; // Pokud neobsahuje, přeskočíme tento student
        }
      }
      // Pokud všechna slova z jména odpovídají, přidáme normalizované jméno studenta do setu navržených
      if (nameMatches)
      {
        suggestedNames.insert(student.first.getRealname());
      }
    }

    return suggestedNames;
  }

private:
  struct CompareByID
  {
    bool operator()(const pair<CStudent, size_t> &lhs, const pair<CStudent, size_t> &rhs) const
    {
      return lhs.second < rhs.second;
    }
  };

  struct CompareStudentPairs
  {
    bool operator()(const std::pair<CStudent, size_t> &a, const std::pair<CStudent, size_t> &b) const
    {
      return a.first < b.first; // Porovnání prvních prvků dvojic
    }
  };

  set<pair<CStudent, size_t>, CompareByID> StudyDept_by_id;
  set<pair<CStudent, size_t>, CompareStudentPairs> StudyDept;
  size_t Student_id = 0;
};
#ifndef __PROGTEST__
int main(void)
{
  CStudyDept x0;
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("James Bond", CDate(1980, 4, 11), 2010));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("James Bond", CDate(1980, 4, 11), 2010)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("Peter Peterson", CDate(1980, 4, 11), 2010));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("Peter Peterson", CDate(1980, 4, 11), 2010)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("James Bond", CDate(1997, 6, 17), 2010));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("James Bond", CDate(1997, 6, 17), 2010)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("James Bond", CDate(1980, 4, 11), 2016));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("James Bond", CDate(1980, 4, 11), 2016)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("Peter Peterson", CDate(1980, 4, 11), 2016));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("Peter Peterson", CDate(1980, 4, 11), 2016)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("Peter Peterson", CDate(1997, 6, 17), 2010));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("Peter Peterson", CDate(1997, 6, 17), 2010)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("James Bond", CDate(1997, 6, 17), 2016));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("James Bond", CDate(1997, 6, 17), 2016)));
  assert(CStudent("James Bond", CDate(1980, 4, 11), 2010) != CStudent("Peter Peterson", CDate(1997, 6, 17), 2016));
  assert(!(CStudent("James Bond", CDate(1980, 4, 11), 2010) == CStudent("Peter Peterson", CDate(1997, 6, 17), 2016)));
  assert(x0.addStudent(CStudent("John Peter Taylor", CDate(1983, 7, 13), 2014)));
  assert(x0.addStudent(CStudent("John Taylor", CDate(1981, 6, 30), 2012)));
  assert(x0.addStudent(CStudent("Peter Taylor", CDate(1982, 2, 23), 2011)));
  assert(x0.addStudent(CStudent("Peter John Taylor", CDate(1984, 1, 17), 2017)));
  assert(x0.addStudent(CStudent("James Bond", CDate(1981, 7, 16), 2013)));
  assert(x0.addStudent(CStudent("James Bond", CDate(1982, 7, 16), 2013)));
  assert(x0.addStudent(CStudent("James Bond", CDate(1981, 8, 16), 2013)));
  assert(x0.addStudent(CStudent("James Bond", CDate(1981, 7, 17), 2013)));
  assert(x0.addStudent(CStudent("James Bond", CDate(1981, 7, 16), 2012)));
  assert(x0.addStudent(CStudent("Bond James", CDate(1981, 7, 16), 2013)));
  assert(x0.search(CFilter().bornAfter(CDate(0, 0, 0)), CSort()) == (list<CStudent>{
                                                                        CStudent("John Peter Taylor", CDate(1983, 7, 13), 2014),
                                                                        CStudent("John Taylor", CDate(1981, 6, 30), 2012),
                                                                        CStudent("Peter Taylor", CDate(1982, 2, 23), 2011),
                                                                        CStudent("Peter John Taylor", CDate(1984, 1, 17), 2017),
                                                                        CStudent("James Bond", CDate(1981, 7, 16), 2013),
                                                                        CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                        CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                        CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                        CStudent("James Bond", CDate(1981, 7, 16), 2012),
                                                                        CStudent("Bond James", CDate(1981, 7, 16), 2013)}));
  assert(x0.search(CFilter(), CSort().addKey(ESortKey::NAME, true)) == (list<CStudent>{
                                                                           CStudent("Bond James", CDate(1981, 7, 16), 2013),
                                                                           CStudent("James Bond", CDate(1981, 7, 16), 2013),
                                                                           CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                           CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                           CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                           CStudent("James Bond", CDate(1981, 7, 16), 2012),
                                                                           CStudent("John Peter Taylor", CDate(1983, 7, 13), 2014),
                                                                           CStudent("John Taylor", CDate(1981, 6, 30), 2012),
                                                                           CStudent("Peter John Taylor", CDate(1984, 1, 17), 2017),
                                                                           CStudent("Peter Taylor", CDate(1982, 2, 23), 2011)}));
  assert(x0.search(CFilter(), CSort().addKey(ESortKey::NAME, false)) == (list<CStudent>{
                                                                            CStudent("Peter Taylor", CDate(1982, 2, 23), 2011),
                                                                            CStudent("Peter John Taylor", CDate(1984, 1, 17), 2017),
                                                                            CStudent("John Taylor", CDate(1981, 6, 30), 2012),
                                                                            CStudent("John Peter Taylor", CDate(1983, 7, 13), 2014),
                                                                            CStudent("James Bond", CDate(1981, 7, 16), 2013),
                                                                            CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                            CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                            CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                            CStudent("James Bond", CDate(1981, 7, 16), 2012),
                                                                            CStudent("Bond James", CDate(1981, 7, 16), 2013)}));
  assert(x0.search(CFilter(), CSort().addKey(ESortKey::ENROLL_YEAR, false).addKey(ESortKey::BIRTH_DATE, false).addKey(ESortKey::NAME, true)) == (list<CStudent>{
                                                                                                                                                    CStudent("Peter John Taylor", CDate(1984, 1, 17), 2017),
                                                                                                                                                    CStudent("John Peter Taylor", CDate(1983, 7, 13), 2014),
                                                                                                                                                    CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                                                                                                    CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                                                                                                    CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                                                                                                    CStudent("Bond James", CDate(1981, 7, 16), 2013),
                                                                                                                                                    CStudent("James Bond", CDate(1981, 7, 16), 2013),
                                                                                                                                                    CStudent("James Bond", CDate(1981, 7, 16), 2012),
                                                                                                                                                    CStudent("John Taylor", CDate(1981, 6, 30), 2012),
                                                                                                                                                    CStudent("Peter Taylor", CDate(1982, 2, 23), 2011)}));
  assert(x0.search(CFilter().name("james bond"), CSort().addKey(ESortKey::ENROLL_YEAR, false).addKey(ESortKey::BIRTH_DATE, false).addKey(ESortKey::NAME, true)) == (list<CStudent>{
                                                                                                                                                                       CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                                                                                                                       CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                                                                                                                       CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                                                                                                                       CStudent("Bond James", CDate(1981, 7, 16), 2013),
                                                                                                                                                                       CStudent("James Bond", CDate(1981, 7, 16), 2013),
                                                                                                                                                                       CStudent("James Bond", CDate(1981, 7, 16), 2012)}));
  assert(x0.search(CFilter().bornAfter(CDate(1980, 4, 11)).bornBefore(CDate(1983, 7, 13)).name("John Taylor").name("james BOND"), CSort().addKey(ESortKey::ENROLL_YEAR, false).addKey(ESortKey::BIRTH_DATE, false).addKey(ESortKey::NAME, true)) == (list<CStudent>{
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                                                                                                                                                                                                        CStudent("Bond James", CDate(1981, 7, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 7, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 7, 16), 2012),
                                                                                                                                                                                                                                                        CStudent("John Taylor", CDate(1981, 6, 30), 2012)}));
  assert(x0.search(CFilter().name("james"), CSort().addKey(ESortKey::NAME, true)) == (list<CStudent>{}));
  assert(x0.suggest("peter") == (set<string>{
                                    "John Peter Taylor",
                                    "Peter John Taylor",
                                    "Peter Taylor"}));
  assert(x0.suggest("bond") == (set<string>{
                                   "Bond James",
                                   "James Bond"}));
  assert(x0.suggest("peter joHn") == (set<string>{
                                         "John Peter Taylor",
                                         "Peter John Taylor"}));
  assert(x0.suggest("peter joHn bond") == (set<string>{}));
  assert(x0.suggest("pete") == (set<string>{}));
  assert(x0.suggest("peter joHn PETER") == (set<string>{
                                               "John Peter Taylor",
                                               "Peter John Taylor"}));
  assert(!x0.addStudent(CStudent("James Bond", CDate(1981, 7, 16), 2013)));
  assert(x0.delStudent(CStudent("James Bond", CDate(1981, 7, 16), 2013)));
  assert(x0.search(CFilter().bornAfter(CDate(1980, 4, 11)).bornBefore(CDate(1983, 7, 13)).name("John Taylor").name("james BOND"), CSort().addKey(ESortKey::ENROLL_YEAR, false).addKey(ESortKey::BIRTH_DATE, false).addKey(ESortKey::NAME, true)) == (list<CStudent>{
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1982, 7, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 8, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 7, 17), 2013),
                                                                                                                                                                                                                                                        CStudent("Bond James", CDate(1981, 7, 16), 2013),
                                                                                                                                                                                                                                                        CStudent("James Bond", CDate(1981, 7, 16), 2012),
                                                                                                                                                                                                                                                        CStudent("John Taylor", CDate(1981, 6, 30), 2012)}));
  assert(!x0.delStudent(CStudent("James Bond", CDate(1981, 7, 16), 2013)));
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
