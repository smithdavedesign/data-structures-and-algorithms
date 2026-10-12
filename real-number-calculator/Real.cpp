// Project: Real Number precision
// File: Real.cpp
// Author: David Smith
// Description: Arbitrary-precision signed decimals as digit vectors.
//
// Rewritten in 2026. The 2017 version (about 1,800 lines, in git history) printed a stray
// NUL byte before every sum and difference and dropped a fraction digit, read past the end
// of a vector while adding, never multiplied (it returned the left operand), had a stub
// for division and crashed comparing whole numbers. This version does the arithmetic on
// unsigned digit strings and is checked against Python's exact Decimal by
// tests/fuzz.py (`make test`).

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include "Real.h"

using namespace std;

// ---------- unsigned decimal strings: no sign, no leading zeros, "0" for zero ----------

static string Trim (const string & s)
{
  size_t i = s.find_first_not_of ('0');
  return i == string::npos ? "0" : s.substr (i);
}

static int CompareU (const string & a, const string & b)
{
  if (a.size () != b.size ())
    return a.size () < b.size () ? -1 : 1;
  return a < b ? -1 : a > b ? 1 : 0;
}

static string AddU (const string & a, const string & b)
{
  string out;
  int carry = 0;
  for (int i = (int) a.size () - 1, j = (int) b.size () - 1; i >= 0 || j >= 0 || carry; i--, j--)
    {
      int sum = carry + (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0);
      out += char ('0' + sum % 10);
      carry = sum / 10;
    }
  reverse (out.begin (), out.end ());
  return Trim (out);
}

static string SubU (const string & a, const string & b)   // requires a >= b
{
  string out;
  int borrow = 0;
  for (int i = (int) a.size () - 1, j = (int) b.size () - 1; i >= 0; i--, j--)
    {
      int d = (a[i] - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);
      borrow = d < 0;
      out += char ('0' + (d + 10) % 10);
    }
  reverse (out.begin (), out.end ());
  return Trim (out);
}

static string MulU (const string & a, const string & b)
{
  vector<int> acc (a.size () + b.size (), 0);
  for (int i = (int) a.size () - 1; i >= 0; i--)
    for (int j = (int) b.size () - 1; j >= 0; j--)
      acc[i + j + 1] += (a[i] - '0') * (b[j] - '0');
  for (int k = (int) acc.size () - 1; k > 0; k--)
    {
      acc[k - 1] += acc[k] / 10;
      acc[k] %= 10;
    }
  string out;
  for (int d : acc)
    out += char ('0' + d);
  return Trim (out);
}

static string DivU (const string & a, const string & b)   // floor(a / b), b != 0
{
  string quotient, rest = "0";
  for (char c : a)
    {
      rest = Trim (rest + c);
      int q = 0;
      while (CompareU (rest, b) >= 0)
        {
          rest = SubU (rest, b);
          q++;
        }
      quotient += char ('0' + q);
    }
  return Trim (quotient);
}

static string Pow10 (int n)
{
  return "1" + string (n, '0');
}

// ---------- representation ----------

Real Real::fromScaled (bool neg, const string & digits, int scale)
{
  string d = Trim (digits);
  if ((int) d.size () <= scale)
    d = string (scale - d.size () + 1, '0') + d;
  Real r;
  string whole = Trim (d.substr (0, d.size () - scale));
  r.front.assign (whole.begin (), whole.end ());
  r.back.assign (d.end () - scale, d.end ());
  r.negative = neg && !r.isZero ();
  return r;
}

string Real::scaled (int scale) const
{
  string s (front.begin (), front.end ());
  s.append (back.begin (), back.end ());
  s.append (scale - back.size (), '0');
  return Trim (s);
}

bool Real::isZero () const
{
  for (char c : front)
    if (c != '0')
      return false;
  for (char c : back)
    if (c != '0')
      return false;
  return true;
}

int Real::compareMagnitude (const Real & other) const
{
  int scale = max (precision (), other.precision ());
  return CompareU (scaled (scale), other.scaled (scale));
}

// ---------- construction ----------

Real::Real () : front (1, '0'), negative (false)
{
}

Real::~Real ()
{
}

Real::Real (const Real & other) : front (other.front), back (other.back), negative (other.negative)
{
}

Real::Real (const string & text) : Real ()
{ // [+-]digits[.digits]; anything else reads as 0
  size_t i = 0;
  bool neg = false;
  if (i < text.size () && (text[i] == '-' || text[i] == '+'))
    neg = text[i++] == '-';
  string whole, fraction;
  while (i < text.size () && isdigit ((unsigned char) text[i]))
    whole += text[i++];
  if (i < text.size () && text[i] == '.')
    for (i++; i < text.size () && isdigit ((unsigned char) text[i]); i++)
      fraction += text[i];
  *this = fromScaled (neg, whole + fraction, (int) fraction.size ());
}

Real::Real (int n) : Real ((long long) n)
{
}

