#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */


class CRange
{
public:
  CRange(long long int lo, long long int hi)
  {
    if (lo > hi)
    {
      throw std::logic_error("Invalid exception thrown");
    }
    else
    {
      m_lo = lo;
      m_hi = hi;
    }
  }

  long long getLo() const
  {
    return m_lo;
  }

  long long getHi() const
  {
    return m_hi;
  }

  void setHi(long long hi)
  {
    if (hi < m_lo)
    {
      throw std::logic_error("Invalid exception thrown");
    }
    m_hi = hi;
  }

  void setLo(long long lo)
  {
    if (lo > m_hi)
    {
      throw std::logic_error("Invalid exception thrown");
    }
    m_lo = lo;
  }

private:
  long long int m_lo;
  long long int m_hi;
};
class CRangeList
{
public:
  // constructor // empty -> done
  // includes long long / range // done vektor<Crange>
  // += range / range list //in progress
  // -= range / range list
  // = range / range list // in progress
  // operator ==
  // operator !=
  // operator <<

  CRangeList(){}; // konstruktor

  CRangeList(std::initializer_list<CRange> list)
  {
    for (auto &&range : list)
    {
      *this += range;
    }
  }
  CRangeList operator=(const CRange &other)
  {
    intervaly.clear();
    intervaly.push_back(other);
    return *this;
  }

  CRangeList &operator=(const CRangeList &other)
  {
    if (this == &other) // kontrola, zda nejde o přiřazení objektu sám sobě
      return *this;

    intervaly.clear(); // odstranění intervalů z původního seznamu

    for (const auto &interval : other.intervaly) // kopírování intervalů z jiného seznamu
      intervaly.push_back(interval);

    return *this;
  }

  CRangeList operator+=(const CRange &other)
  {
    auto it2 = upper_bound(intervaly.begin(), intervaly.end(), other, [](const CRange &a, const CRange &b)
                           { return a.getLo() < b.getLo(); });

    auto it = intervaly.insert(it2, other);

    if (it != intervaly.begin()) // překryti s intervaly který jsou níže
    {
      if (it->getLo() <= prev(it)->getHi() || it->getLo() == prev(it)->getHi() + 1)
      {
        if (it->getHi() < prev(it)->getHi())
        {
          it = prev(it);
          intervaly.erase(next(it));
        }
        else
        {
          prev(it)->setHi(it->getHi());
          it = prev(it);
          intervaly.erase(next(it));
        }
      }
    }

    while (1)
    {
      if (next(it) == intervaly.end()) // není na konci
      {
        break;
      }

      if (it->getHi() > next(it)->getHi()) // aktulaní horni hrana je vetsi než horní hrana dalšího intervalu -> je pres celý interval
      {
        intervaly.erase(next(it));
        continue;
      }
      else
      {                                                                                   // není pres celý interval
        if ((it->getHi() >= next(it)->getLo()) || (it->getHi() + 1 == next(it)->getLo())) //
        {

          it->setHi(next(it)->getHi());
          intervaly.erase(next(it));
          break;
        }
      }
      break;
    }

    return *this;
  }

  CRangeList operator-=(const CRange &other)
  {
    long long int tmp = 0;
    long long int tmp2 = 0;
    auto it2 = upper_bound(intervaly.begin(), intervaly.end(), other, [](const CRange &a, const CRange &b)
                           { return a.getLo() < b.getLo(); });

    auto it = intervaly.insert(it2, other);
    // porovnávám intervaly co jsou níž
    if (it != intervaly.begin())
    {
      if (!(it->getLo() > prev(it)->getHi()))
      {
        if (it->getHi() >= prev(it)->getHi()) // príchozi interval konci/pokracuje za ten pred nim
        {
          if (it->getLo() == prev(it)->getLo()) // interval který mažu z intervalu pokrývá celý předchzí interval //spodní číslo muže být maximalně stejně malé jako spodní číslo u předchozího
          {
            intervaly.erase(prev(it));
            it = prev(it);
          }
          else
          {
            prev(it)->setHi(it->getLo() - 1);
          }
        }
        else
        {
          if (it->getLo() == prev(it)->getLo() && it->getLo() == it->getHi())
          {
            prev(it)->setLo(it->getLo() + 1);
          }
          else
          {
            if (it->getLo() == prev(it)->getLo() && it->getHi() < prev(it)->getHi())
            {
              prev(it)->setLo(it->getHi() + 1);
            }
            else
            {
              tmp = prev(it)->getHi();
              tmp2 = it->getHi();
              prev(it)->setHi(it->getLo() - 1);
              it->setHi(tmp);
              it->setLo(tmp2 + 1);
              return *this;
            }
          }
        }
      }
    }

    while (1)
    {
      if (next(it) == intervaly.end())
      {
        break;
      }

      if (it->getHi() < next(it)->getLo())
      {
        break;
      }

      if (it->getHi() > next(it)->getHi())
      {
        intervaly.erase(next(it));
        continue;
      }
      if (it->getHi() < next(it)->getHi())
      {
        next(it)->setLo(it->getHi() + 1);
        break;
      }
      if (it->getHi() == next(it)->getHi())
      {
        intervaly.erase(next(it));

        break;
      }
    }
    intervaly.erase(it);
    return *this;
  }

