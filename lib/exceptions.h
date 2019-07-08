#ifndef LIB_EXCEPTIONS_H_1906
#define LIB_EXCEPTIONS_H_1906

#include <exception>

class Error : std::exception
{
  public:
    Error(const char *msg) : msg_(msg) {}
    Error(const std::string &msg) : msg_(msg) {}
    const char *what() { return msg_.c_str(); }

  private:
    std::string msg_;
};

#endif
