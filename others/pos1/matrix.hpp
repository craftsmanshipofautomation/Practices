#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <initializer_list>
#include "array2.hpp"
#include "utils.hpp"

template <typename T, int Row, int Column>
class Matrix
{
   friend std::string to_string<T, Row, Column>(const Matrix<T, Row, Column>&);
public:
   Matrix();
   ~Matrix();
   Matrix(const Matrix &);   
   Matrix(Matrix &&);
   Matrix(const std::initializer_list<T>&);   
   Matrix &operator=(Matrix &&);
   Matrix &operator=(const Matrix &);   
   T& operator()(int r, int c);

private:
   T **data_;
};

template<typename T, int R, int C>
std::string to_string(const Matrix<T, R, C>& mat)
{
   std::ostringstream os;
   for (int r = 0; r < R; ++r)
   {
      for (int c = 0; c < C; ++c)
      {
         //std::cout << float(mat.data_[r][c]) << std::endl;
         os << to_string(mat.data_[r][c]) << ", ";
      }
      os << "\n";
   }
   return os.str();
}


template<typename T, int M, int N, int P>
Matrix<T, M, P> operator*(Matrix<T, M, N>& lhs, Matrix<T, N, P>& rhs)
{
   Matrix<T, M, P> ret;
   for (int r = 0; r < M; ++r)
   {
      for (int c = 0; c < P; ++c)
      {
         T temp{};
         for (int i = 0; i < N; ++i)
         {
            temp = temp + lhs(r, i) * rhs(i, c);
         } 
         ret(r, c) = temp;
      }
   }
   return ret;
}


template <typename T, int R, int C>
Matrix<T, R, C>::Matrix()
{
   data_ = Create2DArray<T, R, C>();
}

template <typename T, int R, int C>
Matrix<T, R, C>::~Matrix()
{
   Delete2DArray<T, R, C>(data_);
}

template <typename T, int R, int C>
Matrix<T, R, C>::Matrix(const std::initializer_list<T>& list)
{
   data_ = Create2DArray<T, R, C>();
   auto iter = list.begin();
   for (int r = 0; r < R; ++r)
   {
      for (int c = 0; c < C; ++c)
      {
         if (iter == list.end())
            goto end;
         data_[r][c] = *iter++;
      }
   }
   
   end:
      return;
}

template <typename T, int R, int C>
T& Matrix<T, R, C>::operator()(int r, int c)
{
   assert(r < R);
   assert(!(r < 0));
   assert(c < C);
   assert(!(c < 0));

   return data_[r][c];
}

template <typename T, int R, int C>
Matrix<T, R, C>::Matrix(const Matrix &rhs)
{
   data_ = Create2DArray<T, R, C>();   
   Copy2DArray<T, R, C>(data_, rhs.data_);
}

template <typename T, int R, int C>
Matrix<T, R, C>::Matrix(Matrix &&rhs)
{
   data_ = Create2DArray<T, R, C>();   
   Copy2DArray<T, R, C>(data_, rhs.data_);
}

template <typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::operator=(const Matrix &rhs)
{
   Copy2DArray<T, R, C>(data_, rhs.data_);
   return *this;
}

template <typename T, int R, int C>
Matrix<T, R, C>& Matrix<T, R, C>::operator=(Matrix &&rhs)
{
   Copy2DArray<T, R, C>(data_, rhs.data_);
   return *this;
}

#endif