#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include "expression.h"
using namespace std;
using namespace literals;
using CValue = variant<monostate, double, string>;

constexpr unsigned SPREADSHEET_CYCLIC_DEPS = 0x01;
constexpr unsigned SPREADSHEET_FUNCTIONS = 0x02;
constexpr unsigned SPREADSHEET_FILE_IO = 0x04;
constexpr unsigned SPREADSHEET_SPEED = 0x08;
constexpr unsigned SPREADSHEET_PARSER = 0x10;
#endif /* __PROGTEST__ */
using namespace std;
int global = 0;

#include <stdexcept>
#include <cctype>
#include <string>
#include <string_view>
#include <cmath>

using namespace std;

#include <stdexcept>
#include <cctype>
#include <string>
#include <string_view>
#include <cmath>

using namespace std;
// Class representing a position in a spreadsheet
class CPos
{
public:
  // Constructor taking a string view representing the position
  CPos(string_view str)
  {
    // Check if position is absolute (starting with '$')
    if (!str.empty() && str[0] == '$')
    {
      absolute_column = true;
      str.remove_prefix(1); // Remove the first character '$'
    }
    size_t i = 0;
    // Find the position of the first non-letter character (the end of the column part)
    while (i < str.size() && isalpha(str[i]))
    {
      ++i;
    }

    // Check if row is absolute (ending with '$')
    if (str[i] == '$')
    {
<<<<<<< HEAD
      std::string newStr = std::string(str.substr(0, i)) + std::string(str.substr(i + 1));
      str = std::string_view(newStr.data(), newStr.size());
=======
      string newStr = string(str.substr(0, i)) + string(str.substr(i + 1));
      str = string_view(newStr.data(), newStr.size());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      absolute_row = true;
    }

    // Check if at least one letter (column) and one digit (row) were found
    if (i == 0 || i == str.size() || !isdigit(str[i]))
    {
      posIsGood = false;
    }
    else
    {
      // Extract the column part
      string columnStr = string(str.substr(0, i));
<<<<<<< HEAD
      transform(columnStr.begin(), columnStr.end(), columnStr.begin(), ::toupper); // Convert column string to lowercase
=======
      transform(columnStr.begin(), columnStr.end(), columnStr.begin(), ::toupper); // Convert column string to uppercase
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      columnStr_ = columnStr;

      // Convert the column string to a number
      column_ = columnToNumber(columnStr_);

      // Extract the row part and convert it to an integer
      row_ = stoi(string(str.substr(i)));
    }
  }

  // Comparison operators
  bool operator==(const CPos &other) const
  {
    return column_ == other.column_ && row_ == other.row_;
  }

  bool operator<(const CPos &other) const
  {
    return (column_ < other.column_) || (column_ == other.column_ && row_ < other.row_);
  }

  bool operator>(const CPos &other) const
  {
    return !(*this < other);
  }

<<<<<<< HEAD
=======
  // Getter methods
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string getColumnStr() const { return columnStr_; }
  int getColumn() const { return column_; }
  int getRow() const { return row_; }
  bool getAbsolute_column() const { return absolute_column; }
  bool getAbsolute_row() const { return absolute_row; }
  bool getPosIsGood() const { return posIsGood; }

  // Method to convert row string to integer
  int toInt() const { return row_; }

  // Method to update column with offset
  string getColumnWithOffset(int offset)
  {
    int new_column_ = column_ + offset;
    if (column_ <= 0)
    {
      // Handle special cases if needed
    }
    return numberToColumn(new_column_);
  }

  // Method to apply offset to column and row
  void applyOffset(int offset_w, int offset_h)
  {
    if (!absolute_column)
    {
      column_ += offset_w;
      if (column_ <= 0)
      {
        // Handle special cases if needed
      }
      columnStr_ = numberToColumn(column_);
    }

    if (!absolute_row)
    {
      row_ += offset_h;
      if (row_ <= 0)
      {
        // Handle special cases if needed
      }
    }
  }

  bool getAbsolute_column() const { return absolute_column; }
  bool getAbsolute_row() const { return absolute_row; }
  bool getPosIsGood() const { return posIsGood; }

  // Method to convert row string to integer
  int toInt() const { return row_; }

  // Method to update column with offset
  string getColumnWithOffset(int offset)
  {
    int new_column_ = column_ + offset;
    if (column_ <= 0)
    {
    }

    return numberToColumn(new_column_);
  }
  void applyOffset(int offset_w, int offset_h)
  {
    if (!absolute_column)
    {
      column_ += offset_w;
      if (column_ <= 0)
      {
      }
      columnStr_ = numberToColumn(column_);
    }

    if (!absolute_row)
    {
      row_ += offset_h;
      if (row_ <= 0)
      {
      }
    }
  }

private:
<<<<<<< HEAD
  bool posIsGood = true;
  bool absolute_column = false;
  bool absolute_row = false;
  string columnStr_;
  int column_;
  int row_;
=======
  bool posIsGood = true;    // Flag indicating if the position is valid
  bool absolute_column = false; // Flag indicating if column is absolute
  bool absolute_row = false;    // Flag indicating if row is absolute
  string columnStr_;        // String representation of column
  int column_;              // Numeric representation of column
  int row_;                 // Row number
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4

  // Helper function to convert Excel-style column string to number
  int columnToNumber(const string &columnStr) const
  {
    int column = 0;
    for (char c : columnStr)
    {
      column *= 26;
      column += (c - 'A' + 1);
    }
    return column;
  }

  // Helper function to convert column number to Excel-style column string
  string numberToColumn(int column) const
  {
    string result;
    while (column > 0)
    {
      int remainder = (column - 1) % 26;
      result = char('A' + remainder) + result;
      column = (column - remainder - 1) / 26;
    }
    return result;
  }
};

// Overload of the addition operator for CValue
CValue operator+(CValue left, CValue right)
{
  // Addition for double and double
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return get<double>(left) + get<double>(right);
  }
  // Concatenation for string and string
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return get<string>(left) + get<string>(right);
  }
  // Conversion and concatenation for double and string
  else if (holds_alternative<double>(left) && holds_alternative<string>(right))
  {
    string result = to_string(get<double>(left));
    result += get<string>(right);
    return result;
  }
  // Concatenation for string and double
  else if (holds_alternative<string>(left) && holds_alternative<double>(right))
  {
    string result = get<string>(left);
    result += to_string(get<double>(right));
    return result;
  }
<<<<<<< HEAD
  return monostate{}; // Pro případ, že operandy nejsou ani double, ani string
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the subtraction operator for CValue
CValue operator-(CValue left, CValue right)
{
<<<<<<< HEAD
=======
  // Subtraction for double and double
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  return (holds_alternative<double>(left) && holds_alternative<double>(right)) ? CValue(get<double>(left) - get<double>(right)) : monostate{};
}

