#ifndef ARRAY_2
#define ARRAY_2

template <typename T, int R, int C>
T **Create2DArray()
{
   T **data_ = new T*[R];
   for (int i = 0; i < R; ++i)
   {
      data_[i] = new T[C];
   }
   return data_;
}

template <typename T, int R, int C>
void Delete2DArray(T **&data)
{
   for (int i = 0; i < R; ++i)
   {
      delete[] data[i];
   }
   delete[] data;
   data = nullptr;
}


template <typename T, int R, int C>
void Copy2DArray(T**& lhs, T**& rhs)
{

   for (int i = 0; i < R; ++i)
   {
      for (int j = 0; j < C; ++j)
      {
         lhs[i][j] = rhs[i][j];
      }
   }
}

#endif