#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>
using namespace std;

class CDate
{
public:
  //---------------------------------------------------------------------------------------------
  CDate(int y, int m, int d) : m_Year(y), m_Month(m), m_Day(d)
  {
  }
  //---------------------------------------------------------------------------------------------
  int compare(const CDate &x) const
  {
    if (m_Year != x.m_Year)
      return m_Year - x.m_Year;
    if (m_Month != x.m_Month)
      return m_Month - x.m_Month;
    return m_Day - x.m_Day;
  }
  //---------------------------------------------------------------------------------------------
  int year(void) const
  {
    return m_Year;
  }
  //---------------------------------------------------------------------------------------------
  int month(void) const
  {
    return m_Month;
  }
  //---------------------------------------------------------------------------------------------
  int day(void) const
  {
    return m_Day;
  }
  //---------------------------------------------------------------------------------------------
  friend ostream &operator<<(ostream &os,
                             const CDate &x)
  {
    char oldFill = os.fill();
    return os << setfill('0') << setw(4) << x.m_Year << "-" << setw(2) << static_cast<int>(x.m_Month) << "-" << setw(2) << static_cast<int>(x.m_Day) << setfill(oldFill);
  }
  //---------------------------------------------------------------------------------------------
private:
  int16_t m_Year;
  int8_t m_Month;
  int8_t m_Day;
};
#endif /* __PROGTEST__ */
bool operator<(const CDate &lhs, const CDate &rhs)
{
  if (lhs.year() != rhs.year())
    return lhs.year() < rhs.year();
  if (lhs.month() != rhs.month())
    return lhs.month() < rhs.month();
  return lhs.day() < rhs.day();
}

class CInvoice
{
public:
  CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double vat) : m_Date(date), m_Seller(seller), m_Buyer(buyer), m_Amount(amount), m_Vat(vat)
  {
  }

  CDate date(void) const
  {
    return m_Date;
  }

  string buyer(void) const
  {
    return m_Buyer;
  }

  string seller(void) const
  {
    return m_Seller;
  }

  void setSeller(const string &seller) const
  {
    const_cast<CInvoice *>(this)->m_Seller = seller;
  }

  void setBuyer(const string &buyer) const
  {
    const_cast<CInvoice *>(this)->m_Buyer = buyer;
  }

  void setid(const unsigned long int &id) const
  {
    const_cast<CInvoice *>(this)->m_id = id;
  }

  void setmatch(const bool match) const
  {
    const_cast<CInvoice *>(this)->m_match = match;
  }
  bool match(void) const
  {
    return m_match;
  }

  unsigned int amount(void) const
  {
    return m_Amount;
  }

  double vat(void) const
  {
    return m_Vat;
  }

  unsigned long int id(void) const
  {
    return m_id;
  }

private:
  CDate m_Date;
  string m_Seller;
  string m_Buyer;
  unsigned int m_Amount;
  double m_Vat;
  unsigned long int m_id;
  bool m_match = false;
};

bool operator<(const CInvoice &a, const CInvoice &other)
{
  if (a.seller().compare(other.seller()) != 0)
    return a.seller() < other.seller();
  if (a.buyer().compare(other.buyer()) != 0)
    return a.buyer() < other.buyer();
  if (a.amount() != other.amount())
    return a.amount() < other.amount();
  if (a.vat() != other.vat())
    return a.vat() < other.vat();
  return a.date() < other.date();
}

class CSortOpt
{
public:
  static const int BY_DATE = 0;
  static const int BY_BUYER = 1;
  static const int BY_SELLER = 2;
  static const int BY_AMOUNT = 3;
  static const int BY_VAT = 4;
  static const int BY_INSERT = 5;

  CSortOpt(void)
  {
  }

  struct SortKey
  {
    int sortBy;
    bool ascending;
  };
  CSortOpt &addKey(int key, bool ascending = true)
  {
    SortKey sortKey;
    sortKey.sortBy = key;
    sortKey.ascending = ascending;
    m_sortKeys.push_back(sortKey);
    return *this;
  }
  const std::vector<SortKey> &getSortKeys() const
  {
    return m_sortKeys;
  }

private:
  vector<SortKey> m_sortKeys;
};

class CVATRegister
{
public:
  CVATRegister(void)
  {
  }