// Overload of the multiplication operator for CValue
CValue operator*(CValue left, CValue right)
{
<<<<<<< HEAD
=======
  // Multiplication for double and double
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  return (holds_alternative<double>(left) && holds_alternative<double>(right)) ? CValue(get<double>(left) * get<double>(right)) : monostate{};
}

// Overload of the division operator for CValue
CValue operator/(CValue left, CValue right)
{
  // Division for double and double
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    if (get<double>(right) == 0)
    {
<<<<<<< HEAD
      return monostate{}; // Pro případ, že operandy nejsou ani double, ani string
=======
      return monostate{}; // Return default value if divisor is zero
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    }
    else
    {
      return CValue(get<double>(left) / get<double>(right));
    }
  }
<<<<<<< HEAD
  return monostate{}; // Pro případ, že operandy nejsou ani double, ani string
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the equality operator for CValue
CValue operator==(CValue left, CValue right)
{
  // Equality comparison for double and double, string and string
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return (get<double>(left) == get<double>(right) ? (double)1 : (double)0);
  }
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return get<string>(left) == get<string>(right) ? (double)1 : (double)0;
  }
<<<<<<< HEAD
  return monostate{}; // Pro ostatní případy, kdy typy nejsou kompatibilní pro porovnání
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the inequality operator for CValue
CValue operator!=(CValue left, CValue right)
{
  // Inequality comparison for double and double, string and string
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return get<double>(left) != get<double>(right) ? 1.0 : 0.0;
  }
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return get<string>(left) != get<string>(right) ? 1.0 : 0.0;
  }
<<<<<<< HEAD
  return monostate{}; // Pro ostatní případy, kdy typy nejsou kompatibilní pro porovnání
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the less-than operator for CValue
CValue operator<(CValue left, CValue right)
{
  // Less-than comparison for double and double, string and string
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return (get<double>(left) < get<double>(right) ? (double)1 : (double)0);
  }
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return (get<string>(left) < get<string>(right) ? (double)1 : (double)0);
  }
<<<<<<< HEAD
  return monostate{};
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the greater-than operator for CValue
CValue operator>(CValue left, CValue right)
{
  // Greater-than comparison for double and double, string and string
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return (get<double>(left) > get<double>(right) ? (double)1 : (double)0);
  }
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return (get<string>(left) > get<string>(right) ? (double)1 : (double)0);
  }
<<<<<<< HEAD
  return monostate{};
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the less-than-or-equal-to operator for CValue
CValue operator<=(CValue left, CValue right)
{
  // Less-than-or-equal-to comparison for double and double, string and string
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return (get<double>(left) <= get<double>(right) ? (double)1 : (double)0);
  }
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return (get<string>(left) <= get<string>(right) ? (double)1 : (double)0);
  }
<<<<<<< HEAD
  return monostate{};
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Overload of the greater-than-or-equal-to operator for CValue
CValue operator>=(CValue left, CValue right)
{
  // Greater-than-or-equal-to comparison for double and double, string and string
  if (holds_alternative<double>(left) && holds_alternative<double>(right))
  {
    return (get<double>(left) >= get<double>(right) ? (double)1 : (double)0);
  }
  else if (holds_alternative<string>(left) && holds_alternative<string>(right))
  {
    return (get<string>(left) >= get<string>(right) ? (double)1 : (double)0);
  }
<<<<<<< HEAD
  return monostate{};
=======
  return monostate{}; // Return default value for other cases
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
}

// Define binary subtraction operator for negation operation
CValue operator-(CValue value)
{
  // Check if the value is a double
  if (holds_alternative<double>(value))
  {
    // Negate the double value
    double result = -get<double>(value);
    return CValue(result);
  }
  else
  {
    // Return default value if the value is not a double
    return CValue(monostate{});
  }
}

// Base class representing a node in the Abstract Syntax Tree (AST).
class CAST
{
public:
  // Pure virtual function to solve the cell represented by this node.
<<<<<<< HEAD
  virtual ~CAST() {}
  virtual CValue SolveCell(const map<CPos, shared_ptr<CAST>> &) = 0;
  virtual string print() = 0;
  virtual void setNewOffset(int, int) = 0;
  virtual std::shared_ptr<CAST> clone() const = 0;
=======
  virtual ~CAST() {}                                                 // Destructor
  virtual CValue SolveCell(const map<CPos, shared_ptr<CAST>> &) = 0; // Method to solve the cell
  virtual string print() = 0;                                        // Method to print the node
  virtual void setNewOffset(int, int) = 0;                           // Method to set new offset
  virtual shared_ptr<CAST> clone() const = 0;                        // Method to clone the node
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
};

// Class representing a node in the AST that holds a constant value.
class CASTValue : public CAST
{
public:
  CValue Value; // Value held by this node

  // Constructor to initialize the value of the node.
  CASTValue(CValue Value_) : Value(Value_) {}

  // Method to solve the cell represented by this node, returning the stored value.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    return Value;
  }
<<<<<<< HEAD
=======

  // Method to print the value of the node.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string print() override
  {
    // Depending on the type of value, format accordingly
    if (holds_alternative<monostate>(Value))
    {
<<<<<<< HEAD
      return "Monostate_Value";
=======
      return "Monostate_Value"; // Return description for monostate
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    }
    else if (holds_alternative<double>(Value))
    {
      return to_string(get<double>(Value)); // Return double value as string
    }
    else if (holds_alternative<string>(Value))
    {
      // Format string value, escaping special characters
      string string_value = get<string>(Value);
      for (size_t i = 0; i < string_value.size(); ++i)
      {
        if (string_value[i] == '"' || string_value[i] == '\\')
        {
          string_value.insert(i, 1, string_value[i]);
          i++; // Skip the newly inserted character
        }
        else if (string_value[i] == '\n')
        {
          string_value.replace(i, 1, "\\n");
          i += 2; // Skip the newly inserted characters
        }
      }
      return "\"" + string_value + "\""; // Return formatted string
    }
    else
    {
      return ""; // Default empty string
    }
  }
<<<<<<< HEAD
  void setNewOffset(int offset_w, int offset_h)
  {
    offset_w = offset_w;
    offset_h = offset_h;
  }
  std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTValue>(Value);
=======

  // Method to set new offset (unused in current implementation)
  void setNewOffset(int offset_w, int offset_h)
  {
    offset_w = offset_w; // Set new offset width
    offset_h = offset_h; // Set new offset height
  }

  // Method to clone the node
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node
    return make_shared<CASTValue>(Value);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs addition operation.
