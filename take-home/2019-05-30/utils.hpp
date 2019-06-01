#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <sstream>
#include <iostream>
#include <string>

template<typename T>
std::string to_string(const T& t)
{
   std::ostringstream os;
   os << t;
   return os.str();
}

template <typename T, int Row, int Column>
class Matrix;
template<typename T, int R, int C>
std::string to_string(const Matrix<T, R, C>& mat);



template <typename T>
class Triple;
template<typename T>
std::string to_string(const Triple<T>& triple);



#endif