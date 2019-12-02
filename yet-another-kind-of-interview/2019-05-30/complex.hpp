#ifndef COMPLEX_H
#define COMPLEX_H

#include <string>

class Complex
{
   friend std::string to_string(const Complex& complex);
   public:
   
   Complex() {}
   ~Complex() {}   
   Complex(float r, float i): real_(r), imag_(i) {}
   Complex(const Complex& rhs): real_(rhs.real_), imag_(rhs.imag_) {}
   Complex& operator=(const Complex&);
   Complex operator+(const Complex&) const;
   Complex operator*(const Complex&) const;
   
   private:
      float real_;
      float imag_;
};
std::string to_string(const Complex& complex);


#endif