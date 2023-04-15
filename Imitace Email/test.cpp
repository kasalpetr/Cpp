#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

using namespace std;

class CMail
{
public:
  CMail(const char *from, const char *to, const char *body)
  {
    m_from = new char[strlen(from) + 1];
    strcpy(m_from, from);

    m_to = new char[strlen(to) + 1];
    strcpy(m_to, to);

    m_body = new char[strlen(body) + 1];
    strcpy(m_body, body);
  }

  CMail(const CMail &other)
  {
    m_from = new char[strlen(other.m_from) + 1];
    strcpy(m_from, other.m_from);

    m_to = new char[strlen(other.m_to) + 1];
    strcpy(m_to, other.m_to);

    m_body = new char[strlen(other.m_body) + 1];
    strcpy(m_body, other.m_body);
  }

  ~CMail()
  {
    delete[] m_from;
    delete[] m_to;
    delete[] m_body;
  }

  bool operator==(const CMail &x) const
  {
    return strcmp(m_from, x.m_from) == 0 &&
           strcmp(m_to, x.m_to) == 0 &&
           strcmp(m_body, x.m_body) == 0;
  }

  friend ostream &operator<<(ostream &os, const CMail &m)
  {
    os << "From: " << m.m_from << ", "
       << "To: " << m.m_to << ", "
       << "Body: " << m.m_body;
    return os;
  }

  bool operator<(const CMail &other) const
  {
    return m_to < other.m_to;
  }

  char *get_from() const
  {
    return m_from;
  }

  char *get_to() const
  {
    return m_to;
  }

private:
  char *m_from;
  char *m_to;
  char *m_body;
};

template <typename T>
class Vector
{
public:
  Vector() : m_size(0), m_capacity(4), m_data(new T *[m_capacity]) {}

  Vector(const Vector &other) : m_size(other.m_size), m_capacity(other.m_capacity), m_data(new T *[m_capacity])
  {
    for (int i = 0; i < m_size; ++i)
    {
      m_data[i] = new T(*other.m_data[i]);
    }
  }

  ~Vector()
  {
    for (int i = 0; i < m_size; ++i)
    {
      delete m_data[i];
    }
    delete[] m_data;
  }

  void push_back(const T &mail)
  {
    if (m_size == m_capacity)
    {
      reserve(m_capacity * 2);
    }
    m_data[m_size++] = new T(mail);
  }

  void clear()
  {
    for (int i = 0; i < m_size; ++i)
    {
      delete m_data[i];
    }
    m_size = 0;
  }

  void insert(int index, const T &value)
  {
    if (index < 0 || index > m_size)
    {
      throw std::out_of_range("Invalid index");
    }

    if (m_size == m_capacity)
    {
      reserve(m_capacity * 2);
    }

    for (int i = m_size; i > index; --i)
    {
      m_data[i] = m_data[i - 1];
    }

    m_data[index] = new T(value);
    ++m_size;
  }