  bool registerCompany(const string &name)
  {
    string lower_name;
    lower_name = toLower(name);                 // převod písmen na lowercase
    lower_name = removeExtraSpaces(lower_name); // remove spaces

    if (companies_lowercase.empty())
    {
      companies.push_back(name);
      companies_lowercase.push_back(lower_name); // přidání do vektoru
      return true;
    }
    else
    {
      auto it = find(companies_lowercase.begin(), companies_lowercase.end(), lower_name);
      ; // najde místo kam ve vektoru companies vložit novou firmu
      if (it == companies_lowercase.end())
      {
        int index = it - companies_lowercase.begin();
        companies.insert(companies.begin() + index, name);
        companies_lowercase.insert(it, lower_name); // vložím na místo ve vektoru aby byl stále seřazen a šlo používat binární

        return true;
      }
    }

    return false;
  }

  bool addIssued(const CInvoice &x)
  {
    string buyer = x.buyer();
    string seller = x.seller();

    buyer = toLower(buyer);
    buyer = removeExtraSpaces(buyer);
    seller = toLower(seller);
    seller = removeExtraSpaces(seller);

    x.setBuyer(buyer);
    x.setSeller(seller);

    if (buyer == seller) // kontrola stejného kupujícího jako prodávajícího
    {
      return false;
    }

    auto it_buyer = find(companies_lowercase.begin(), companies_lowercase.end(), buyer);
    auto it_seller = find(companies_lowercase.begin(), companies_lowercase.end(), seller);

    if (it_seller == companies_lowercase.end() || it_buyer == companies_lowercase.end()) // společnost není registrována
    {
      return false;
    }
    if (map_issue.empty()) // mapa je prázdná
    {

      if (!(map_accepted.empty())) // jestli map_acceptedd neni prazdna tak se tam koukne jestli tam nahoddou neni stejna faktura když ano tak se nastaví flag
      {
        /* code */

        auto it_match = map_accepted.find(buyer);
        auto it_match_2 = map_accepted.find(seller);
        if (it_match != map_accepted.end() && it_match_2 != map_accepted.end())
        {
          auto &faktura_match = it_match->second;
          auto &faktura_match_2 = it_match_2->second;

          auto faktura_change = faktura_match.find(x);
          auto faktura_change_2 = faktura_match_2.find(x);
          if (faktura_change != faktura_match.end() && faktura_change_2 != faktura_match_2.end())
          {
            faktura_change->setmatch(true);
            faktura_change_2->setmatch(true);
            x.setmatch(true);
          }
        }
      }

      x.setid(id); // nastavení id faktury
      id++;
      map_issue[seller].insert(x); // vložení do mapy
      map_issue[buyer].insert(x);  // vložení do mapy
      return true;
    }

    auto it = map_issue.find(seller); // hledám prodavajícího v mapě

    if (it != map_issue.end()) // je tam prodavající
    {
      const set<CInvoice> &invoiceSet = it->second;
      auto it2 = invoiceSet.find(x);
      if (it2 != invoiceSet.end()) // není v setu
      {
        return false;
      }
    }

    if (!(map_accepted.empty())) // jestli map_acceptedd neni prazdna tak se tam koukne jestli tam nahoddou neni stejna faktura když ano tak se nastaví flag
    {
      auto it_match = map_accepted.find(buyer);
      auto it_match_2 = map_accepted.find(seller);
      if (it_match != map_accepted.end() && it_match_2 != map_accepted.end())
      {
        auto &faktura_match = it_match->second;
        auto &faktura_match_2 = it_match_2->second;

        auto faktura_change = faktura_match.find(x);
        auto faktura_change_2 = faktura_match_2.find(x);
        if (faktura_change != faktura_match.end() && faktura_change_2 != faktura_match_2.end())
        {
          faktura_change->setmatch(true);
          faktura_change_2->setmatch(true);
          x.setmatch(true);
        }
      }
    }

    x.setid(id); // nastavení id faktury
    id++;
    map_issue[seller].insert(x); // vložení do mapy
    map_issue[buyer].insert(x);  // vložení do mapy
    return true;
  }