class CASTAdd : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTAdd(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

  // Method to solve the cell represented by this node, performing addition of left and right operands.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

    // Perform addition of values
    return leftValue + rightValue;
  }

  // Method to print the addition operation.
  string print() override
  {
    string add_str = "(" + Left->print() + "+" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTAdd>(Left->clone(), Right->clone());
  }
};
=======
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4

  // Method to set new offset for operands.
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTAdd>(Left->clone(), Right->clone());
  }
};
// Class representing a subtraction operation node in the Abstract Syntax Tree (AST).
class CASTSub : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTSub(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

  // Method to resolve the subtraction operation.
  // It evaluates the left and right operands and performs the subtraction.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Resolve the left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

    // Perform subtraction of values
    return leftValue - rightValue;
  }

  // Method to print the subtraction operation.
  string print() override
  {
    string add_str = "(" + Left->print() + "-" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    return std::make_shared<CASTSub>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTSub>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a multiplication operation node in the Abstract Syntax Tree (AST).
class CASTMul : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTMul(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

  // Method to resolve the multiplication operation.
  // It evaluates the left and right operands and performs the multiplication.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Resolve the left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

    // Perform multiplication of values
    return leftValue * rightValue;
  }

  // Method to print the multiplication operation.
  string print() override
  {
    string add_str = "(" + Left->print() + "*" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    return std::make_shared<CASTMul>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTMul>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a division operation node in the Abstract Syntax Tree (AST).
class CASTDiv : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTDiv(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

  // Method to resolve the division operation.
  // It evaluates the left and right operands and performs the division.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Resolve the left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

    // Perform division of values
    return leftValue / rightValue;
  }

  // Method to print the division operation.
  string print() override
  {
    string add_str = "(" + Left->print() + "/" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    return std::make_shared<CASTDiv>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTDiv>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs exponentiation operation.
class CASTPow : public CAST
{
public:
  shared_ptr<CAST> Base;     // Base operand
  shared_ptr<CAST> Exponent; // Exponent operand

  // Constructor to initialize the base and exponent operands.
  CASTPow(shared_ptr<CAST> base, shared_ptr<CAST> exponent)
      : Base(base), Exponent(exponent) {}

  // Method to solve the cell represented by this node, performing exponentiation of base to the exponent.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve base and exponent operands
    CValue baseValue = Base->SolveCell(AST_cells);
    CValue exponentValue = Exponent->SolveCell(AST_cells);

    // Check if baseValue and exponentValue are doubles
    if (holds_alternative<double>(baseValue) && holds_alternative<double>(exponentValue))
    {
      // Calculate the exponentiation of doubles
      double base = get<double>(baseValue);
      double exponent = get<double>(exponentValue);
      double result = pow(base, exponent);
      return result;
    }
    else
    {
      // Handle other cases if needed
      // For example, if baseValue or exponentValue is not a double, or if they hold different types
      // You can add error handling or support for other types here
      return CValue(); // Return a default value for now
    }
  }

  // Method to print the exponentiation operation.
  string print() override
  {
    string add_str = "(" + Base->print() + "^" + Exponent->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Base->setNewOffset(offset_w, offset_h);
    Exponent->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    return std::make_shared<CASTPow>(Base->clone(), Exponent->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTPow>(Base->clone(), Exponent->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs negation operation.
class CASTNeg : public CAST
{
public:
  shared_ptr<CAST> Operand; // Operand to be negated

  // Constructor to initialize the operand.
  CASTNeg(shared_ptr<CAST> operand) : Operand(operand) {}

  // Method to solve the cell represented by this node, performing negation of the operand.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve the operand
    CValue operandValue = Operand->SolveCell(AST_cells);

    // Perform negation of value
    return -operandValue;
  }

  // Method to print the negation operation.
  string print() override
  {
    string add_str = "(-" + Operand->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Operand->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    return std::make_shared<CASTNeg>(Operand->clone());
  }
};

class CASTEq : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTEq(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

  // Method to solve the cell represented by this node, performing addition of left and right operands.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

    // Perform addition of values
    return leftValue == rightValue;
  }
  string print() override
  {
    string add_str = "(" + Left->print() + "=" + Right->print() + ")";
    return add_str;
  }
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTEq>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTNeg>(Operand->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs equality operation.
class CASTEq : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTEq(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

  // Method to solve the cell represented by this node, performing equality check between left and right operands.
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

    // Perform equality check
    return leftValue == rightValue;
  }

  // Method to print the equality operation.
  string print() override
  {
    string add_str = "(" + Left->print() + "=" + Right->print() + ")";
    return add_str;
  }

  // Method to set new offset for operands.
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTEq>(Left->clone(), Right->clone());
  }
};

// Class representing a node in the AST that performs inequality operation.
class CASTNe : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTNe(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

<<<<<<< HEAD
  // Method to solve the cell represented by this node, performing addition of left and right operands.
=======
  // Method to solve the cell represented by this node, performing inequality check between left and right operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

<<<<<<< HEAD
    // Perform addition of values
    return leftValue != rightValue;
  }
=======
    // Perform inequality check
    return leftValue != rightValue;
  }

  // Method to print the inequality operation.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string print() override
  {
    string add_str = "(" + Left->print() + "<>" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTNe>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTNe>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs less than operation.
class CASTLt : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTLt(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

<<<<<<< HEAD
  // Method to solve the cell represented by this node, performing addition of left and right operands.
=======
  // Method to solve the cell represented by this node, performing less than check between left and right operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

<<<<<<< HEAD
    // Perform addition of values
    return leftValue < rightValue;
  }
=======
    // Perform less than check
    return leftValue < rightValue;
  }

  // Method to print the less than operation.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string print() override
  {
    string add_str = "(" + Left->print() + "<" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTLt>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTLt>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs less than or equal to operation.
class CASTLe : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTLe(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

<<<<<<< HEAD
  // Method to solve the cell represented by this node, performing addition of left and right operands.
=======
  // Method to solve the cell represented by this node, performing less than or equal to check between left and right operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

<<<<<<< HEAD
    // Perform addition of values
    return leftValue <= rightValue;
  }
=======
    // Perform less than or equal to check
    return leftValue <= rightValue;
  }

  // Method to print the less than or equal to operation.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string print() override
  {
    string add_str = "(" + Left->print() + "<=" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTLe>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTLe>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs greater than operation.
class CASTGt : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTGt(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

<<<<<<< HEAD
  // Method to solve the cell represented by this node, performing addition of left and right operands.
=======
  // Method to solve the cell represented by this node, performing greater than check between left and right operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

<<<<<<< HEAD
    // Perform addition of values
    return leftValue > rightValue;
  }
=======
    // Perform greater than check
    return leftValue > rightValue;
  }

  // Method to print the greater than operation.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string print() override
  {
    string add_str = "(" + Left->print() + ">" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTGt>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTGt>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that performs greater than or equal to operation.
class CASTGe : public CAST
{
public:
  shared_ptr<CAST> Left;  // Left operand
  shared_ptr<CAST> Right; // Right operand

  // Constructor to initialize the left and right operands.
  CASTGe(shared_ptr<CAST> left, shared_ptr<CAST> right)
      : Left(left), Right(right) {}

<<<<<<< HEAD
  // Method to solve the cell represented by this node, performing addition of left and right operands.
=======
  // Method to solve the cell represented by this node, performing greater than or equal to check between left and right operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Solve left and right operands
    CValue leftValue = Left->SolveCell(AST_cells);
    CValue rightValue = Right->SolveCell(AST_cells);

<<<<<<< HEAD
    // Perform addition of values
    return leftValue >= rightValue;
  }
=======
    // Perform greater than or equal to check
    return leftValue >= rightValue;
  }

  // Method to print the greater than or equal to operation.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  string print() override
  {
    string add_str = "(" + Left->print() + ">=" + Right->print() + ")";
    return add_str;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for operands.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    Left->setNewOffset(offset_w, offset_h);
    Right->setNewOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTGe>(Left->clone(), Right->clone());
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTGe>(Left->clone(), Right->clone());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};

// Class representing a node in the AST that represents a cell reference.
class CASTReference : public CAST
{
public:
  CPos ReferencePos; // Position of the cell in AST_cells

  // Default constructor
  CASTReference() = default;

  // Constructor to initialize ReferencePos
  CASTReference(const CPos &referencePos) : ReferencePos(referencePos) {}

  // Implementation of SolveCell method for CASTReference class
  CValue SolveCell(const map<CPos, shared_ptr<CAST>> &AST_cells) override
  {
    // Check if a cell with the given position exists in AST_cells
    if (AST_cells.count(ReferencePos) > 0)
    {
      // If yes, get the cell value
      auto ast = AST_cells.at(ReferencePos);
<<<<<<< HEAD
      global++;
      if (global > 10000)
      {
       return CValue(); 
      }
      
      // Vyvolání metody SolveCell na této buňce
=======
      // Call SolveCell method on this cell
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      return ast->SolveCell(AST_cells);
      
    }
    else
    {
      // Cell does not exist, return default value or raise an error
      return CValue(); // Or raise an error
    }
  }

  // Method to print the cell reference.
  string print() override
  {
    string strRef;
    if (ReferencePos.getAbsolute_column())
      strRef = "$";
    strRef = strRef + ReferencePos.getColumnStr();
    if (ReferencePos.getAbsolute_row())
      strRef += "$";
    strRef += to_string(ReferencePos.getRow());
    return strRef;
  }
<<<<<<< HEAD
=======

  // Method to set new offset for the reference.
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  void setNewOffset(int offset_w, int offset_h)
  {
    ReferencePos.applyOffset(offset_w, offset_h);
  }
<<<<<<< HEAD
  virtual std::shared_ptr<CAST> clone() const override
  {
    // Vytvoření hluboké kopie
    return std::make_shared<CASTReference>(ReferencePos);
=======

  // Method to clone the node.
  virtual shared_ptr<CAST> clone() const override
  {
    // Create a deep copy of the node.
    return make_shared<CASTReference>(ReferencePos);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }
};
// Class Cbuilder, derived from CExprBuilder, responsible for building the Abstract Syntax Tree (AST) from parsed expressions.

class Cbuilder : public CExprBuilder
{
public:
  // Constructor taking a map of cell positions and their corresponding AST nodes.

  Cbuilder(const map<CPos, shared_ptr<CAST>> &cells_) : AST_cells(cells_) {}

  // Method for implementing addition operation.
  void opAdd() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

    // Create a new node for addition operation
    auto addNode = make_shared<CASTAdd>(operand1, operand2);

    // Add operands as children to the addition node
    addNode->Left = operand1;
    addNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(addNode);
  }

  // Method for implementing subtraction operation.
  void opSub() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

    // Create a new node for subtraction operation
    auto subNode = make_shared<CASTSub>(operand1, operand2);

    // Add operands as children to the subtraction node
    subNode->Left = operand1;
    subNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(subNode);
  }

  // Method for implementing multiplication operation.
  void opMul() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

    // Create a new node for multiplication operation
    auto mulNode = make_shared<CASTMul>(operand1, operand2);

    // Add operands as children to the multiplication node
    mulNode->Left = operand1;
    mulNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(mulNode);
  }

  // Method for implementing division operation.
  void opDiv() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

    // Create a new node for division operation
    auto divNode = make_shared<CASTDiv>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
  }

  // Method for implementing exponentiation operation.
  void opPow() override
  {
    // Pop two operands from the stack
    auto exponent = stackFromParser.top();
    stackFromParser.pop();
    auto base = stackFromParser.top();
    stackFromParser.pop();

    // Create a new node for exponentiation operation
    auto powNode = make_shared<CASTPow>(base, exponent);

    // Add operands as children to the exponentiation node
    powNode->Base = base;
    powNode->Exponent = exponent;

    // Push the new node back to the stack
    stackFromParser.push(powNode);
  }

  // Method for implementing negation operation.
  void opNeg() override
  {
    // Pop the operand from the stack
    auto operand = stackFromParser.top();
    stackFromParser.pop();

    // Create a new node for negation operation
    auto negNode = make_shared<CASTNeg>(operand);

    // Set the operand for the negation node
    negNode->Operand = operand;

    // Push the new node back to the stack
    stackFromParser.push(negNode);
  }

  // Method for implementing equality operation.
  void opEq() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

<<<<<<< HEAD
    // Create a new node for division operation
    auto divNode = make_shared<CASTEq>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
=======
    // Create a new node for equality operation
    auto eqNode = make_shared<CASTEq>(operand1, operand2);

    // Add operands as children to the equality node
    eqNode->Left = operand1;
    eqNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(eqNode);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }

  // Method for implementing inequality operation.
  void opNe() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

