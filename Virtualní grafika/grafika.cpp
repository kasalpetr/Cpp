#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect
{
public:
  CRect(double x, double y, double w, double h) : m_X(x), m_Y(y), m_W(w), m_H(h)
  {
  }
  friend ostream &operator<<(ostream &os, const CRect &x)
  {
    return os << '(' << x.m_X << ',' << x.m_Y << ',' << x.m_W << ',' << x.m_H << ')';
  }
  double m_X;
  double m_Y;
  double m_W;
  double m_H;
};
#endif /* __PROGTEST__ */

// abstraktní třída
class CControl
{
public:
  // konstruktor
  CControl(int id, const CRect &rect) : id(id), rect(rect){};
  virtual ~CControl() {}

  virtual ostringstream draw(bool is_last) const = 0; // vypis

  virtual ostringstream drawAlone() const = 0; // vypis

  void resize(const CRect &newRect)
  {
    rect.m_X = pomer.m_X * newRect.m_W + newRect.m_X;
    rect.m_Y = pomer.m_Y * newRect.m_H + newRect.m_Y;

    rect.m_W = pomer.m_W * newRect.m_W;
    rect.m_H = pomer.m_H * newRect.m_H;
  } // zmena velikosti okna

  virtual unique_ptr<CControl> clone() const = 0; // clone daného objektu

  virtual string getValue() const { return ""; } // getter

  virtual void setValue(const std::string &value) {} // setter

  friend ostream &operator<<(ostream &os, const CControl &control)
  {
    os << control.drawAlone().str();
    return os;
  }

  int id;
  CRect rect;
  CRect pomer = rect;
};

class CWindow
{
public:
  CWindow(int id, const string &title, const CRect &absPos) : m_id(id), title(title), rect(absPos) {}

  CWindow(const CWindow &other) : m_id(other.m_id), title(other.title), rect(other.rect)
  {
    for (const auto &control : other.m_control)
    {
      m_control.push_back(control->clone().release());
    }
  }

  ~CWindow()
  {
    for (auto &control : m_control)
    {
      delete control;
    }
    m_control.clear();
  }

  // add
  CWindow &add(const CControl &control)
  {
    auto cloned_control = control.clone().release();
    cloned_control->resize(rect);
    m_control.push_back(cloned_control);
    return *this;
  }

  friend ostream &operator<<(ostream &os, const CWindow &window)
  {
    os << "[" << window.m_id << "] "
       << "Window \"" << window.title << "\" " << window.rect << "\n";

    for (const auto &control : window.m_control)
    {
      bool is_last_control = (control == window.m_control.back());
      os << control->draw(is_last_control).str();
    }

    return os;
  }

  CWindow &operator=(const CWindow &other)
  {
    if (this == &other)
      return *this;

    // zkopírování hodnot jednotlivých atributů
    m_id = other.m_id;
    title = other.title;
    rect = other.rect;

    // odstranění stávajících ovládacích prvků
    for (auto &control : m_control)
      delete control;
    m_control.clear();

    // vytvoření kopií ovládacích prvků z druhé instance
    for (const auto &control : other.m_control)
      m_control.push_back(control->clone().release());

    return *this;
  }
  // search
  
  CWindow setPosition(const CRect newrect){
    rect = newrect;
     for (const auto &control : m_control)
    {
     control->resize(newrect);
    }
    return *this;
  }
  CControl *search(int x)
  {
    for (auto &control : m_control)
    {
      if (control->id == x)
      {
        return control;
      }
    }
    return nullptr;
  }

  // setPosition

private:
  vector<CControl *> m_control;
  int m_id;
  string title;
  CRect rect;
};

class CButton : public CControl
{
public:
  CButton(int id, const CRect &relPos, const string &name) : CControl(id, relPos), m_text(name) {}

  unique_ptr<CControl> clone() const override
  {
    return make_unique<CButton>(*this);
  }

  ostringstream draw(bool is_last) const override
  {
    ostringstream x;
    x << "+- [" << id << "] "
      << "Button \"" << m_text << "\" " << rect << "\n";

    return x;
  }