  bool addAccepted(const CInvoice &x)
  {
    string buyer = x.buyer();
    string seller = x.seller();

    buyer = toLower(buyer);
    buyer = removeExtraSpaces(buyer);
    seller = toLower(seller);
    seller = removeExtraSpaces(seller);

    x.setBuyer(buyer);
    x.setSeller(seller);

    if (buyer == seller) // kontrola stejného kupujícího jako prodávajícího
    {
      return false;
    }

    auto it_buyer = find(companies_lowercase.begin(), companies_lowercase.end(), buyer);
    auto it_seller = find(companies_lowercase.begin(), companies_lowercase.end(), seller);

    if (it_seller == companies_lowercase.end() || it_buyer == companies_lowercase.end()) // společnost není registrována
    {
      return false;
    }
    if (map_accepted.empty()) // mapa je prázdná
    {
      if (!(map_issue.empty())) // jestli map_issue neni prazdna tak se tam koukne jestli tam nahoddou neni stejna faktura když ano tak se nastaví flag
      {
        auto it_match = map_issue.find(buyer);
        auto it_match_2 = map_issue.find(seller);
        if (it_match != map_issue.end() && it_match_2 != map_issue.end())
        {
          auto &faktura_match = it_match->second;
          auto &faktura_match_2 = it_match_2->second;

          auto faktura_change = faktura_match.find(x);
          auto faktura_change_2 = faktura_match_2.find(x);

          if (faktura_change != faktura_match.end() && faktura_change_2 != faktura_match_2.end())
          {
            faktura_change->setmatch(true);
            faktura_change_2->setmatch(true);
            x.setmatch(true);
          }
        }
      }

      x.setid(id); // nastavení id faktury
      id++;
      map_accepted[buyer].insert(x);  // vložení do mapy
      map_accepted[seller].insert(x); // vložení do mapy
      return true;
    }

    auto it = map_accepted.find(buyer); // hledám kupujícího v mapě

    if (it != map_accepted.end()) // není tam kupující
    {
      const set<CInvoice> &invoiceSet = it->second;
      auto it2 = invoiceSet.find(x);
      if (it2 != invoiceSet.end()) // není v setu
      {
        return false;
      }
    }

    if (!(map_issue.empty())) // jestli map_issue neni prazdna tak se tam koukne jestli tam nahoddou neni stejna faktura když ano tak se nastaví flag
    {
      auto it_match = map_issue.find(buyer);
      auto it_match_2 = map_issue.find(seller);
      if (it_match != map_issue.end() && it_match_2 != map_issue.end())
      {
        auto &faktura_match = it_match->second;
        auto &faktura_match_2 = it_match_2->second;

        auto faktura_change = faktura_match.find(x);
        auto faktura_change_2 = faktura_match_2.find(x);

        if (faktura_change != faktura_match.end() && faktura_change_2 != faktura_match_2.end())
        {
          faktura_change->setmatch(true);
          faktura_change_2->setmatch(true);
          x.setmatch(true);
        }
      }
    }

    x.setid(id); // nastavení id faktury
    id++;
    map_accepted[buyer].insert(x);  // vložení do mapy
    map_accepted[seller].insert(x); // vložení do mapy
    return true;
  }

  bool delIssued(const CInvoice &x)
  {
    string seller = x.seller();
    string buyer = x.buyer();

    seller = toLower(seller);
    seller = removeExtraSpaces(seller);

    buyer = toLower(buyer);
    buyer = removeExtraSpaces(buyer);

    x.setBuyer(buyer);
    x.setSeller(seller);

    if (map_issue.empty())
    {
      return false;
    }

    auto it = map_issue.find(seller);
    auto it_buyer = map_issue.find(buyer);

    if (it == map_issue.end() || it_buyer == map_issue.end()) // seller not found in the map
    {
      return false;
    }

    auto &invoiceSet = it->second;
    auto it2 = invoiceSet.find(x);

    auto &invoiceSet_buyyer = it_buyer->second;
    auto it2_buyer = invoiceSet_buyyer.find(x);

    if (it2 == invoiceSet.end()) // invoice not found in the set
    {
      return false;
    }

    auto it_match_1 = map_accepted.find(seller); // najiti v accepted
    auto it_match_2 = map_accepted.find(buyer);  // najiti v accepted

    if (it_match_1 != map_accepted.end() && it_match_2 != map_accepted.end() && it2->match() == true) // tady nastavim v accepted u techto faktur false ve sparovani
    {
      auto &invoiceSet_match_1 = it_match_1->second;
      auto it2_match_1 = invoiceSet_match_1.find(x);

      auto &invoiceSet_match_2 = it_match_2->second;
      auto it2_match_2 = invoiceSet_match_2.find(x);

      it2_match_1->setmatch(false);
      it2_match_2->setmatch(false);
    }

    // pridavam jak ke kupujicimu tak k prodavajicimu proto je musím oboje oddstranit
    invoiceSet.erase(it2);              // delete the invoice from the set
    invoiceSet_buyyer.erase(it2_buyer); // delete the invoice from the set
    return true;
  }

