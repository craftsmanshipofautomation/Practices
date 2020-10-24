template<typename T>
void print(const T& t, bool newline) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, " "));
    if (newline)
        std::cout << std::endl;
}

template<typename T>
void print(const T& t, int N, bool newline) {
    std::copy(t.cbegin(), t.cbegin() + N, std::ostream_iterator<typename T::value_type>(std::cout, " "));
    if (newline)
        std::cout << std::endl;
}

template<typename T>
void print(T* p, size_t sz)
{
    for (size_t i = 0; i < sz; ++i)
    {
        std::cout << p[i] << " ";
    }
    std::cout << std::endl;
}

