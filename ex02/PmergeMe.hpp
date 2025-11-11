#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>

typedef std::vector<int> Vector;
typedef std::vector<Vector> Vector2D;

typedef std::deque<int> Deque;
typedef std::deque<Deque> DequeD2;

class PmergeMe {
    public:
        PmergeMe(int ac, char *av[]);
        ~PmergeMe();
        void sort();
    private:
        PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &src);

        Vector _v;
        Deque _d;

        Vector sortVector(Vector &v, int level, bool isDebug);
        // Deque sortDeque(Deque &d, int level, bool isDebug);

        // pairVec makePairs(const vec &v);
        // pairDeq makePairs(const deq &v);

        // void insertPendVector(vec &sorted, const vec &pend);
        // void insertPendDeque(deq &sorted, const deq &pend);

        void trim(std::string &s);
        bool isNumber(const std::string &str);

};

#endif
