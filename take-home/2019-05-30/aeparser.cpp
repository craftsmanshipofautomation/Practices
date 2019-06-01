#include "aeparser.hpp"
#include <cmath>
#define UNARY(sym) \
   if (op == #sym) \
      return lhs sym rhs;

float AEParser::Calculate(float lhs, float rhs, std::string &op)
{
   UNARY(+);
   UNARY(-);
   UNARY(*);
   UNARY(/);
}

float AEParser::Calculate(float uni, std::string &op)
{
   if (op == "sin")
      return sin(uni);

   if (op == "cos")
      return cos(uni);
}

int AEParser::Classify(std::string &op)
{
   // temperary handling!
   if (op.size() == 3)
      return 2;
   else
      return 1;
}

float AEParser::Parse()
{
   auto iter = ae_.begin();

   while (iter != ae_.end())
   {
      if (*iter == '(')
      {
         pare_stack_.push('(');
         ++iter;
         continue;
      }
      if (*iter == ')' && pare_stack_.top() == '(')
      {
         pare_stack_.pop();
         // get operation
         curr_op_ = op_stack_.top();
         op_stack_.pop();
         int op_type = Classify(curr_op_);
         if (op_type == 1)
         {

            rhs_ = float_stack_.top();
            float_stack_.pop();
            lhs_ = float_stack_.top();
            float_stack_.pop();
            result_ = Calculate(lhs_, rhs_, curr_op_);
         }
         else if (op_type == 2)
         {
            result_ = float_stack_.top();
            float_stack_.pop();
            result_ = Calculate(result_, curr_op_);
         }
         float_stack_.push(result_);
         ++iter;
         continue;
      }
      if (isdigit(*iter))
      {
         // get the whole digit
         std::string digits(1, *iter);
         while (isdigit(*++iter))
            digits += *iter;
         if (*iter == '.')
         {
            digits += *iter;
            while (isdigit(*++iter))
               digits += *iter;
         }
         float_stack_.push(std::stof(digits));
         // iter arrive at the head of non digits
         continue;
      }
      if (*iter == 's')
      {
         //assume there is no illegal input
         // s must imply sin
         iter += 3;
         op_stack_.push("sin");
         continue;
      }
      if (*iter == 'c')
      {

         iter += 3;
         op_stack_.push("cos");
         continue;
      }
      if (*iter == '+' ||
          *iter == '-' ||
          *iter == '*' ||
          *iter == '/')
      {
         std::string op(1, *iter);
         op_stack_.push(op);
         ++iter;
         continue;
      }
      if (*iter == ' ')
      {
         while (*++iter == ' ')
            ;
         continue;
      }
   }
   return result_;
}