  ostringstream drawAlone() const override
  {
    ostringstream x;
    x << "[" << id << "] "
      << "Button \"" << m_text << "\" " << rect << "\n";

    return x;
  }
  //<< pro vystup
private:
  CRect pomer = rect;
  string m_text;
};

class CInput : public CControl
{
public:
  CInput(int id, const CRect &relPos, const string &value) : CControl(id, relPos), m_input(value) {}
  // setValue
  void setValue(string x)
  {
    m_input = x;
  }

  // getValue
  string getValue()
  {
    return m_input;
  }
  //<< pro vystup

  ostringstream draw(bool is_last) const override
  {
    ostringstream x;
    x << "+- [" << id << "] "
      << "Input \"" << m_input << "\" " << rect << "\n";

    return x;
  }

  ostringstream drawAlone() const override
  {
    ostringstream x;
    x << "[" << id << "] "
      << "Input \"" << m_input << "\" " << rect << "\n";

    return x;
  }

  unique_ptr<CControl> clone() const override
  {
    return make_unique<CInput>(*this);
  }

private:
  CRect pomer = rect;
  string m_input;
};

class CLabel : public CControl
{
public:
  CLabel(int id, const CRect &relPos, const string &label) : CControl(id, relPos), m_label(label) {}

  unique_ptr<CControl> clone() const override
  {
    return make_unique<CLabel>(*this);
  }

  ostringstream draw(bool is_last) const override
  {
    ostringstream x;
    x << "+- [" << id << "] "
      << "Label \"" << m_label << "\" " << rect << "\n";

    return x;
  }

  ostringstream drawAlone() const override
  {
    ostringstream x;
    x << "[" << id << "] "
      << "Label \"" << m_label << "\" " << rect << "\n";

    return x;
  }
  //<< pro vystup
private:
  string m_label;
  CRect pomer = rect;
};

class CComboBox : public CControl
{
public:
  CComboBox(int id, const CRect &relPos) : CControl(id, relPos)
  {
  }
  // add
  CComboBox &add(string x)
  {
    box_text.push_back(x);
    return *this;
  }
  // setSelected
  void setSelected(long unsigned int index)
  {
    if (index >= 0 && index < box_text.size())
    {
      m_selectedIndex = index;
    }
  }

  ostringstream draw(bool is_last) const override
  {
    ostringstream x;
    x << "+- [" << id << "] "
      << "ComboBox " << rect << "\n";
    if (box_text.empty())
    {
      return x;
    }
    if (is_last)
    {
      for (long unsigned int i = 0; i < box_text.size(); i++)
      {
        if (i == m_selectedIndex)
        {
          x << "   +->" << box_text[i] << "<"
            << "\n";
        }
        else
        {
          x << "   +- " << box_text[i] << "\n";
        }
      }
    }
    else
    {
      for (long unsigned int i = 0; i < box_text.size(); i++)
      {
        if (i == m_selectedIndex)
        {
          x << "|  +->" << box_text[i] << "<"
            << "\n";
        }
        else
        {
          x << "|  +- " << box_text[i] << "\n";
        }
      }
    }

    return x;
  }

  ostringstream drawAlone() const override
  {
    ostringstream x;
    x << "[" << id << "] "
      << "ComboBox "
      << rect << "\n";
    for (long unsigned int i = 0; i < box_text.size(); i++)
    {
      if (i == m_selectedIndex)
      {
        x << "+->" << box_text[i] << "<"
          << "\n";
      }
      else
      {
        x << "+- " << box_text[i] << "\n";
      }
    }
    return x;
  }
  // getSelected

  int getSelected()
  {
    return m_selectedIndex;
  }

  unique_ptr<CControl> clone() const override
  {
    return make_unique<CComboBox>(*this);
  }

private:
  vector<string> box_text;
  long unsigned int m_selectedIndex = 0;
  CRect pomer = rect;
};

// output operators

#ifndef __PROGTEST__
template <typename _T>
string toString(const _T &x)
{
  ostringstream oss;
  oss << x;
  return oss.str();
}

