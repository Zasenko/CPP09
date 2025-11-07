#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>

typedef std::vector<size_t> vec;
typedef std::vector<vec> pairVec;

typedef std::deque<size_t> deq;
typedef std::deque<deq> pairDeq;

class PmergeMe {
    public:
        PmergeMe(int ac, char *av[]);
        ~PmergeMe();
        void sort();
    private:
        PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &src);

        vec _v;
        deq _d;

        vec sortVector(const vec &v);
        deq sortDeque(const deq &d);

        pairVec makePairs(const vec &v);
        pairDeq makePairs(const deq &v);

        void insertPendVector(vec &sorted, const vec &pend);
        void insertPendDeque(deq &sorted, const deq &pend);

        void trim(std::string &s);
        bool isNumber(const std::string &str);

        template <typename Container>
        size_t binarySearch(const Container &sorted, typename Container::value_type value)
        {
            if (sorted.empty())
                return 0;
            size_t left = 0;
            size_t right = sorted.size();
            while (left < right)
            {
                size_t mid = left + (right - left) / 2;
                if (sorted[mid] < value)
                    left = mid + 1;
                else
                    right = mid;
            }
            return left;
        }

        template <typename Container>
        Container buildJacobOrder(size_t n)
        {
            Container order;
            if (n == 0)
                return order;

            // Generate Jacobsthal numbers up to n
            Container jacob;
            jacob.push_back(1);
            jacob.push_back(3);

            while (jacob.back() < n)
            {
                size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
                jacob.push_back(next);
            }
            order.push_back(0); // First element is always at index 0
            for (size_t i = 0; i < jacob.size(); i++)
            {
                size_t j = jacob[i];
                if (j < n)
                    order.push_back(j);
                // Add numbers between previous Jacobsthal numbers
                if (i > 0)
                {
                    size_t prev = jacob[i - 1];
                    for (size_t k = j - 1; k > prev; k--)
                    {
                        if (k < n)
                            order.push_back(k);
                        if (k - 1 == prev)
                            break; // защита от size_t underflow
                    }
                }
            }
            return order;
        }
};

#endif