  CRangeList operator+(const CRange &other)
  {
    *this += other;
    return *this;
  }
  CRangeList operator-(const CRange &other)
  {
    *this -= other;
    return *this;
  }

  CRangeList operator+=(const CRangeList &other)
  {
    if (*this == other)
    {
      return *this;
    }

    for (auto &it : other.intervaly)
    {
      *this += it;
    }
    return *this;
  }

  CRangeList operator-=(const CRangeList &other)
  {
    if (*this == other)
    {
      this->intervaly.clear();
    }

    for (auto &it : other.intervaly)
    {
      *this -= it;
    }
    return *this;
  }

  bool operator==(const CRangeList &other) const
  {
    if (intervaly.size() != other.intervaly.size())
    {
      return false;
    }

    auto it1 = intervaly.begin();
    auto it2 = other.intervaly.begin();

    while (it1 != intervaly.end())
    {
      if (it1->getLo() != it2->getLo() || it1->getHi() != it2->getHi())
      {
        return false;
      }

      ++it1;
      ++it2;
    }

    return true;
  }

  bool operator!=(const CRangeList &other) const
  {
    if (*this == other)
    {
      return false;
    }
    return true;
  }

  bool includes(long long val) const
  {
    return includes(CRange(val, val));
  }

  bool includes(const CRange &other) const
  {
    if (this->intervaly.empty())
    {
      return false;
    }

    auto it = upper_bound(intervaly.begin(), intervaly.end(), other, [](const CRange &a, const CRange &b)
                          { return a.getLo() < b.getLo(); });

    if (it == intervaly.begin())
    {
      return false;
    }
    if (prev(it)->getLo() <= other.getLo() && prev(it)->getHi() >= other.getHi())
    {
      return true;
    }

    return false;
  }
 
  auto begin() { return intervaly.begin(); }
  auto end() { return intervaly.end(); }
  auto begin() const { return intervaly.begin(); }
  auto end() const { return intervaly.end(); }

  vector<CRange> intervaly;

private:
  // todo
};

ostream &operator<<(ostream &os, const CRangeList &ranges)
{
  bool is_hex = os.flags() & std::ios::hex;
  if (is_hex)
  {
    os << std::dec;
  }
  os << "{";
  for (long unsigned int i = 0; i < ranges.intervaly.size(); ++i)
  {
    auto &it = ranges.intervaly[i];
    if (it.getLo() == it.getHi())
    {
      os << it.getLo();
    }
    else
    {
      os << "<" << it.getLo() << ".." << it.getHi() << ">";
    }
    if (i != ranges.intervaly.size() - 1)
    {
      os << ",";
    }
  }
  os << "}";
  if (is_hex)
  {
    os << std::hex;
  }
  return os;
}

CRangeList operator+(const CRange &a, const CRange &b)
{
  CRangeList newList;
  newList = a;
  newList += b;
  return newList;
}

CRangeList operator-(const CRange &a, const CRange &b)
{
  CRangeList newList;
  newList = a;
  newList -= b;
  return newList;
}

#ifndef __PROGTEST__
string toString(const CRangeList &x)
{
  ostringstream oss;
  oss << x;
  return oss.str();
}