  int m_size = 0;
  int m_capacity;
  T **m_data;

private:
  void reserve(int newCapacity)
  {
    T **newData = new T *[newCapacity];
    for (int i = 0; i < m_size; ++i)
    {
      newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
  }
};

int lower_boundto(const Vector<Vector<CMail>> &a, const char *key) 
{
  int left = 0;
  int right = a.m_size - 1;
  int mid;

  while (left <= right)
  {
    mid = (left + right) / 2;
    if (strcmp(a.m_data[mid]->m_data[0]->get_to(), key) < 0)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return left;
}

int lower_boundfrom(const Vector<Vector<CMail>> &a, const char *key) 
{
  int left = 0;
  int right = a.m_size - 1;
  int mid;

  while (left <= right)
  {
    mid = (left + right) / 2;
    if (strcmp(a.m_data[mid]->m_data[0]->get_from(), key) < 0)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return left;
}

class CMailIterator
{
public:
  CMailIterator(const Vector<CMail> *inbox) : m_inbox(inbox != nullptr && inbox->m_size > 0 ? new Vector<CMail>(*inbox) : nullptr), m_index(0) {}

  ~CMailIterator()
  {
    delete m_inbox;
  }

  explicit operator bool(void) const
  {
    if (m_inbox == nullptr)
    {
      return false;
    }
    else
    {
      return m_index < m_inbox->m_size;
    }
  }

  bool operator!(void) const
  {
    if (m_inbox == nullptr)
    {
      return true;
    }
    else
    {
      return !(m_index < m_inbox->m_size);
    }
  }

  void vypis()
  {
    cout << *m_inbox->m_data[m_index] << endl;
  }

  const CMail &operator*(void) const
  {
    return *m_inbox->m_data[m_index];
  }

  CMailIterator &operator++(void)
  {
    m_index++;
    return *this;
  }

private:
  const Vector<CMail> *m_inbox;
  int m_index;
};

class CMailServer
{
public:
  CMailServer(void)
  {
  }

  CMailServer(const CMailServer &src)
  {
    for (int i = 0; i < src.inboxvektor.m_size; i++)
    {
      Vector<CMail> new_inbox = *(src.inboxvektor.m_data[i]);
      inboxvektor.push_back(new_inbox);
    }
    for (int i = 0; i < src.outboxvektor.m_size; i++)
    {
      Vector<CMail> new_outbox = *(src.outboxvektor.m_data[i]);
      outboxvektor.push_back(new_outbox);
    }
  }

  CMailServer &operator=(const CMailServer &src)
  {
    if (this == &src)
    {
      return *this;
    }
    this->inboxvektor.clear();
    this->outboxvektor.clear();
    for (int i = 0; i < src.inboxvektor.m_size; i++)
    {
      Vector<CMail> new_inbox = *(src.inboxvektor.m_data[i]);
      this->inboxvektor.push_back(new_inbox);
    }
    for (int i = 0; i < src.outboxvektor.m_size; i++)
    {
      Vector<CMail> new_outbox = *(src.outboxvektor.m_data[i]);
      this->outboxvektor.push_back(new_outbox);
    }
    return *this;
  }

  ~CMailServer(void)
  {
    inboxvektor.clear();
    outboxvektor.clear();
  }

  void sendMail(const CMail &m)
  {
    if (inboxvektor.m_size == 0 && outboxvektor.m_size == 0) // když je to první prvek
    {
      box.clear();
      box.push_back(m);
      inboxvektor.push_back(box);
      outboxvektor.push_back(box);
    }
    else
    {
      auto it2 = lower_boundfrom(outboxvektor, m.get_from());
      if(outboxvektor.m_size > it2){
      if (strcmp(outboxvektor.m_data[it2]->m_data[0]->get_from(), m.get_from()) == 0)
      {
        outboxvektor.m_data[it2]->push_back(m);
      }  else
      {
        box.clear();
        box.push_back(m);
        outboxvektor.insert(it2, box);
      }
      }
      else
      {
        box.clear();
        box.push_back(m);
        outboxvektor.insert(it2, box);
      }

      auto it = lower_boundto(inboxvektor, m.get_to());
      if(inboxvektor.m_size > it){
      if (strcmp(inboxvektor.m_data[it]->m_data[0]->get_to(), m.get_to()) == 0)
      {
        inboxvektor.m_data[it]->push_back(m);
      }
      else
      {
        box.clear();
        box.push_back(m);
        inboxvektor.insert(it, box);
      }
      }else
      {
        box.clear();
        box.push_back(m);
        inboxvektor.insert(it, box);
      }
    }
  }

  void vypis()
  {
    cout << "inboxvektor --------------\n"
         << endl;
    for (int i = 0; i < inboxvektor.m_size; i++)
    {
      cout << "-->" << inboxvektor.m_data[i]->m_data[0]->get_to() << "<--\n"
           << endl;

      for (int j = 0; j < inboxvektor.m_data[i]->m_size; j++)
      {
        cout << *inboxvektor.m_data[i]->m_data[j] << endl;
      }
    }
    cout << endl;

    cout << "outboxvektor -------------- \n"
         << endl;
    for (int i = 0; i < outboxvektor.m_size; i++)
    {
      cout << "\n-->" << outboxvektor.m_data[i]->m_data[0]->get_from() << "<--\n"
           << endl;
      for (int j = 0; j < outboxvektor.m_data[i]->m_size; j++)
      {
        cout << *outboxvektor.m_data[i]->m_data[j] << endl;
      }
    }
    cout << endl;
  }

  CMailIterator outbox(const char *email) const
  {
    Vector<CMail> empty;

    for (int i = 0; i < outboxvektor.m_size; i++)
    {
      if (strcmp(outboxvektor.m_data[i]->m_data[0]->get_from(), email) == 0)
      {
        return outboxvektor.m_data[i];
      }
    }
    return CMailIterator(&empty);
  }

  CMailIterator inbox(const char *email) const
  {
    Vector<CMail> empty;
    auto it = lower_boundto(inboxvektor, email);
    if (strcmp(inboxvektor.m_data[it]->m_data[0]->get_to(), email) == 0)
    {
        return inboxvektor.m_data[it];
    }
    
    return CMailIterator(&empty);
  }

private:
  Vector<CMail> box;
  Vector<Vector<CMail>> inboxvektor;
  Vector<Vector<CMail>> outboxvektor;
  bool change = false;
};

#ifndef __PROGTEST__

bool matchOutput(const CMail &m, const char *str)
{
  ostringstream oss;
  oss << m;
  return oss.str() == str;
}

int main(void)
{
  char from[100], to[100], body[1024];

  assert(CMail("john", "peter", "progtest deadline") == CMail("john", "peter", "progtest deadline"));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("john", "progtest deadline", "peter")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("peter", "john", "progtest deadline")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("peter", "progtest deadline", "john")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "john", "peter")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "peter", "john")));

  CMailServer s0;
  s0.sendMail(CMail("john", "peter", "some important mail"));

  strncpy(from, "john", sizeof(from));
  strncpy(to, "thomas", sizeof(to));
  strncpy(body, "another important mail", sizeof(body));
  s0.sendMail(CMail(from, to, body));
  strncpy(from, "john", sizeof(from));
  strncpy(to, "alice", sizeof(to));
  strncpy(body, "deadline notice", sizeof(body));
  s0.sendMail(CMail(from, to, body));
  s0.sendMail(CMail("alice", "john", "deadline confirmation"));
  s0.sendMail(CMail("peter", "alice", "PR bullshit"));

  CMailIterator i0 = s0.inbox("alice");
  assert(i0 && *i0 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
  assert(++i0 && *i0 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i0, "From: peter, To: alice, Body: PR bullshit"));
  assert(!++i0);

  CMailIterator i1 = s0.inbox("john");
  assert(i1 && *i1 == CMail("alice", "john", "deadline confirmation"));
  assert(matchOutput(*i1, "From: alice, To: john, Body: deadline confirmation"));
  assert(!++i1);

  CMailIterator i2 = s0.outbox("john");
  assert(i2 && *i2 == CMail("john", "peter", "some important mail"));
  assert(matchOutput(*i2, "From: john, To: peter, Body: some important mail"));
  assert(++i2 && *i2 == CMail("john", "thomas", "another important mail"));
  assert(matchOutput(*i2, "From: john, To: thomas, Body: another important mail"));
  assert(++i2 && *i2 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i2, "From: john, To: alice, Body: deadline notice"));
  assert(!++i2);

  CMailIterator i3 = s0.outbox("thomas");
  assert(!i3);

  CMailIterator i4 = s0.outbox("steve");
  assert(!i4);

  CMailIterator i5 = s0.outbox("thomas");
  s0.sendMail(CMail("thomas", "boss", "daily report"));
  assert(!i5);

  CMailIterator i6 = s0.outbox("thomas");
  assert(i6 && *i6 == CMail("thomas", "boss", "daily report"));
  assert(matchOutput(*i6, "From: thomas, To: boss, Body: daily report"));
  assert(!++i6);

  CMailIterator i7 = s0.inbox("alice");
  s0.sendMail(CMail("thomas", "alice", "meeting details"));
  assert(i7 && *i7 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i7, "From: john, To: alice, Body: deadline notice"));
  assert(++i7 && *i7 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i7, "From: peter, To: alice, Body: PR bullshit"));
  assert(!++i7);

  CMailIterator i8 = s0.inbox("alice");
  assert(i8 && *i8 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i8, "From: john, To: alice, Body: deadline notice"));
  assert(++i8 && *i8 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i8, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i8 && *i8 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i8, "From: thomas, To: alice, Body: meeting details"));
  assert(!++i8);

  CMailServer s1(s0);
  s0.sendMail(CMail("joe", "alice", "delivery details"));
  s1.sendMail(CMail("sam", "alice", "order confirmation"));
  CMailIterator i9 = s0.inbox("alice");
  assert(i9 && *i9 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i9, "From: john, To: alice, Body: deadline notice"));
  assert(++i9 && *i9 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i9, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i9 && *i9 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i9, "From: thomas, To: alice, Body: meeting details"));
  assert(++i9 && *i9 == CMail("joe", "alice", "delivery details"));
  assert(matchOutput(*i9, "From: joe, To: alice, Body: delivery details"));
  assert(!++i9);

  CMailIterator i10 = s1.inbox("alice");
  assert(i10 && *i10 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i10, "From: john, To: alice, Body: deadline notice"));
  assert(++i10 && *i10 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i10, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i10 && *i10 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i10, "From: thomas, To: alice, Body: meeting details"));
  assert(++i10 && *i10 == CMail("sam", "alice", "order confirmation"));
  assert(matchOutput(*i10, "From: sam, To: alice, Body: order confirmation"));
  assert(!++i10);

  CMailServer s2;
  s2.sendMail(CMail("alice", "alice", "mailbox test"));
  CMailIterator i11 = s2.inbox("alice");
  assert(i11 && *i11 == CMail("alice", "alice", "mailbox test"));
  assert(matchOutput(*i11, "From: alice, To: alice, Body: mailbox test"));
  assert(!++i11);

  s2 = s0;
  s0.sendMail(CMail("steve", "alice", "newsletter"));
  s2.sendMail(CMail("paul", "alice", "invalid invoice"));
  CMailIterator i12 = s0.inbox("alice");
  assert(i12 && *i12 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i12, "From: john, To: alice, Body: deadline notice"));
  assert(++i12 && *i12 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i12, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i12 && *i12 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i12, "From: thomas, To: alice, Body: meeting details"));
  assert(++i12 && *i12 == CMail("joe", "alice", "delivery details"));
  assert(matchOutput(*i12, "From: joe, To: alice, Body: delivery details"));
  assert(++i12 && *i12 == CMail("steve", "alice", "newsletter"));
  assert(matchOutput(*i12, "From: steve, To: alice, Body: newsletter"));
  assert(!++i12);

  CMailIterator i13 = s2.inbox("alice");
  assert(i13 && *i13 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i13, "From: john, To: alice, Body: deadline notice"));
  assert(++i13 && *i13 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i13, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i13 && *i13 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i13, "From: thomas, To: alice, Body: meeting details"));
  assert(++i13 && *i13 == CMail("joe", "alice", "delivery details"));
  assert(matchOutput(*i13, "From: joe, To: alice, Body: delivery details"));
  assert(++i13 && *i13 == CMail("paul", "alice", "invalid invoice"));
  assert(matchOutput(*i13, "From: paul, To: alice, Body: invalid invoice"));
  assert(!++i13);

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
