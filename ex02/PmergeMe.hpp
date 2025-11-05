#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <ctime>

typedef std::vector<int> vec;
typedef std::vector<vec> pairVec;

typedef std::deque<int> deq;
typedef std::deque<int> pairDeq;

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
        void sortDeque();

        void insertPendVector(vec &sorted, const vec &pend);

        std::vector<size_t> buildJacobOrder(size_t n);

        void trim(std::string &s);
        bool isNumber(const std::string &str);
};

#endif