<<<<<<< HEAD
    // Create a new node for division operation
    auto divNode = make_shared<CASTNe>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
=======
    // Create a new node for inequality operation
    auto neNode = make_shared<CASTNe>(operand1, operand2);

    // Add operands as children to the inequality node
    neNode->Left = operand1;
    neNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(neNode);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }

  // Method for implementing less than operation.
  void opLt() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

<<<<<<< HEAD
    // Create a new node for division operation
    auto divNode = make_shared<CASTLt>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
=======
    // Create a new node for less than operation
    auto ltNode = make_shared<CASTLt>(operand1, operand2);

    // Add operands as children to the less than node
    ltNode->Left = operand1;
    ltNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(ltNode);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }

  // Method for implementing less than or equal to operation.
  void opLe() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

<<<<<<< HEAD
    // Create a new node for division operation
    auto divNode = make_shared<CASTLe>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
=======
    // Create a new node for less than or equal to operation
    auto leNode = make_shared<CASTLe>(operand1, operand2);

    // Add operands as children to the less than or equal to node
    leNode->Left = operand1;
    leNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(leNode);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }

  // Method for implementing greater than operation.
  void opGt() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

<<<<<<< HEAD
    // Create a new node for division operation
    auto divNode = make_shared<CASTGt>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
=======
    // Create a new node for greater than operation
    auto gtNode = make_shared<CASTGt>(operand1, operand2);

    // Add operands as children to the greater than node
    gtNode->Left = operand1;
    gtNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(gtNode);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }

  // Method for implementing greater than or equal to operation.
  void opGe() override
  {
    // Pop two operands from the stack
    auto operand2 = stackFromParser.top();
    stackFromParser.pop();
    auto operand1 = stackFromParser.top();
    stackFromParser.pop();

<<<<<<< HEAD
    // Create a new node for division operation
    auto divNode = make_shared<CASTGe>(operand1, operand2);

    // Add operands as children to the division node
    divNode->Left = operand1;
    divNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(divNode);
=======
    // Create a new node for greater than or equal to operation
    auto geNode = make_shared<CASTGe>(operand1, operand2);

    // Add operands as children to the greater than or equal to node
    geNode->Left = operand1;
    geNode->Right = operand2;

    // Push the new node back to the stack
    stackFromParser.push(geNode);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
  }

  // Method for processing numerical value.
  void valNumber(double val) override
  {
    // Push the numerical value node onto the stack
    stackFromParser.push(make_shared<CASTValue>(CValue(val)));
  }

  // Method for processing string value.
  void valString(string val) override
  {
    // Push the string value node onto the stack
    stackFromParser.push(make_shared<CASTValue>(CValue(val)));
  }

  // Method for processing cell reference.
  void valReference(string val) override
  {
    // Create a position object for the cell reference
    CPos ReferencePos(val);

<<<<<<< HEAD
    // Vytvoření instance CASTReference a uložení pozice do ní
    auto reference = make_shared<CASTReference>(ReferencePos);
    // Uložení instance do zásobníku
=======
    // Create a new node for the cell reference and store the position
    auto reference = make_shared<CASTReference>(ReferencePos);

    // Insert the cell reference position into the set
    GraphForCells.insert(ReferencePos);

    // Push the cell reference node onto the stack
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    stackFromParser.push(reference);
  }

  // Method for processing range.
  void valRange(string val) override
  {
    // Currently not implemented
  }

  // Method for processing function call.
  void funcCall(string fnName, int paramCount) override
  {
    // Currently not implemented
  }

  // Method for retrieving the AST from the parser stack.
  shared_ptr<CAST> getAST()
  {
    if (stackFromParser.empty())
    {
<<<<<<< HEAD
=======
      // If the stack is empty, return a default value node
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      return make_shared<CASTValue>(CValue(monostate{}));
    }
    else
    {
<<<<<<< HEAD
      // Get AST from the stack
=======
      // Otherwise, retrieve the AST from the stack
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      auto ast = stackFromParser.top();
      stackFromParser.pop();
      return ast;
    }
<<<<<<< HEAD
  }

