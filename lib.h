#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <deque>

#ifdef _GLIBCXX_VECTOR
#if defined(_BASIC_STRING_H) && defined(_GLIBCXX_SSTREAM)
	template<class T> std::istream& operator>>(std::istream& istm, std::vector<T>& vec) {
		std::string s;
		if (std::getline(istm, s)) {
			T tmp;
			std::istringstream iss(std::move(s));
			while (iss >> tmp)
				vec.push_back(tmp);
		}
		return istm;
	}
#endif // _BASIC_STRING_H && _GLIBCXX_SSTREAM
	template<class T> std::ostream& operator<<(std::ostream& ostm, std::vector<T>& vec) {
		for (const auto& r : vec)
			ostm << r << ' ';
		return ostm;
	}
#endif // _GLIBCXX_VECTOR