Real::Real (long long n) : Real ()
{
  // via unsigned, so LLONG_MIN works too
  unsigned long long m = n < 0 ? 0ULL - (unsigned long long) n : (unsigned long long) n;
  *this = fromScaled (n < 0, to_string (m), 0);
}

Real::Real (double d) : Real ()
{
  if (!std::isfinite (d))
    throw domain_error ("Real: not a finite number");
  // A double is a binary fraction, so its decimal expansion ends; %.1100f prints all of it.
  char buf[1500];
  snprintf (buf, sizeof buf, "%.1100f", d);
  string s (buf);
  size_t last = s.find_last_not_of ('0');
  s.erase (s[last] == '.' ? last + 2 : last + 1);   // keep one fraction digit: 12345.0
  *this = Real (s);
}

Real::Real (double d, int digits) : Real (d)
{
  round (digits);
}

Real & Real::operator = (const Real & other)
{
  front = other.front;
  back = other.back;
  negative = other.negative;
  return *this;
}

void Real::set_Neg (bool neg)
{
  negative = neg && !isZero ();
}

// ---------- precision ----------

int Real::precision () const
{
  return (int) back.size ();
}

void Real::round (int digits)
{
  if (digits < 0)
    digits = 0;
  if (digits >= precision ())
    {
      back.resize (digits, '0');
      return;
    }
  // drop the extra digits, then add one in the last kept place if the first dropped is >= 5
  int drop = precision () - digits;
  string all = scaled (precision ());
  bool up = false;
  if ((int) all.size () >= drop)
    up = all[all.size () - drop] >= '5';
  string head = (int) all.size () > drop ? all.substr (0, all.size () - drop) : "0";
  if (up)
    head = AddU (head, "1");
  *this = fromScaled (negative, head, digits);
}

// ---------- I/O ----------

string Real::toString () const
{
  string s = negative ? "-" : "";
  s.append (front.begin (), front.end ());
  s += '.';
  if (back.empty ())
    s += '0';
  else
    s.append (back.begin (), back.end ());
  return s;
}

ostream & operator << (ostream & outs, const Real & real)
{
  return outs << real.toString ();
}

istream & operator >> (istream & ins, Real & real)
{
  string token;
  if (ins >> token)
    real = Real (token);
  return ins;
}

// ---------- comparison ----------

bool Real::operator < (const Real & other) const
{
  if (negative != other.negative)
    return negative;
  int c = compareMagnitude (other);
  return negative ? c > 0 : c < 0;
}

bool Real::operator > (const Real & other) const
{
  return other < *this;
}

bool Real::operator <= (const Real & other) const
{
  return !(other < *this);
}

bool Real::operator >= (const Real & other) const
{
  return !(*this < other);
}

bool Real::operator == (const Real & other) const
{
  return negative == other.negative && compareMagnitude (other) == 0;
}

bool Real::operator != (const Real & other) const
{
  return !(*this == other);
}

// ---------- arithmetic ----------

Real Real::operator + (const Real & other) const
{
  int scale = max (precision (), other.precision ());
  string a = scaled (scale), b = other.scaled (scale);
  if (negative == other.negative)
    return fromScaled (negative, AddU (a, b), scale);
  // different signs: subtract the smaller magnitude from the larger, keep the larger's sign
  if (CompareU (a, b) >= 0)
    return fromScaled (negative, SubU (a, b), scale);
  return fromScaled (other.negative, SubU (b, a), scale);
}

Real Real::operator - (const Real & other) const
{
  Real flipped (other);
  flipped.set_Neg (!other.negative);
  return *this + flipped;
}

Real Real::operator * (const Real & other) const
{
  string a = scaled (precision ()), b = other.scaled (other.precision ());
  return fromScaled (negative != other.negative, MulU (a, b), precision () + other.precision ());
}

Real Real::operator / (const Real & other) const
{
  if (other.isZero ())
    throw domain_error ("Real: division by zero");
  // q = a / b to `scale` fraction digits, rounded half away from zero:
  // (a * 10^(sb + scale + 1) / 10^sa) / b, then drop the extra digit
  int scale = max (precision (), other.precision ()) + DIVISION_DIGITS;
  int sa = precision (), sb = other.precision ();
  string numerator = MulU (scaled (sa), Pow10 (sb + scale + 1));
  string q = DivU (DivU (numerator, Pow10 (sa)), other.scaled (sb));
  string head = q.size () > 1 ? q.substr (0, q.size () - 1) : "0";
  if (q.back () >= '5')
    head = AddU (head, "1");
  return fromScaled (negative != other.negative, head, scale);
}

Real Real::operator += (const Real & other)
{
  return *this = *this + other;
}

Real Real::operator -= (const Real & other)
{
  return *this = *this - other;
}

Real Real::operator *= (const Real & other)
{
  return *this = *this * other;
}

Real Real::operator /= (const Real & other)
{
  return *this = *this / other;
}
