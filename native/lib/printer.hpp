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