  bool delAccepted(const CInvoice &x)
  {
    string buyer = x.buyer();
    string seller = x.seller();

    buyer = toLower(buyer);
    buyer = removeExtraSpaces(buyer);

    seller = toLower(seller);
    seller = removeExtraSpaces(seller);

    x.setBuyer(buyer);
    x.setSeller(seller);

    if (map_accepted.empty())
    {
      return false;
    }

    auto it = map_accepted.find(buyer);
    auto it_seller = map_accepted.find(seller);

    if (it == map_accepted.end() || it_seller == map_accepted.end()) // seller not found in the map
    {
      return false;
    }

    auto &invoiceSet = it->second;
    auto &invoiceSet_seller = it_seller->second;
    auto it2 = invoiceSet.find(x);
    auto it2_seller = invoiceSet_seller.find(x);

    if (it2 == invoiceSet.end()) // invoice not found in the set
    {
      return false;
    }

    auto it_match_1 = map_issue.find(seller); // najiti v issue
    auto it_match_2 = map_issue.find(buyer);  // najiti v issue

    if (it_match_1 != map_issue.end() && it_match_2 != map_issue.end() && it2->match() == true) // tady nastavim v accepted u techto faktur false ve sparovani
    {
      auto &invoiceSet_match_1 = it_match_1->second;
      auto it2_match_1 = invoiceSet_match_1.find(x);

      auto &invoiceSet_match_2 = it_match_2->second;
      auto it2_match_2 = invoiceSet_match_2.find(x);

      it2_match_1->setmatch(false);
      it2_match_2->setmatch(false);
    }

    // pridavam jak ke kupujicimu tak k prodavajicimu proto je musím oboje oddstranit

    invoiceSet.erase(it2);               // delete the invoice from the set
    invoiceSet_seller.erase(it2_seller); // delete the invoice from the set
    return true;
  }

