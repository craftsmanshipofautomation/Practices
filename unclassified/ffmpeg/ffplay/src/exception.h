#include <exception>
class AVException : public std::exception
{
    public:
    AVException(const char* s)
    : s_(s)
    {
    }
    const char* what () noexcept
    {
        return s_;
    }
    private:
        const char* s_;
};