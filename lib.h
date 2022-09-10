#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <deque>
#include <array>
#include <map>
#include <cmath>

#ifdef _STL_VECTOR_H
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
#endif // _STL_VECTOR_H


#ifdef _STL_MAP_H
	template<class Key, class T> std::istream& operator>>(std::istream& istm, std::map<Key, T>& mp) {
		std::string s;
		if (std::getline(istm, s)) {
			T tmp;
			std::istringstream iss(std::move(s));
			while (iss >> tmp)
				mp.at(tmp)++;
		}
		return istm;
	}

	template<class T> std::istream& operator>><char, T>(std::istream& istm, std::map<char, T>& mp) {
		std::string s;
		if (std::getline(istm, s)) {
			for (const auto& r : s)
				mp.at(r)++;
		}
		return istm;
	}
#endif // _STL_MAP_H

#ifdef _GLIBCXX_CMATH
	// formula of area of triangle. Arguments are length of base and height.
	template<class T> double area_triangle(T base, T height) {
		return base * height / 2;
	}

	// formula of area of triangle. Arguments are length of two sides and angle(degree) between these two sides.
	template<class T> double area_triangle(T a, T b, double deg) {
		return a * b * std::sin(deg * 180 / M_PI) / 2;
	}

	// heron's formula. This function returns area of triangle. Arguments are length of three sides.
	template<class T> double heron(T a, T b, T c) {
		const auto (a + b + c) / 2;
		return std::sqrt(s * (s - a) * (s - b) * (s - c));
	}

	// factorial: n! = n * (n - 1) * ... * 1
	size_t factorial(const size_t n) {
		size_t result = 1;
		for (size_t i = 1; i < n + 1; ++i)
			result *= i;
		return result;
	}

	// permutation: n P r = n * (n - 1) * ... * (n - r + 1)
	size_t permutation(const size_t n, const size_t r) {
		size_t result = 1;
		for (size_t i = n; i > n - r; --i)
			result *= i;
		return result;
	}

	// combination: n C r = n P r / r!
	size_t combination(const size_t n, const size_t r) {
		if (r > n - r)
			return permutation(n, n - r) / factorial(n - r);
		else
			return permutation(n, r) / factorial(r);
	}

	// Euclid's algorithm. Return value is GCD of two integer.
	long long euclid(long long a, long long b) {
		while (a >= 1 && b >= 1) {
			if (a < b)
				b = b % a;
			else
				a = a % b;
		}
		if (a >= 1)
			return a;
		return b;
	}

	// Judge whether argument is prime.
	bool isPrime(size_t value) {
		for (size_t i = 2; i < value; ++i) {
			if (value % i == 0)
				return false;
		}
		return true;
	}
#ifdef _STL_VECTOR_H
	template<class T> T average(const std::vector<T>& vec) {
		T sum = 0;
		for (const auto& r : vec)
			sum += r;
		return sum / vec.size();
	}
#endif // _STL_VECTOR_H
#endif // _GLIBCXX_CMATH
#include <algorithm>
#ifdef _GLIBCXX_ALGORITHM
	template<class RandomAccessIterator, class Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
	static inline bool iter_sorting_swap(RandomAccessIterator left, RandomAccessIterator right, Predicate pred = Predicate()) {
		if (a > b) return iter_sorting_swap(b, a);
		else       return pred(*right, *left) ? std::iter_swap(a, b), true : false;
	}

	template<class RandomAccessIterator> void bubble_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		for (auto it = first; it != last; ++it) {
			for (auto j = last - 1; j < it; --j) {
				iter_sorting_swap(j, j -1);
			}
		}
	}

	template<class RandomAccessIterator> void comb_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		auto size = last - first;
		for (decltype(size) interval = size / 1.3; ; interval /= 1.3) {
			for (auto it = first; i + interval < last; ++i) {
				iter_sorting_swap(i, i + interval);
			}
			if (interval <= 1) break;
		}
	}

	template<class RandomAccessIterator> void gnome_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		for (auto gnome = first + (last - first) / 2; gnome != last;) {
			if (gnome == first) ++gnome;
			iter_sorting_swap(gnome, gnome - 1) ? --gnome : ++gnome;
		}
	}

	template<class RandomAccessIterator> void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		iter_sorting_swap(first, first + 1);
		for (auto it = first + 1; i != last; ++i) {
			for (auto jt = it; jt > first; --jt) {
				if (!iter_sorting_swap(j, j - 1)) break;
			}
		}
	}

	template<class RandomAccessIterator> void merge_sort(RandomAccessIterator first, RandomAccessIterator last) {
		auto diff = last - first;
		if (diff <= 1) return;
		auto middle = first + diff / 2;
		merge_sort(first, middle);
		merge_sort(middle, last);
		std::inplace_merge(first, middle, last);
	}
#endif // _GLIBCXX_ALGORITHM