  list<CInvoice> unmatched(const string &company, const CSortOpt &sortBy) const
  {
    list<CInvoice> result;
    string original_name;
    string tmp_name;

    string string_company_lower = company;
    string_company_lower = toLower(string_company_lower);
    string_company_lower = removeExtraSpaces(string_company_lower); // nazev firmy upraven tak aby se dalo vyhledavat

    auto it_company = find(companies_lowercase.begin(), companies_lowercase.end(), string_company_lower); // najde originalni jmeno firmy ktera je na vstupu
    if (it_company != companies_lowercase.end())                                                          // najiti originalního jmena
    {
      int index = it_company - companies_lowercase.begin();
      original_name = companies[index];
      // použijte original_name podle potřeby
    }

    if (map_issue.empty() && map_accepted.empty()) // neni tam zadna faktura vrati prazdny list
    {
      return result;
    }

    auto it_issue = map_issue.find(string_company_lower);       // faktury v issue
    auto it_accepted = map_accepted.find(string_company_lower); // faktury v acceptedd
    if (it_issue != map_issue.end())                            // seller not found in the map
    {
      auto &invoiceSet = it_issue->second; // faktury kde se objevuje daná firma
      for (auto &it2_issue : invoiceSet)   // proje vsechny faktury
      {
        if (it2_issue.match() == false)
        {
          CInvoice final_faktura(it2_issue);
          if (final_faktura.buyer() == string_company_lower)
          {
            final_faktura.setBuyer(original_name);
            auto it_originalname = find(companies_lowercase.begin(), companies_lowercase.end(), it2_issue.seller()); // najde originalni jmeno firmy ktera je na vstupu
                 if (it_originalname != companies_lowercase.end())
            {
            int index = it_originalname - companies_lowercase.begin();
            final_faktura.setSeller(companies[index]);
            }
          }
          else
          {
            final_faktura.setSeller(original_name);
            auto it_originalname = find(companies_lowercase.begin(), companies_lowercase.end(), it2_issue.buyer()); // najde originalni jmeno firmy ktera je na vstupu
               if (it_originalname != companies_lowercase.end())
            {
            int index = it_originalname - companies_lowercase.begin();
            final_faktura.setBuyer(companies[index]);
            }
          }

          result.push_back(final_faktura); // pridaní do listu
        }
      }
    }
    if (it_accepted != map_accepted.end())
    {

      auto &invoiceSet_accepted = it_accepted->second;

      for (auto &it2_accepted : invoiceSet_accepted)
      {
        if (it2_accepted.match() == false)
        {
          CInvoice final_faktura(it2_accepted);
          if (final_faktura.buyer() == string_company_lower) // zmena na originialní jmeno co je na vstupu
          {
            final_faktura.setBuyer(original_name);
            auto it_originalname = find(companies_lowercase.begin(), companies_lowercase.end(), it2_accepted.seller()); // najde originalni jmeno firmy ktera je na vstupu

            if (it_originalname != companies_lowercase.end())
            {
              int index = it_originalname - companies_lowercase.begin();
              final_faktura.setSeller(companies[index]);
            }
          }
          else
          {
            final_faktura.setSeller(original_name);
            auto it_originalname = find(companies_lowercase.begin(), companies_lowercase.end(), it2_accepted.buyer()); // najde originalni jmeno firmy ktera je na vstupu
            if (it_originalname != companies_lowercase.end())
            {
              int index = it_originalname - companies_lowercase.begin();
              final_faktura.setBuyer(companies[index]);
            }
          }

          result.push_back(final_faktura); // pridaní do listu
        }
      }
    }

    if (sortBy.getSortKeys().empty()) // pokud je to prázný seřadím to podle toho jak to přislo
    {
      result.sort([](const CInvoice &a, const CInvoice &b)
                  { return a.id() < b.id(); });
    }
    else // je tam nějaké kriterium tak se to muže seřait
    {
      /* code */
      result.sort([this, &sortBy](const CInvoice &a, const CInvoice &b)
                  { return compareInvoices(a, b, sortBy); }); // řazení pole kriterii
    }

    for (auto it : result) // test print
    {
      cout << "-_-" << it.seller() << " " << it.buyer() << " " << it.amount() << " " << it.vat() << endl; // test print
    }
    cout << "-----------------------------------------" << endl;
    return result;
  }

  void printRegistredcompanies() // test print
  {
    for (auto a : companies_lowercase)
    {
      cout << a << endl;
    }

    cout << "-----------------" << endl;
  }

private:
  vector<string> companies_lowercase;   // vektor zaregistrovaných firem seřezených dle jména -> jmeno je v malých písmenách a bez přebytečnýh mezer
  vector<string> companies;             // vektor zaregistrovaných firem seřezených dle jména
  map<string, set<CInvoice>> map_issue; // u každého kliče(firmy) jsou všechny faktury se vyskytuje at už jako kupující nebo proddávající
  map<string, set<CInvoice>> map_accepted;
  unsigned long int id = 0;
  bool compareInvoices(const CInvoice &a, const CInvoice &b, const CSortOpt &sortBy) const
  {

    for (const auto &key : sortBy.getSortKeys())
    {
      switch (key.sortBy)
      {
      case CSortOpt::BY_DATE:
        if (a.date() < b.date())
          return key.ascending;
        if (b.date() < a.date())
          return !key.ascending;
        break;
      case CSortOpt::BY_BUYER:
        if (a.buyer() < b.buyer())
          return key.ascending;
        if (b.buyer() < a.buyer())
          return !key.ascending;
        break;
      case CSortOpt::BY_SELLER:
        if (a.seller() < b.seller())
          return !key.ascending;
        if (b.seller() < a.seller())
          return key.ascending;
        break;
      case CSortOpt::BY_AMOUNT:
        if (a.amount() < b.amount())
          return key.ascending;
        if (b.amount() < a.amount())
          return !key.ascending;
        break;
      case CSortOpt::BY_VAT:
        if (a.vat() < b.vat())
          return key.ascending;
        if (b.vat() < a.vat())
          return !key.ascending;
        break;
      }
    }

    // Pokud jsou faktury stejné podle všech řadicích kritérií, ponechá se původní pořadí
    return a.id() < b.id();
  }