private:
  stack<shared_ptr<CAST>> stackFromParser;
  map<CPos, shared_ptr<CAST>> AST_cells;
  //set
=======
  }

  // Method for retrieving the graph of cells.
  set<CPos> getGraph()
  {
    return GraphForCells;
  }

private:
  stack<shared_ptr<CAST>> stackFromParser; // Stack for storing AST nodes during parsing
  map<CPos, shared_ptr<CAST>> AST_cells;   // Map of cell positions and their corresponding AST nodes
  set<CPos> GraphForCells;                 // Set for storing the graph of cells
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
};

// Class CSpreadsheet representing a spreadsheet with cells
class CSpreadsheet
{
public:
  // Static method to retrieve capabilities of the spreadsheet
  static unsigned capabilities()
  {
    return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_SPEED;
  }

  // Default constructor
  CSpreadsheet() {}

  // Method to load data into the spreadsheet from an input stream
  bool load(istream &is)
  {
    // Clear previous state
    cells_.clear();
    Cbuilder BobTheBuilder(cells_); // Parser object

    string line;
    while (getline(is, line))
    {
      // Separate line into position and content
      size_t colonPos = line.find(':');
      if (colonPos == string::npos)
      {
        return false;
      }
      string posStr = line.substr(0, colonPos);
      string content = line.substr(colonPos + 1);
      CPos loadPos(posStr);
      if (content != "=Monostate_Value")
      {
<<<<<<< HEAD

        setCell(loadPos, content);
        // cout << loadPos.getColumnStr() << loadPos.getRow() << ": " << content << endl;
      }
      else
      {
=======
        // Set cell with position and content
        setCell(loadPos, content);
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      }
    }

    return true;
  }

   // Method to save data from the spreadsheet to an output stream
  bool save(ostream &os) const
  {
    for (const auto &cell : cells_)
    {
      os << cell.first.getColumnStr() << cell.first.getRow() << ":=" << cell.second->print() << endl;
<<<<<<< HEAD
      //  cout << cell.first.getColumnStr() << cell.first.getRow() << ":=" << cell.second->print() << endl;
=======
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    }
    return true;
  }

  // Method to set content of a cell in the spreadsheet
  bool setCell(CPos pos, string contents)
  {
    if (!pos.getPosIsGood() || contents.empty())
      return false;
<<<<<<< HEAD

    Cbuilder BobTheBuilder(cells_);           // Bob the friend of Parser
    parseExpression(contents, BobTheBuilder); // call parser
=======
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4

    Cbuilder BobTheBuilder(cells_);           // Parser object
    parseExpression(contents, BobTheBuilder); // Parse the expression

    // Get AST
    auto ast = BobTheBuilder.getAST();
    auto GraphForCells = BobTheBuilder.getGraph();
    // Save AST into cells_ map
    cells_[pos] = ast;
    GraphAllcells[pos] = GraphForCells;
    return true;
  }

