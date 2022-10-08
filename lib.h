#ifdef _STL_VECTOR_H
#if defined(_BASIC_STRING_H) && defined(_GLIBCXX_SSTREAM)
	template<class T>
	std::istream& operator>>(std::istream& istm, std::vector<T>& vec) {
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
	template<class T>
	std::ostream& operator<<(std::ostream& ostm, std::vector<T>& vec) {
		for (const auto& r : vec)
			ostm << r << ' ';
		return ostm;
	}
#endif // _STL_VECTOR_H

#ifdef _STL_MAP_H
	template<class Key, class T>
	std::istream& operator>>(std::istream& istm, std::map<Key, T>& mp) {
		std::string s;
		if (std::getline(istm, s)) {
			T tmp;
			std::istringstream iss(std::move(s));
			while (iss >> tmp)
				mp.at(tmp)++;
		}
		return istm;
	}
#endif // _STL_MAP_H

#ifdef _GLIBCXX_CMATH
	// formula of area of triangle. Arguments are length of base and height.
	template<class T>
	double area_triangle(T base, T height) {
		return base * height / 2;
	}

	// formula of area of triangle. Arguments are length of two sides and angle(degree) between these two sides.
	template<class T>
	double area_triangle(T a, T b, double deg) {
		return a * b * std::sin(deg * 180 / M_PI) / 2;
	}

	// heron's formula. This function returns area of triangle. Arguments are length of three sides.
	template<class T>
	double heron(T a, T b, T c) {
		const auto s =  (a + b + c) / 2;
		return std::sqrt(s * (s - a) * (s - b) * (s - c));
	}

	// factorial: n! = n * (n - 1) * ... * 1
	uintmax_t factorial(const uintmax_t n) {
		uintmax_t result = 1;
		for (uintmax_t i = 1; i < n + 1; ++i)
			result *= i;
		return result;
	}

	// permutation: n P r = n * (n - 1) * ... * (n - r + 1)
	uintmax_t permutation(const uintmax_t n, const uintmax_t r) {
		uintmax_t result = 1;
		for (uintmax_t i = n; i > n - r; --i)
			result *= i;
		return result;
	}

	// combination: n C r = n P r / r!
	uintmax_t combination(const uintmax_t n, const uintmax_t r) {
		if (r > n - r)
			return permutation(n, n - r) / factorial(n - r);
		else
			return permutation(n, r) / factorial(r);
	}

	// Euclid's algorithm. Return value is GCD of two integer.
	uintmax_t euclid(uintmax_t a, uintmax_t b) {
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
	bool isPrime(uintmax_t value) {
		for (uintmax_t i = 2; i < value; ++i) {
			if (value % i == 0)
				return false;
		}
		return true;
	}

	uintmax_t gcd(uintmax_t a, uintmax_t b) {
		if (a % b == 0) return b;
		else return gcd(b, a % b);
	}

	uintmax_t lcm(uintmax_t a, uintmax_t b) {
		return a * b / gcd(a, b);
	}
#ifdef _STL_VECTOR_H
	template<class T>
	T average(const std::vector<T>& vec) {
		T sum = 0;
		for (const auto& r : vec)
			sum += r;
		return sum / vec.size();
	}

	uintmax_t gcd(std::vector<uintmax_t>& vec) {
		uintmax_t result = vec.front();
		for (uintmax_t i = vec.size() - 2; i >= 0; --i)
			result = gcd(result, vec[i + 1]);
		return vec.front();
	}

	uintmax_t lcm(std::vector<uintmax_t>& vec) {
		uintmax_t result = vec.front();
		for (uintmax_t i = vec.size() - 2; i >= 0; --i)
			result = lcm(result, vec[i + 1]);
		return result;
	}
#endif // _STL_VECTOR_H
#endif // _GLIBCXX_CMATH

#include <algorithm>
#include <iterator>
#if defined(_GLIBCXX_ALGORITHM) && defined(_GLIBCXX_ITERATOR)
	// utility for sort algorithm.
	template<class RandomAccessIterator, class Predicate = std::less<class std::iterator_traits<RandomAccessIterator>::value_type>>
	bool iter_sorting_swap(RandomAccessIterator left, RandomAccessIterator right, Predicate pred = Predicate()) {
		if (left > right) return iter_sorting_swap(right, left);
		else return pred(*right, *left) ? std::iter_swap(left, right), true : false;
	}

	template<class RandomAccessIterator>
	void quick_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		RandomAccessIterator i = first, j = last - 1;
		for (auto pivot = first; ; ++i, --j) {
			while (*i < *pivot) ++i;
			while (*pivot < *j) --j;
			if (i >= j) break;
			iter_sorting_swap(i, j);
		}
		quick_sort(first, i);
		quick_sort(j + 1, last);
	}

	template<class RandomAccessIterator>
	void bubble_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		for (auto it = first; it != last; ++it)
			for (auto j = last - 1; j > it; --j)
				iter_sorting_swap(j, j - 1);
	}

	template<class RandomAccessIterator>
	void comb_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		auto size = last - first;
		for (decltype(size) interval = size / 1.3; ; interval /= 1.3) {
			for (auto it = first; it + interval < last; ++it)
				iter_sorting_swap(it, it + interval);
			if (interval <= 1) break;
		}
	}

	template<class RandomAccessIterator>
	void gnome_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		for (auto gnome = first + (last - first) / 2; gnome != last;) {
			if (gnome == first) ++gnome;
			iter_sorting_swap(gnome, gnome - 1) ? --gnome : ++gnome;
		}
	}

	template<class RandomAccessIterator>
	void insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		iter_sorting_swap(first, first + 1);
		for (auto it = first + 1; it != last; ++it) {
			for (auto jt = it; jt > first; --jt) {
				if (!iter_sorting_swap(jt, jt - 1)) break;
			}
		}
	}

	template<class RandomAccessIterator>
	void merge_sort(RandomAccessIterator first, RandomAccessIterator last) {
		auto diff = last - first;
		if (diff <= 1) return;
		auto middle = first + diff / 2;
		merge_sort(first, middle);
		merge_sort(middle, last);
		std::inplace_merge(first, middle, last);
	}

	template<class RandomAccessIterator>
	void selection_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		for (; first != last; ++first) {
			auto min = std::min_element(first, last);
			iter_sorting_swap(first, min);
		}
	}

	template<class RandomAccessIterator>
	void shaker_sort(RandomAccessIterator first, RandomAccessIterator last) {
		if (last - first <= 1) return;
		for (RandomAccessIterator index; first != last;) {
			for (auto it = first; it != last - 1; ++it)
				if (iter_sorting_swap(it, it + 1)) index = it;
			last = index;
			if (first == last) break;
			index = last;
			for (auto it = last; it != first; --it)
				if (iter_sorting_swap(it, it - 1)) index = it;
			first = index;
		}
	}
#endif // _GLIBCXX_ALGORITHM && _GLIBCXX_ITERATOR