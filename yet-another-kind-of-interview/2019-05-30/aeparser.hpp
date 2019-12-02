#ifndef AEPARSER_H
#define AEPARSER_H

#include <string>
#include <stack>
class AEParser
{
   public:
   AEParser(const std::string & ae): ae_(ae) {}

   float Parse();
   
   private:
   int Classify(std::string & op);
   float Calculate(float lhs, float rhs, std::string& op);
   float Calculate(float uni, std::string& op);   
   
   
   
   private:
      std::string ae_;
      std::stack<char> pare_stack_;
      std::stack<float> float_stack_;
      std::stack<std::string> op_stack_;
      float result_, lhs_, rhs_;
      std::string curr_op_;
      

};





#endif