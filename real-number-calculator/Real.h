// Project: Real Number precision
// File: Real.h
// Author: David Smith
// Description: The Real Class: signed decimal numbers of any length and precision.
//
// A value is stored as a sign, its integer digits (front) and its fraction digits (back).
// The fraction keeps the precision it was given ("1800.80" stays 1800.80), sums and
// differences keep the larger precision of the two, products the sum of both, and
// quotients DIVISION_DIGITS more than the larger.

#ifndef REAL_H
#define REAL_H
#include <iostream>
#include <string>
#include <vector>

class Real
{
 public:
  Real();
  ~Real();
  Real( const Real & );
  Real( const std::string & );
  Real( int );
  Real( long long );
  Real( double );            // the double's exact binary value, every digit of it
  Real( double, int );       // ... rounded to that many fraction digits
  void round (int );         // round half away from zero to that many fraction digits
  int precision () const;    // number of fraction digits
  std::string toString() const;

  // I/O stream
  friend std::istream & operator >> (std::istream & ins, Real & );
  friend std::ostream & operator << (std::ostream & outs, const Real & );

  // Operator overloads
  bool operator <  (const Real & ) const;
  bool operator >  (const Real & ) const;
  bool operator <= (const Real & ) const;
  bool operator >= (const Real & ) const;
  bool operator == (const Real & ) const;
  bool operator != (const Real & ) const;
  Real operator +  (const Real & ) const;
  Real operator -  (const Real & ) const;
  Real operator *  (const Real & ) const;
  Real operator /  (const Real & ) const;   // throws std::domain_error on division by zero
  Real & operator  = (const Real & );
  Real operator += (const Real & );
  Real operator -= (const Real & );
  Real operator *= (const Real & );
  Real operator /= (const Real & );
  void set_Neg(bool);

  static const int DIVISION_DIGITS = 10;

 private:
  // value = (negative ? -1 : 1) * digits / 10^scale, digits without leading zeros
  static Real fromScaled (bool negative, const std::string & digits, int scale);
  std::string scaled (int scale) const;   // all digits, padded to `scale` fraction digits
  int compareMagnitude (const Real & ) const;
  bool isZero () const;

  std::vector <char> front;   // integer digits, most significant first; "0" for zero
  std::vector <char> back;    // fraction digits
  bool negative;
};

#endif
