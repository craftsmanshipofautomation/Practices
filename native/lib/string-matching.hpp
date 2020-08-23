#ifndef STRING_MATCHING_HPP_
#define STRING_MATCHING_HPP_


std::vector<size_t> native_pattern_search(const std::string& text, const std::string& pat);

// pi: [0, offset1] -> [o, offset2]
std::vector<int> compute_kmp_pi(const std::string& pat);
std::vector<size_t> kmp_search(const std::string& text, const std::string& pat);


#endif