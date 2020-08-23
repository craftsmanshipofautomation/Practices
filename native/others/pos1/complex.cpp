#include "complex.hpp"
#include <sstream>

Complex Complex::operator+(const Complex& rhs) const
{
   Complex ret;
   ret.real_ = this->real_ + rhs.real_;
   ret.imag_ = this->imag_ + rhs.imag_;
   return ret;
}

Complex Complex::operator*(const Complex& rhs) const
{
   Complex ret;
   ret.real_ = this->real_ * rhs.real_ - this->imag_ * rhs.imag_;
   ret.imag_ = this->real_ * rhs.imag_ + this->imag_ * rhs.real_;
   return ret;
}

Complex& Complex::operator=(const Complex& rhs)
{
   real_ = rhs.real_;
   imag_ = rhs.imag_;
   return *this;
}


std::string to_string(const Complex& complex)
{
   std::ostringstream os;
   os << complex.real_ << " + " << complex.imag_ << "i";
   return os.str();
}