int main(void)
{


  CWindow a(0, "Sample window", CRect(10, 10, 600, 480));
  a.add(CButton(1, CRect(0.1, 0.8, 0.3, 0.1), "Ok")).add(CButton(2, CRect(0.6, 0.8, 0.3, 0.1), "Cancel"));
  a.add(CLabel(10, CRect(0.1, 0.1, 0.2, 0.1), "Username:"));
  a.add(CInput(11, CRect(0.4, 0.1, 0.5, 0.1), "chucknorris"));
  a.add(CComboBox(20, CRect(0.1, 0.3, 0.8, 0.1)).add("Karate").add("Judo").add("Box").add("Progtest")); // memory leak

  assert(toString(a) ==
         "[0] Window \"Sample window\" (10,10,600,480)\n"
         "+- [1] Button \"Ok\" (70,394,180,48)\n"
         "+- [2] Button \"Cancel\" (370,394,180,48)\n"
         "+- [10] Label \"Username:\" (70,58,120,48)\n"
         "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
         "+- [20] ComboBox (70,154,480,48)\n"
         "   +->Karate<\n"
         "   +- Judo\n"
         "   +- Box\n"
         "   +- Progtest\n");
  CWindow b = a;

  // cout << toString(*b.search(20)) << endl;

  assert(toString(*b.search(20)) ==
         "[20] ComboBox (70,154,480,48)\n"
         "+->Karate<\n"
         "+- Judo\n"
         "+- Box\n"
         "+- Progtest\n");

  assert(dynamic_cast<CComboBox &>(*b.search(20)).getSelected() == 0);
  dynamic_cast<CComboBox &>(*b.search(20)).setSelected(3);
  assert(dynamic_cast<CInput &>(*b.search(11)).getValue() == "chucknorris");
  dynamic_cast<CInput &>(*b.search(11)).setValue("chucknorris@fit.cvut.cz");
  b.add(CComboBox(21, CRect(0.1, 0.5, 0.8, 0.1)).add("PA2").add("OSY").add("Both"));


  assert(toString(b) ==
         "[0] Window \"Sample window\" (10,10,600,480)\n"
         "+- [1] Button \"Ok\" (70,394,180,48)\n"
         "+- [2] Button \"Cancel\" (370,394,180,48)\n"
         "+- [10] Label \"Username:\" (70,58,120,48)\n"
         "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
         "+- [20] ComboBox (70,154,480,48)\n"
         "|  +- Karate\n"
         "|  +- Judo\n"
         "|  +- Box\n"
         "|  +->Progtest<\n"
         "+- [21] ComboBox (70,250,480,48)\n"
         "   +->PA2<\n"
         "   +- OSY\n"
         "   +- Both\n");
  assert(toString(a) ==
         "[0] Window \"Sample window\" (10,10,600,480)\n"
         "+- [1] Button \"Ok\" (70,394,180,48)\n"
         "+- [2] Button \"Cancel\" (370,394,180,48)\n"
         "+- [10] Label \"Username:\" (70,58,120,48)\n"
         "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
         "+- [20] ComboBox (70,154,480,48)\n"
         "   +->Karate<\n"
         "   +- Judo\n"
         "   +- Box\n"
         "   +- Progtest\n");

  b.setPosition(CRect(20, 30, 640, 520));
  cout << toString(b) << endl;

  assert(toString(b) ==
         "[0] Window \"Sample window\" (20,30,640,520)\n"
         "+- [1] Button \"Ok\" (84,446,192,52)\n"
         "+- [2] Button \"Cancel\" (404,446,192,52)\n"
         "+- [10] Label \"Username:\" (84,82,128,52)\n"
         "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
         "+- [20] ComboBox (84,186,512,52)\n"
         "|  +- Karate\n"
         "|  +- Judo\n"
         "|  +- Box\n"
         "|  +->Progtest<\n"
         "+- [21] ComboBox (84,290,512,52)\n"
         "   +->PA2<\n"
         "   +- OSY\n"
         "   +- Both\n");

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
