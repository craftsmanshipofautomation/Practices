#include "complex.hpp"
#include "matrix.hpp"
#include "triple.hpp"
#include <iostream>

using namespace std;

int main()
{
   cout << "------- matrix of float ---------------" << endl;
   
   Matrix<float, 2, 3> mf23{1.2, 0.5, 2.7, -1.2, 3.0, 1.1};
   Matrix<float, 3, 2> mf32{3.3, 1.6, 2.3, 1, 1, 0};
   Matrix<float, 2, 2> result = mf23 * mf32;
   cout << to_string(mf23) << endl;;
   cout << to_string(mf32) << endl;;   
   cout << to_string(result) << endl;;


   cout << "------- matrix of complex ---------------" << endl;   
   Matrix<Complex, 2, 3> mc23{{1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6}, {7.7, 8.8}, {9.9, 10.1}, {11.2, 12.3}};
   Matrix<Complex, 3, 2> mc32{{1.1, 2.2}, {3.3, 4.4}, {5.5, 6.6}, {7.7, 8.8}, {9.9, 10.1}, {11.2, 12.3}};   
   Matrix<Complex, 2, 2> complex_result = mc23 * mc32;
   cout << to_string(mc23) << endl;;
   cout << to_string(mc32) << endl;;   
   cout << to_string(complex_result) << endl;;
   
   
   cout << "------- matrix of triple ---------------" << endl;   
   Matrix<Triple<float>, 2, 3> mt23{{1.0, 2, 3}, {3, 4, 5}, {5, 6, 7}, {7, 8, 9}, {9, 10.234234, 11}, {11, 12, 13}};
   Matrix<Triple<float>, 3, 2> mt32{{1, 2, 3.6}, {3, 4, 5}, {5, 6, 7}, {7, 8, 9}, {9, 10.234234, 11}, {11, 12, 13}};
   
   Matrix<Triple<float>, 2, 2> triple_result = mt23 * mt32;
   cout << to_string(mt23) << endl;;
   cout << to_string(mt32) << endl;;   
   cout << to_string(triple_result) << endl;;

}