  string toLower(string str) const // převod stringu na malá písmena
  {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
              { return tolower(c); });
    return str;
  }

  string removeExtraSpaces(const string &str) const // odstraní přebytečné mezery
  {
    string result;
    bool space;

    if (str.length() == 1)
    {
      return str;
    }

    if (str[0] == ' ')
    {
      space = true;
    }
    else
    {
      space = false;
    }

    for (char c : str)
    {
      if (isspace(c))
      {
        if (!space)
        {
          space = true;
          result += ' ';
        }
      }
      else
      {
        space = false;
        result += c;
      }
    }

    if (result.back() == ' ')
    {
      result.pop_back();
    }

    return result;
  }
};

#ifndef __PROGTEST__
bool equalLists(const list<CInvoice> &a, const list<CInvoice> &b)
{
  if (a.size() != b.size()) // If the sizes of the lists don't match, they can't be equal.
    return false;

  auto ita = a.begin();
  auto itb = b.begin();
  while (ita != a.end() && itb != b.end()) // Iterate over the lists and compare each element.
  {
    if (!(ita->date().year() == itb->date().year() && ita->date().month() == itb->date().month() && ita->date().day() == itb->date().day() && ita->buyer() == itb->buyer() && ita->seller() == itb->seller() && ita->amount() == itb->amount() && ita->vat() == itb->vat()))
      return false;
    ++ita;
    ++itb;
  }

  return true;
}

int main(void)
{
  CVATRegister r;
  // assert(r.registerCompany("FirSt Company"));
  // assert(r.registerCompany("Second     Company"));
  // // assert(r.registerCompany("ThirdCompany, Ltd."));
  // // assert(r.registerCompany("Third Company, Ltd."));
  // // assert(!r.registerCompany(""));
  // // assert(!r.registerCompany(" Third  Company,  Ltd.  "));
  // // r.unmatched("first company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true));
  // // r.unmatched("Second Company ", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true));
  // // r.unmatched("Secssond Company ", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true));

  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 20330, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2030, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 202220, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2020, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 20220, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 211100, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 21100, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2010, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200000, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 20000, 30));
  // r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2000, 30));

  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 20330, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2030, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 202220, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2020, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 20220, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 211100, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 21100, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2010, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200000, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 20000, 30));
  // r.addAccepted(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 2000, 30));

  // // // cout << " test--------------" << endl;
  // r.unmatched("first company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true));
  // r.unmatched("Second Company ", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true));
  // r.unmatched("Secssond Company ", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_SELLER, true));
  // r.unmatched("se", CSortOpt());
  // // cout << " konec test -------------" << endl;

  assert(r.registerCompany("first Company"));
  assert(r.registerCompany("Second     Company"));
  assert(r.registerCompany("ThirdCompany, Ltd."));
  assert(r.registerCompany("Third Company, Ltd."));
  assert(!r.registerCompany("Third Company, Ltd."));
  assert(!r.registerCompany(" Third  Company,  Ltd.  "));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
  assert(r.addIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
  assert(!r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
  assert(!r.addIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
  assert(!r.addIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));

  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, false).addKey(CSortOpt::BY_DATE, false)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));

  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000)}));

  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_VAT, true).addKey(CSortOpt::BY_AMOUNT, true).addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));

  assert(equalLists(r.unmatched("First Company", CSortOpt()),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000)}));

  assert(equalLists(r.unmatched("second company", CSortOpt().addKey(CSortOpt::BY_DATE, false)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400, 34.000000)}));
  assert(equalLists(r.unmatched("last company", CSortOpt().addKey(CSortOpt::BY_VAT, true)),
                    list<CInvoice>{}));

  assert(r.addAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
  assert(r.addAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(r.addAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));

  assert(!r.delIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "A First Company", "Second Company ", 200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Hand", 200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 1200, 30)));
  assert(!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 200, 130)));
  assert(r.delIssued(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company", 200, 30)));

  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));

  assert(r.delAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));
  assert(r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));

  assert(equalLists(r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true)),
                    list<CInvoice>{
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 20.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 30.000000),
                        CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300, 32.000000)}));

  // cout << " ------------------------test--------------" << endl;
  // r.unmatched("First Company", CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(CSortOpt::BY_DATE, true));
  // cout << "-------------------------- konec test -------------" << endl;
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