  // Method to get value of a cell in the spreadsheet
  CValue getValue(CPos pos)
  {
<<<<<<< HEAD
    global = 0;
    // Check if the cell exists in the cells_ map
    if (cells_.count(pos) > 0)
=======
    set<CPos> visited;

    // Perform DFS traversal to detect cycles
    if (dfs(pos, visited))
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    {
      // If a cycle is detected during traversal, return appropriate value.
      // Here, an empty value is returned for illustration purposes.
      return CValue();
    }
    else
    {
      // Check if the cell exists in the cells_ map
      if (cells_.count(pos) > 0)
      {
<<<<<<< HEAD
      
        return ast->SolveCell(cells_);
=======
        // If it does, get the cell value from the corresponding AST
        auto ast = cells_[pos];
        if (ast)
        {
          return ast->SolveCell(cells_);
        }
        else
        {
          // If the AST is null, return some default value
          return CValue();
        }
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
      }
      else
      {
        // If the cell doesn't exist in the cells_ map, also return a default value
        return CValue();
      }
    }
  }

<<<<<<< HEAD
  void copyRect(CPos dst, CPos src, int w, int h)
  {
    // cout << "Zdrojový čtverec:\n";
    vector<shared_ptr<CAST>> dataForCopy;
=======
  // Method to copy a rectangular region of cells within the spreadsheet
  void copyRect(CPos dst, CPos src, int w, int h)
  {
    vector<shared_ptr<CAST>> dataForCopy;
    vector<set<CPos>> graphForCopy;
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    for (int i = 0; i < h; ++i)
    {
      for (int j = 0; j < w; ++j)
      {
        CPos srcPos(src.getColumnWithOffset(j) + to_string(src.getRow() + i));
<<<<<<< HEAD
        // cout << srcPos.getColumnStr() << srcPos.getRow() << endl;
        // Zkontrolujte, zda je položka v mape cells_
        if (cells_.count(srcPos) > 0)
        {
          // Pokud existuje, vytvořte kopii
          shared_ptr<CAST> copy(cells_[srcPos]->clone());
          dataForCopy.push_back(copy);
        }
        else
        {
          // Pokud neexistuje, vytvořte prázdnou hodnotu
          // Pokud je CValue definováno jako varianta (variant), můžete vytvořit prázdnou hodnotu monostate
          CASTValue emptyValue{monostate{}};
          shared_ptr<CAST> emptyCopy = std::make_shared<CASTValue>(emptyValue);
          dataForCopy.push_back(emptyCopy);
        }
      }
    }
    int offset_W = dst.getColumn() - src.getColumn(); // offset width - how columns changes
    int offset_H = dst.getRow() - src.getRow();       // offset height - how rows changes

    // Zde můžete upravit offsety vektoru podle potřeby
=======
        if (cells_.count(srcPos) > 0)
        {
          // If cell exists, create a copy
          shared_ptr<CAST> copy(cells_[srcPos]->clone());
          dataForCopy.push_back(copy);
          graphForCopy.push_back(GraphAllcells[srcPos]); // Store corresponding neighbor graph
        }
        else
        {
          // If cell doesn't exist, create an empty value
          CASTValue emptyValue{monostate{}};
          shared_ptr<CAST> emptyCopy = make_shared<CASTValue>(emptyValue);
          dataForCopy.push_back(emptyCopy);
          // Add empty set to graphForCopy
          graphForCopy.push_back(set<CPos>{});
        }
      }
    }
    int offset_W = dst.getColumn() - src.getColumn(); // Offset width - how columns change
    int offset_H = dst.getRow() - src.getRow();       // Offset height - how rows change

    // Apply offsets to all elements
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    for (auto &element : dataForCopy)
    {
      element->setNewOffset(offset_W, offset_H);
    }

<<<<<<< HEAD
    // cout << "Cílový čtverec:\n";
=======
    // Apply offsets to all neighbor graphs
    for (auto &neighbors : graphForCopy)
    {
      for (auto &neighbor : neighbors)
      {
        // Cast constant reference to non-constant
        CPos &mutableNeighbor = const_cast<CPos &>(neighbor);
        // Apply offset
        mutableNeighbor.applyOffset(offset_W, offset_H);
      }
    }

    // Finally, set copies to new positions and update neighbor graphs in GraphAllcells
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
    for (int i = 0; i < h; ++i)
    {
      for (int j = 0; j < w; ++j)
      {
        CPos dstPos(dst.getColumnWithOffset(j) + to_string(dst.getRow() + i));
<<<<<<< HEAD
        // cout << dstPos.getColumnStr() << dstPos.getRow() << endl;
        if (!dataForCopy.empty())
        {
          cells_[dstPos] = dataForCopy.front();
          dataForCopy.erase(dataForCopy.begin()); // Odstraní první prvek z vektoru
=======
        if (!dataForCopy.empty())
        {
          cells_[dstPos] = dataForCopy.front();
          dataForCopy.erase(dataForCopy.begin());
          GraphAllcells[dstPos] = graphForCopy.front(); // Add updated set to GraphAllcells
          graphForCopy.erase(graphForCopy.begin());
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4
        }
      }
    }
  }

  // Method to print cell values and their references
  void printCells()
  {
    // Print cell values
    for (const auto &[pos, ast] : cells_)
    {
      cout << "Cell " << pos.getColumnStr() << pos.getRow() << ": ";
      if (ast)
      {
        auto value = getValue(pos);
        if (holds_alternative<double>(value))
        {
          cout << get<double>(value);
        }
        else if (holds_alternative<string>(value))
        {
          cout << get<string>(value);
        }
        else
        {
          cout << "Undefined";
        }
      }
      else
      {
        cout << "Undefined (AST is null)";
      }
      cout << endl;
    }
    cout << "---------------------" << endl;

    // Print cell references
    for (const auto &pair : GraphAllcells)
    {
      cout << "Cell " << pair.first.getColumnStr() << pair.first.getRow() << " is referencing: ";
      for (const auto &reference : pair.second)
      {
        cout << reference.getColumnStr() << reference.getRow() << " ";
      }
      cout << endl;
    }
  }

private:
<<<<<<< HEAD
  map<CPos, shared_ptr<CAST>> cells_;
=======
  map<CPos, shared_ptr<CAST>> cells_;      // Map of cell positions and their corresponding AST nodes
  map<CPos, set<CPos>> GraphAllcells;      // Map of cell positions and their neighboring cells
  // Method to perform DFS traversal to detect cycles in the cell references
  bool dfs(const CPos &current, set<CPos> &visited)
  {
    // If current node has already been visited, return true (cycle detected)
    if (visited.find(current) != visited.end())
    {
      return true;
    }

    // Add current node to visited nodes
    visited.insert(current);

    // Traverse all neighboring nodes
    for (const auto &neighbor : GraphAllcells[current])
    {
      if (dfs(neighbor, visited))
      {
        return true; // Cycle found
      }
    }

    // Remove current node from visited list upon recursion exit
    visited.erase(current);

    return false; // No cycle found
  }
};
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4

};
#ifndef __PROGTEST__