int main(void)
{
  CRangeList a, b;
  /*
    a -= CRange(1, 1);
    a += CRange(1, 1);
    a -= CRange(1, 1);
    a += CRange(2, 2);
    a += CRange(3, 3);
    a += CRange(4, 4);
    a += CRange(5, 5);
    a += CRange(6, 6);
    a += CRange(7, 7);
    a += CRange(8, 8);
    a += CRange(9, 9);
    a += CRange(10, 10);
    a += CRange(11, 11);
    a += CRange(12, 12);
    a += CRange(13, 13);
    a += CRange(14, 14);
    a += CRange(15, 15);
    a += CRange(16, 16);
    a += CRange(17, 17);
    a += CRange(18, 18);
    a += CRange(19, 19);
    a += CRange(20, 20);
    a += CRange(21, 21);
    a += CRange(22, 22);
    a += CRange(23, 23);
    a += CRange(24, 24);
    a += CRange(25, 25);
    a += CRange(26, 26);
    a += CRange(27, 27);
    a += CRange(28, 28);
    a += CRange(29, 29);
    a += CRange(30, 30);
    a += CRange(31, 31);
    a += CRange(32, 32);
    a += CRange(33, 33);
    a += CRange(34, 34);operator-=
    a += CRange(35, 35);
    a += (CRange(LLONG_MIN, LLONG_MAX));
    assert(a.includes(CRange(LLONG_MIN, LLONG_MIN)));
    assert(!(a == b));
    b = a;
    assert(a == b);
  */

  //----------------------------------------------------------------------------------
  // cout << "A" << toString(a) << endl;

  a -= CRange(LLONG_MIN, LLONG_MAX);
  assert(sizeof(CRange) <= 2 * sizeof(long long));

  a = CRange(5, 10);
  a += CRange(25, 100);

  assert(toString(a) == "{<5..10>,<25..100>}");

  a += CRange(-5, 0);
  a += CRange(8, 50);
  assert(toString(a) == "{<-5..0>,<5..100>}");
  a += CRange(101, 105) + CRange(120, 150) + CRange(160, 180) + CRange(190, 210); // operator crangelist + crange je vlastne jako crangelist +=crange
  assert(toString(a) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}");
  a += CRange(106, 119) + CRange(152, 158);
  assert(toString(a) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}");
  a += CRange(-3, 170);
  a += CRange(-30, 1000);
  assert(toString(a) == "{<-30..1000>}");
  b = CRange(-500, -300) + CRange(2000, 3000) + CRange(700, 1001);
  a += b;
  assert(toString(a) == "{<-500..-300>,<-30..1001>,<2000..3000>}");
  a -= CRange(-400, -400);
  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}");
  a -= CRange(900, 2500);
  a -= CRange(10, 20) + CRange(900, 2500) + CRange(30, 40) + CRange(10000, 20000);
  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  try
  {
    a += CRange(15, 18) + CRange(10, 0) + CRange(35, 38);
    assert("Exception not thrown" == nullptr);
  }
  catch (const std::logic_error &e)
  {
  }
  catch (...)
  {
    assert("Invalid exception thrown" == nullptr);
  }
  assert(toString(a) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");

  b = a;
  assert(a == b);
  assert(!(a != b));
  b += CRange(2600, 2700);
  assert(toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
  assert(a == b);
  assert(!(a != b));
  b += CRange(15, 15);
  assert(toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}");
  assert(!(a == b));
  assert(a != b);
  assert(b.includes(15));
  assert(b.includes(2900));
  assert(b.includes(CRange(15, 15)));
  assert(b.includes(CRange(-350, -350)));
  assert(b.includes(CRange(100, 200)));
  assert(!b.includes(CRange(800, 900)));
  assert(!b.includes(CRange(-1000, -450)));
  assert(!b.includes(CRange(0, 500)));

  a += CRange(-10000, 10000) + CRange(10000000, 1000000000);
  assert(toString(a) == "{<-10000..10000>,<10000000..1000000000>}");
  b += a;
  assert(toString(b) == "{<-10000..10000>,<10000000..1000000000>}");
  b -= a;
  assert(toString(b) == "{}");
  b += CRange(0, 100) + CRange(200, 300) - CRange(150, 250) + CRange(160, 180) - CRange(170, 170);
  assert(toString(b) == "{<0..100>,<160..169>,<171..180>,<251..300>}");
  b -= CRange(10, 90) - CRange(20, 30) - CRange(40, 50) - CRange(60, 90) + CRange(70, 80);
  assert(toString(b) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}");
  // cout << "A" << toString(a) << endl;
  // cout << "B" << toString(b) << endl;

  CRangeList x{{5, 20}, {150, 200}, {-9, 12}, {48, 93}};
  assert(toString(x) == "{<-9..20>,<48..93>,<150..200>}");
  ostringstream oss;
  oss << setfill('=') << hex << left;
  for (const auto &v : x + CRange(-100, -100))
    oss << x << endl;
  oss << setw(10) << 1024;
  assert(oss.str() == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======");
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

// TO DO

// pokud se shoduje vektor s nějakým který odstranit

// odebirám z prázdného vektoru

// pretecení long long intu?