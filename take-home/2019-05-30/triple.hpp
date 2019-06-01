#ifndef TRIPLE_HPP
#define TRIPLE_HPP

#include <string>
#include <sstream>
#include "utils.hpp"



template <typename T>
class Triple
{
   friend std::string to_string<T>(const Triple<T>& triple);
   public:
   Triple() {}
   ~Triple() {}   
   Triple(T&& a, T&& b, T&& c): a0_(a), a1_(b), a2_(c) {}
   Triple(const Triple& rhs) : a0_(rhs.a0_), a1_(rhs.a1_), a2_(rhs.a2_) {}
   Triple& operator=(const Triple&);
   Triple operator*(const Triple&);
   Triple operator+(const Triple&);
   std::string str();
   private:
      T a0_;
      T a1_;
      T a2_;
};

template<typename T>
std::string to_string(const Triple<T>& triple)
{
   std::ostringstream os;
   os << "(" << to_string(triple.a0_) << ", "
             << to_string(triple.a1_) << ", "
             << to_string(triple.a2_) << ")";
   return os.str();
}

template <typename T>
Triple<T>& Triple<T>::operator=(const Triple<T>& rhs)
{
   a0_ = rhs.a0_;
   a1_ = rhs.a1_;
   a2_ = rhs.a2_;
   return *this;
}

template <typename T>
Triple<T> Triple<T>::operator*(const Triple<T>& rhs)
{
   Triple<T> ret;
   ret.a0_ = a0_ + rhs.a0_;
   ret.a1_ = a1_ + rhs.a1_;
   ret.a2_ = a2_ + rhs.a2_;
   return ret;
}

template <typename T>
Triple<T> Triple<T>::operator+(const Triple<T>& rhs)
{
   Triple<T> ret;
   ret.a0_ = a0_ * rhs.a0_;
   ret.a1_ = a1_ * rhs.a1_;
   ret.a2_ = a2_ * rhs.a2_;
   return ret;
}

#endif