bool valueMatch(const CValue &r, const CValue &s)

{
  if (r.index() != s.index())
    return false;
  if (r.index() == 0)
    return true;
  if (r.index() == 2)
    return get<string>(r) == get<string>(s);
  if (isnan(get<double>(r)) && isnan(get<double>(s)))
    return true;
  if (isinf(get<double>(r)) && isinf(get<double>(s)))
    return (get<double>(r) < 0 && get<double>(s) < 0) || (get<double>(r) > 0 && get<double>(s) > 0);
  return fabs(get<double>(r) - get<double>(s)) <= 1e8 * DBL_EPSILON * fabs(get<double>(r));
}

int main()
{
  CSpreadsheet x0, x1, test1, test2;
  ostringstream oss;
  istringstream iss;
  string data;

  oss.clear();
  oss.str("");
  assert(x0.save(oss));
  data = oss.str();
  iss.clear();
  iss.str(data);
  assert(x1.load(iss));
  assert(x0.setCell(CPos("a1"), "10"));
  assert(x0.setCell(CPos("A2"), "20.5"));
  assert(x0.setCell(CPos("A3"), "3e1"));
  assert(x0.setCell(CPos("A4"), "=40"));
  assert(x0.setCell(CPos("A5"), "=5e+1"));
  assert(x0.setCell(CPos("Z1"), "=((1000+2-10*10-2)/2)"));
  assert(x0.setCell(CPos("B1"), "=A1+A2*A3"));

  assert(x0.setCell(CPos("A6"), "raw text with any characters, including a quote \" or a newline\n"));
  assert(x0.setCell(CPos("A7"), "=\"quoted string, quotes must be doubled: \"\". Moreover, backslashes are needed for C++.\""));
  assert(valueMatch(x0.getValue(CPos("A1")), CValue(10.0)));
  assert(valueMatch(x0.getValue(CPos("A2")), CValue(20.5)));
  assert(valueMatch(x0.getValue(CPos("A3")), CValue(30.0)));
  assert(valueMatch(x0.getValue(CPos("A4")), CValue(40.0)));
  assert(valueMatch(x0.getValue(CPos("A5")), CValue(50.0)));
  assert(valueMatch(x0.getValue(CPos("A6")), CValue("raw text with any characters, including a quote \" or a newline\n")));
  assert(valueMatch(x0.getValue(CPos("A7")), CValue("quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++.")));
  assert(valueMatch(x0.getValue(CPos("A8")), CValue()));
  assert(valueMatch(x0.getValue(CPos("AAAA9999")), CValue()));
  // test1 = x0;
  // oss.clear();
  // oss.str("");
  // assert(test1.save(oss));
  // data = oss.str();
  // iss.clear();
  // iss.str(data);
  // assert(test2.load(iss));
  // test1.printCells();
  // test2.printCells();
  assert(x0.setCell(CPos("B1"), "=A1+A2*A3"));
  assert(x0.setCell(CPos("B2"), "= -A1 ^ 2 - A2 / 2   "));
  assert(x0.setCell(CPos("B3"), "= 2 ^ $A$1"));
  assert(x0.setCell(CPos("B4"), "=($A1+A$2)^2"));
  assert(x0.setCell(CPos("B5"), "=B1+B2+B3+B4"));
  assert(x0.setCell(CPos("B6"), "=B1+B2+B3+B4+B5"));
  assert(valueMatch(x0.getValue(CPos("B1")), CValue(625.0)));
  assert(valueMatch(x0.getValue(CPos("B2")), CValue(-110.25)));
  assert(valueMatch(x0.getValue(CPos("B3")), CValue(1024.0)));
  assert(valueMatch(x0.getValue(CPos("B4")), CValue(930.25)));
  assert(valueMatch(x0.getValue(CPos("B5")), CValue(2469.0)));
  assert(valueMatch(x0.getValue(CPos("B6")), CValue(4938.0)));
  assert(x0.setCell(CPos("A1"), "12"));
  assert(valueMatch(x0.getValue(CPos("B1")), CValue(627.0)));
  assert(valueMatch(x0.getValue(CPos("B2")), CValue(-154.25)));
  assert(valueMatch(x0.getValue(CPos("B3")), CValue(4096.0)));
  assert(valueMatch(x0.getValue(CPos("B4")), CValue(1056.25)));
  assert(valueMatch(x0.getValue(CPos("B5")), CValue(5625.0)));
  assert(valueMatch(x0.getValue(CPos("B6")), CValue(11250.0)));
  x1 = x0;
  assert(x0.setCell(CPos("A2"), "100"));
  assert(x1.setCell(CPos("A2"), "=A3+A5+A4"));
  assert(valueMatch(x0.getValue(CPos("B1")), CValue(3012.0)));
  assert(valueMatch(x0.getValue(CPos("B2")), CValue(-194.0)));
  assert(valueMatch(x0.getValue(CPos("B3")), CValue(4096.0)));
  assert(valueMatch(x0.getValue(CPos("B4")), CValue(12544.0)));
  assert(valueMatch(x0.getValue(CPos("B5")), CValue(19458.0)));
  assert(valueMatch(x0.getValue(CPos("B6")), CValue(38916.0)));
  assert(valueMatch(x1.getValue(CPos("B1")), CValue(3612.0)));
  assert(valueMatch(x1.getValue(CPos("B2")), CValue(-204.0)));
  assert(valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
  assert(valueMatch(x1.getValue(CPos("B4")), CValue(17424.0)));
  assert(valueMatch(x1.getValue(CPos("B5")), CValue(24928.0)));
  assert(valueMatch(x1.getValue(CPos("B6")), CValue(49856.0)));
  oss.clear();
  oss.str("");
  assert(x0.save(oss));
  data = oss.str();
  iss.clear();
  iss.str(data);
  assert(x1.load(iss));
  assert(valueMatch(x1.getValue(CPos("B1")), CValue(3012.0)));
  assert(valueMatch(x1.getValue(CPos("B2")), CValue(-194.0)));
  assert(valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
  assert(valueMatch(x1.getValue(CPos("B4")), CValue(12544.0)));
  assert(valueMatch(x1.getValue(CPos("B5")), CValue(19458.0)));
  assert(valueMatch(x1.getValue(CPos("B6")), CValue(38916.0)));
  assert(x0.setCell(CPos("A3"), "4e1"));
  assert(valueMatch(x1.getValue(CPos("B1")), CValue(3012.0)));
  assert(valueMatch(x1.getValue(CPos("B2")), CValue(-194.0)));
  assert(valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
  assert(valueMatch(x1.getValue(CPos("B4")), CValue(12544.0)));
  assert(valueMatch(x1.getValue(CPos("B5")), CValue(19458.0)));
  assert(valueMatch(x1.getValue(CPos("B6")), CValue(38916.0)));
  oss.clear();
  oss.str("");
  assert(x0.save(oss));
  data = oss.str();
  for (size_t i = 0; i < min<size_t>(data.length(), 10); i++)
    data[i] ^= 0x5a;
  iss.clear();
  iss.str(data);
  assert(!x1.load(iss));
  assert(x0.setCell(CPos("D0"), "10"));
  assert(x0.setCell(CPos("D1"), "20"));
  assert(x0.setCell(CPos("D2"), "30"));
  assert(x0.setCell(CPos("D3"), "40"));
  assert(x0.setCell(CPos("D4"), "50"));
  assert(x0.setCell(CPos("E0"), "60"));
  assert(x0.setCell(CPos("E1"), "70"));
  assert(x0.setCell(CPos("E2"), "80"));
  assert(x0.setCell(CPos("E3"), "90"));
  assert(x0.setCell(CPos("E4"), "100"));
  assert(x0.setCell(CPos("F10"), "=D0+5"));
  assert(x0.setCell(CPos("F11"), "=$D0+5"));
  assert(x0.setCell(CPos("F12"), "=D$0+5"));
  assert(x0.setCell(CPos("F13"), "=$D$0+5"));
  x0.copyRect(CPos("G11"), CPos("F10"), 1, 4);
  assert(valueMatch(x0.getValue(CPos("F10")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F11")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F12")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F13")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F14")), CValue()));
  assert(valueMatch(x0.getValue(CPos("G10")), CValue()));
  assert(valueMatch(x0.getValue(CPos("G11")), CValue(75.0)));
  assert(valueMatch(x0.getValue(CPos("G12")), CValue(25.0)));
  assert(valueMatch(x0.getValue(CPos("G13")), CValue(65.0)));
  assert(valueMatch(x0.getValue(CPos("G14")), CValue(15.0)));

  x0.copyRect(CPos("G11"), CPos("F10"), 2, 4);
  oss.clear();
  oss.str("");
  assert(x0.save(oss));
  data = oss.str();
  iss.clear();
  iss.str(data);
  assert(x1.load(iss));

  assert(valueMatch(x0.getValue(CPos("F10")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F11")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F12")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F13")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("F14")), CValue()));
  assert(valueMatch(x0.getValue(CPos("G10")), CValue()));
  assert(valueMatch(x0.getValue(CPos("G11")), CValue(75.0)));
  assert(valueMatch(x0.getValue(CPos("G12")), CValue(25.0)));
  assert(valueMatch(x0.getValue(CPos("G13")), CValue(65.0)));
  assert(valueMatch(x0.getValue(CPos("G14")), CValue(15.0)));
  assert(valueMatch(x0.getValue(CPos("H10")), CValue()));
  assert(valueMatch(x0.getValue(CPos("H11")), CValue()));
  // x0.save(oss);
  assert(valueMatch(x0.getValue(CPos("H12")), CValue()));
  assert(valueMatch(x0.getValue(CPos("H13")), CValue(35.0)));
  assert(valueMatch(x0.getValue(CPos("H14")), CValue()));
  assert(x0.setCell(CPos("F0"), "-27"));
  assert(valueMatch(x0.getValue(CPos("H14")), CValue(-22.0)));
  x0.copyRect(CPos("H12"), CPos("H13"), 1, 2);
  assert(valueMatch(x0.getValue(CPos("H12")), CValue(25.0)));
  assert(valueMatch(x0.getValue(CPos("H13")), CValue(-22.0)));
  assert(valueMatch(x0.getValue(CPos("H14")), CValue(-22.0)));

  assert(x0.setCell(CPos("TEST1"), "50"));
  assert(x0.setCell(CPos("TEST2"), "50"));
  assert(x0.setCell(CPos("TEST3"), "60"));
  assert(x0.setCell(CPos("TEST4"), "60"));
  assert(x0.setCell(CPos("TEST5"), "70"));
  assert(x0.setCell(CPos("TEST6"), "70"));
  assert(x0.setCell(CPos("TESu1"), "500"));
  assert(x0.setCell(CPos("TESu2"), "500"));
  assert(x0.setCell(CPos("TESu3"), "600"));
  assert(x0.setCell(CPos("TESu4"), "600"));
  assert(x0.setCell(CPos("TESu5"), "700"));
  assert(x0.setCell(CPos("TESu6"), "700"));
  assert(!x0.setCell(CPos("TESu6"), ""));
  assert(x0.setCell(CPos("HELL666"), "=TEST1 <> TEST2"));
  assert(valueMatch(x0.getValue(CPos("TEsT1")), CValue(50.0)));
  assert(valueMatch(x0.getValue(CPos("TEST2")), CValue(50.0)));
  assert(valueMatch(x0.getValue(CPos("TEsT3")), CValue(60.0)));
  assert(valueMatch(x0.getValue(CPos("TEsT4")), CValue(60.0)));
  assert(valueMatch(x0.getValue(CPos("TEsT5")), CValue(70.0)));
  assert(valueMatch(x0.getValue(CPos("TEsT6")), CValue(70.0)));
  assert(valueMatch(x0.getValue(CPos("HELL666")), CValue(0.0)));
  x0.copyRect(CPos("abas0"), CPos("asdas999"), 2, 6);

<<<<<<< HEAD
   assert(x0.setCell(CPos("TEST100"), "=Test100+100"));
  assert(x0.setCell(CPos("TEST200"), "50"));
=======
  assert(x0.setCell(CPos("A0"), "=A1+5"));
  assert(x0.setCell(CPos("A1"), "=$A$0"));
  assert(valueMatch(x0.getValue(CPos("A0")), CValue()));
  assert(valueMatch(x0.getValue(CPos("A1")), CValue()));
  x0.copyRect(CPos("B0"), CPos("A0"), 1, 3);
  assert(valueMatch(x0.getValue(CPos("B1")), CValue()));

  assert(x0.setCell(CPos("TEST200"), "50"));
  assert(valueMatch(x0.getValue(CPos("TEST100")), CValue()));
  // assert(valueMatch(x0.getValue(CPos("TESa101")), CValue(100.0)));
>>>>>>> 3ff2c55041148a15b8a531458b64cbad0091c5f4

  x0.printCells();
  // cout << "------------ X1 ->" << endl;
  // x1.printCells();
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
